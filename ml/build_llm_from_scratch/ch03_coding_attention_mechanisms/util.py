import tiktoken
import torch

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
) -> DataLoader:
    tokenizer = tiktoken.get_encoding('gpt2')
    dataset = GPTDatasetV1(content, tokenizer, context_window, stride)
    return DataLoader(
        dataset,
        batch_size=batch_size,
        shuffle=shuffle,
        drop_last=drop_last,
        num_workers=num_workers,
    )
