import { useState, useEffect } from 'react';

import { TextInput } from './TextInput';
import { List } from './List';
import { type ListItem } from './Item';
import { logRender } from '../util/log';

import { v4 as uuidv4 } from 'uuid';

function useStorageState<T>(key: string, initialState: T) {
  const [value, setValue] = useState<any>(
    localStorage.getItem(key) ?? initialState,
  );

  useEffect(() => {
    localStorage.setItem(key, value);
  }, [key, value]);
  return [value, setValue];
}

const initialItems: ListItem[] = [
  {
    id: uuidv4(),
    title: 'Personal Website',
  },
  {
    id: uuidv4(),
    title: 'Landing Page',
  },
  {
    id: uuidv4(),
    title: 'E-Commerce',
  },
  {
    id: uuidv4(),
    title: 'Design Portfolio',
  },
];

function getItems(): Promise<ListItem[]> {
  return new Promise((resolve) => {
    setTimeout(() => resolve(initialItems), 2000);
  });
}

export function Main() {
  logRender('Main');

  const [search, setSearch] = useStorageState<string>('search', '');
  const [items, setItems] = useState<ListItem[]>([]);
  const [addItemName, setAddItemName] = useState<string>('');

  useEffect(() => {
    getItems().then((result) => {
      setItems(result);
    });
  });

  function onSearchQueryChange(event: React.ChangeEvent<HTMLInputElement>) {
    setSearch(event.target.value);
  }

  function onAddItemNameChange(event: React.ChangeEvent<HTMLInputElement>) {
    setAddItemName(event.target.value);
  }

  function onAddItem() {
    setItems([
      ...items,
      {
        id: uuidv4(),
        title: addItemName,
      },
    ]);
  }

  function onRemoveItem(id: string) {
    setItems(items.filter((ele) => ele.id !== id));
  }

  return (
    <>
      <TextInput
        id="search"
        placeholder="Search here"
        text={search}
        type="search"
        isFocused
        onValueChange={onSearchQueryChange}
      >
        <strong>Filter</strong>
      </TextInput>
      <List items={items} search={search} onRemove={onRemoveItem} />
      <TextInput
        id="add-item"
        placeholder="Item name"
        text={addItemName}
        type="text"
        isFocused
        onValueChange={onAddItemNameChange}
      ></TextInput>{' '}
      <button onClick={onAddItem}>Add</button>
    </>
  );
}
