import { Search } from './Search';
import { List, type ListItem } from './List';

export function Main() {
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
  return (
    <>
      <Search />
      <List items={items} />
    </>
  );
}
