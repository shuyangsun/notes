export interface ListItem {
  id: string;
  name: string;
}

interface Props {
  items: ListItem[];
}

export function List({ items }: Props) {
  return (
    <ul>
      {items.map((ele: ListItem) => (
        <li key={ele.id}>{ele.name}</li>
      ))}
    </ul>
  );
}
