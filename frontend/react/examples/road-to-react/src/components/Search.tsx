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
      <input id="search" type="search" onChange={onSearchInputChange}></input>
      <label htmlFor="search">Searching for: {search} </label>
    </>
  );
}
