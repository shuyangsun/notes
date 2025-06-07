import type React from 'react';
import { logRender } from '../util/log';

interface Props {
  search: string;
  onSearchInputChange: (event: React.ChangeEvent<HTMLInputElement>) => void;
}

export function Search({ search, onSearchInputChange }: Props) {
  logRender('Search');
  return (
    <>
      <input
        id="search"
        type="search"
        placeholder="search here"
        value={search}
        onChange={onSearchInputChange}
      ></input>
    </>
  );
}
