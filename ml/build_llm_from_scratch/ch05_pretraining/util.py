import tiktoken
import torch
import torch.nn as nn

from torch.utils.data import Dataset, DataLoader
from typing import Self

def text_corpus() -> str:
    with open('The_Verdict.txt', 'r', encoding='utf-8') as txt_file:
        return txt_file.read()

def text_to_token_ids(text: str, tokenizer: tiktoken.Encoding) -> list[int]:
    return tokenizer.encode(content, allowed_special={'<|endoftext|>'})

class GPTDatasetV1(Dataset):
    _input_ids: list[torch.Tensor]
    _target_ids: list[torch.Tensor]

    def __init__(
        self,
        content: str,
        tokenizer: tiktoken.core.Encoding,
        context_window_size: int,
        stride: int
    ):
        self._input_ids = []
        self._target_ids = []

        token_ids = tokenizer.encode(content, allowed_special={'<|endoftext|>'})

        for i in range(0, len(token_ids) - context_window_size, stride):
            input_chunk = token_ids[i:i + context_window_size]
            target_chunk = token_ids[i + 1: i + 1 + context_window_size]
            self._input_ids.append(torch.tensor(input_chunk))
            self._target_ids.append(torch.tensor(target_chunk))

    def __len__(self) -> int:
        return len(self._input_ids)

    def __getitem__(self, idx: int) -> (torch.Tensor, torch.Tensor):
        return self._input_ids[idx], self._target_ids[idx]

def create_dataloader_v1(
    content: str,
    batch_size: int,
    context_window: int, 
    stride: int = 1,
    shuffle: bool = True,
    drop_last: bool = True,
    num_workers: int = 0,
    tokenizer: tiktoken.Encoding = tiktoken.get_encoding('gpt2'),
) -> DataLoader:
    dataset = GPTDatasetV1(content, tokenizer, context_window, stride)
    return DataLoader(
        dataset,
        batch_size=batch_size,
        shuffle=shuffle,
        drop_last=drop_last,
        num_workers=num_workers,
    )

