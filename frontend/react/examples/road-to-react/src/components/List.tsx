import { logRender } from '../util/log';
import { Item, type ListItem } from './Item';

interface Props {
  items: ListItem[];
  search: string;
}

export function List({ items, search }: Props) {
  logRender('List');
  const filteredItems: ListItem[] = search
    ? items.filter((ele: ListItem) =>
        ele.title.toLowerCase().includes(search.toLowerCase()),
      )
    : items;
  return (
    <ul>
      {filteredItems.map(({ id, ...item }: ListItem) => (
        <Item key={id} {...item} />
      ))}
    </ul>
  );
}
