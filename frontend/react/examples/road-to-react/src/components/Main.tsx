import { useState } from 'react';

import { Search } from './Search';
import { List, type ListItem } from './List';
import { logRender } from '../util/log';

export function Main() {
  logRender('Main');

  const [search, setSearch] = useState<string>('');
  const items: ListItem[] = [
    {
      id: 'df50ccdb-96cc-4643-a6db-2c0efde0194e',
      name: 'Personal Website',
    },
    {
      id: 'ca7e706f-6009-4632-b158-e48f46d968e0',
      name: 'Landing Page',
    },
    {
      id: '94e65127-f330-45ed-9374-ae4ca0e3d9a1',
      name: 'E-Commerce',
    },
    {
      id: 'ad79a2b9-9871-4382-85f7-8dfcf5027f65',
      name: 'Design Portfolio',
    },
  ];

  function onSearchInputChange(
    event: React.ChangeEvent<HTMLInputElement>,
  ): void {
    setSearch(event.target.value);
    if (event.target.value) {
      console.log(`Searching for '${event.target.value}'`);
    } else {
      console.log('Cleared search field.');
    }
  }

  return (
    <>
      <Search search={search} onSearchInputChange={onSearchInputChange} />
      <List items={items} search={search} />
    </>
  );
}