class MultiHeadAttention(nn.Module):
    def __init__(
        self,
        d_in: int,
        d_out: int,
        context_length: int,
        dropout: float,
        num_heads: int,
        qkv_bias=False
    ): 
        super().__init__()
        assert (d_out % num_heads == 0), f'd_out ({d_out}) must be divisible by num_heads ({num_heads})'

        self._d_in = d_in
        self._d_out = d_out
        self._context_length = context_length
        self._num_heads = num_heads
        self._head_dim = d_out // num_heads

        self._w_query = nn.Linear(d_in, d_out, bias=qkv_bias)
        self._w_key = nn.Linear(d_in, d_out, bias=qkv_bias)
        self._w_value = nn.Linear(d_in, d_out, bias=qkv_bias)
        self._out_proj = nn.Linear(d_out, d_out)
        self._dropout = nn.Dropout(dropout)

        self.register_buffer(
            'mask',
            torch.triu(torch.ones(context_length, context_length), diagonal=1).bool()
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        b, num_tokens, d_in = x.shape
        assert (d_in == self._d_in), f'input d_in ({d_in}) must be the same as d_in ({self._d_in})'

        # KQV shape: (b, num_heads, num_tokens, head_dim)
        keys = self._reshape_kqv(self._w_key(x), b, num_tokens)
        queries = self._reshape_kqv(self._w_query(x), b, num_tokens)
        values = self._reshape_kqv(self._w_value(x), b, num_tokens)

        # Attention scores and weights shape:  (b, num_heads, num_tokens, num_tokens)
        attn_scores = queries @ keys.transpose(2, 3)
        mask = self.mask[:num_tokens, :num_tokens]
        attn_weights = torch.softmax(attn_scores / self._head_dim ** 0.5, dim=-1)
        attn_weights = self._dropout(attn_weights)

        context_vec = (attn_weights @ values).transpose(1, 2) # (b, num_tokens, num_heads, head_dim)
        context_vec = context_vec.contiguous().view(b, num_tokens, self._d_out)
        return self._out_proj(context_vec) # (b, num_tokens, d_out)

    def _reshape_kqv(self, tensor: torch.Tensor, b: int, num_tokens: int) -> torch.Tensor:
        """
        Converts QKV weights from shape (b, num_tokens, d_out) to (b, num_heads, num_tokens, head_dim).
        """
        return tensor.view(b, num_tokens, self._num_heads, self._head_dim).transpose(1, 2)

class Config:
    def __init__(
        self,
        vocab_size: int,
        context_length: int,
        emb_dim: int,
        n_heads: int,
        n_layers: int,
        drop_rate: float,
        qkv_bias: bool
    ):
        self.vocab_size = vocab_size
        self.context_length = context_length
        self.emb_dim = emb_dim
        self.n_heads = n_heads
        self.n_layers = n_layers
        self.drop_rate = drop_rate
        self.qkv_bias = qkv_bias

    def as_dict(self) -> dict[str, int | float | bool]:
        return self.__dict__

    @classmethod
    def gpt2_small(cls) -> Self:
        return Config(
            vocab_size = 50257,
            context_length = 1024,
            emb_dim = 768,
            n_heads = 12,
            n_layers = 12,
            drop_rate = 0.1,
            qkv_bias = False,
        )

    @classmethod
    def gpt2_medium(cls) -> Self:
        return Config(
            vocab_size = 50257,
            context_length = 1024,
            emb_dim = 1024,
            n_heads = 16,
            n_layers = 24,
            drop_rate = 0.1,
            qkv_bias = False,
        )

    @classmethod
    def gpt2_large(cls) -> Self:
        return Config(
            vocab_size = 50257,
            context_length = 1024,
            emb_dim = 1280,
            n_heads = 20,
            n_layers = 36,
            drop_rate = 0.1,
            qkv_bias = False,
        )

    @classmethod
    def gpt2_xl(cls) -> Self:
        return Config(
            vocab_size = 50257,
            context_length = 1024,
            emb_dim = 1600,
            n_heads = 25,
            n_layers = 48,
            drop_rate = 0.1,
            qkv_bias = False,
        )

class LayerNorm(nn.Module):
    def __init__(self, emb_dim: int):
        super().__init__()
        self.eps = 1e-7
        self.scale = nn.Parameter(torch.ones(emb_dim))
        self.shift = nn.Parameter(torch.zeros(emb_dim))

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        mean = x.mean(dim=-1, keepdim=True)
        var = x.var(dim=-1, keepdim=True, unbiased=False)
        norm_x = (x - mean) / torch.sqrt(var + self.eps)
        return self.scale * norm_x + self.shift

class FeedForward(nn.Module):
    def __init__(self, emb_dim: int, expand_factor: int = 4):
        super().__init__()
        self.layers = nn.Sequential(
            nn.Linear(emb_dim, expand_factor * emb_dim),
            nn.GELU(),
            nn.Linear(expand_factor * emb_dim, emb_dim),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.layers(x)

class TransformerBlock(nn.Module):
    def __init__(self, cfg: Config):
        super().__init__()
        self.mhatt = MultiHeadAttention(
            d_in=cfg.emb_dim,
            d_out=cfg.emb_dim,
            context_length=cfg.context_length,
            dropout=cfg.drop_rate,
            num_heads=cfg.n_heads,
        )
        self.ff = FeedForward(cfg.emb_dim)
        self.norm1 = LayerNorm(cfg.emb_dim)
        self.norm2 = LayerNorm(cfg.emb_dim)
        self.drop = nn.Dropout(cfg.drop_rate)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        x = self.drop(self.mhatt(self.norm1(x))) + x
        return self.drop(self.ff(self.norm2(x))) + x

class GPTModel(nn.Module):
    def __init__(self, cfg: Config):
        super().__init__()
        self.tok_emb = nn.Embedding(cfg.vocab_size, cfg.emb_dim)
        self.pos_emb = nn.Embedding(cfg.context_length, cfg.emb_dim)
        self.drop_emb = nn.Dropout(cfg.drop_rate)

        self.trf_blocks = nn.Sequential(*[TransformerBlock(cfg) for _ in range(cfg.n_layers)])
        self.final_norm = LayerNorm(cfg.emb_dim)
        self.out_head = nn.Linear(cfg.emb_dim, cfg.vocab_size, bias=False)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        b, seq_len = x.shape
        tok_emb = self.tok_emb(x)
        pos_emb = self.pos_emb(torch.arange(seq_len, device=x.device))
        return self.out_head(self.final_norm(self.trf_blocks(self.drop_emb(tok_emb + pos_emb))))

    def num_params(self) -> int:
        return sum(p.numel() for p in self.parameters())

    def f32_param_size_gb(self) -> int:
        return self.num_params() * 4 / 1024 ** 3

def predict_text(model: GPTModel, device: torch.device, tokenizer: tiktoken.Encoding, text: str, max_len: int = 1024) -> str:
    eos = '<|endoftext|>'
    next_token: str | None = None
    encoded_len: int = 0
    model.eval()
    with torch.no_grad():
        while next_token != eos and encoded_len < max_len:
            encoded = tokenizer.encode(text, allowed_special={eos})
            encoded_len = len(encoded)
            next_tok_logits = model(torch.tensor(encoded).unsqueeze(0).to(device)).squeeze(0)[-1]
            next_tok_probs = torch.softmax(next_tok_logits, dim=0)
            next_token = tokenizer.decode([torch.argmax(next_tok_probs).item()])
            text += next_token
    model.train()
    return text

def auto_device() -> torch.device:
    if torch.cuda.is_available():
        print('Using CUDA backend.')
        return torch.device('cuda')
    if torch.backends.mps.is_available():
        print('Using MPS backend.')
        return torch.device('mps')
    print('Using CPU backend.')
    return torch.device('cpu')