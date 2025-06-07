import { logRender } from '../util/log';

export interface ListItem {
  id: string;
  name: string;
}

interface Props {
  items: ListItem[];
  search: string;
}

export function List({ items, search }: Props) {
  logRender('List');
  const filteredItems: ListItem[] = search
    ? items
    : items.filter((ele: ListItem) =>
        search ? ele.name.toLowerCase().includes(search.toLowerCase()) : true,
      );
  return (
    <ul>
      {filteredItems.map((ele: ListItem) => (
        <li key={ele.id}>{ele.name}</li>
      ))}
    </ul>
  );
}
