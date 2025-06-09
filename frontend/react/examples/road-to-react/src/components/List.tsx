import { logRender } from '../util/log';
import { Item, type ListItem } from './Item';

interface Props {
  items: ListItem[];
  search: string;
  onRemove: (id: string) => void;
}

export function List({ items, search, onRemove }: Props) {
  logRender('List');
  const filteredItems: ListItem[] = search
    ? items.filter((ele: ListItem) =>
        ele.title.toLowerCase().includes(search.toLowerCase()),
      )
    : items;
  return (
    <ul>
      {filteredItems.map(({ ...item }: ListItem) => (
        <Item key={item.id} {...item} onRemove={onRemove} />
      ))}
    </ul>
  );
}
