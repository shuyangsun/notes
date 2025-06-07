import type React from 'react';
import { logRender } from '../util/log';

interface Props {
  onSearchInputChange: (event: React.ChangeEvent<HTMLInputElement>) => void;
}

export function Search({ onSearchInputChange }: Props) {
  logRender('Search');
  return (
    <>
      <input
        id="search"
        type="search"
        placeholder="search here"
        onChange={onSearchInputChange}
      ></input>
    </>
  );
}
