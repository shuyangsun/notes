import tiktoken
import torch
import torch.nn as nn

from torch.utils.data import Dataset, DataLoader

def text_corpus() -> str:
    with open('The_Verdict.txt', 'r', encoding='utf-8') as txt_file:
        return txt_file.read()

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
