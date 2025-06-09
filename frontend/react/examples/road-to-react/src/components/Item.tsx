export interface ListItem {
  id: string;
  title: string;
}

type Props = ListItem & { onRemove: (id: string) => void };

export function Item({ id, title, onRemove }: Props) {
  return (
    <li>
      <span className="title">{title + ' '}</span>
      <button onClick={() => onRemove(id)}>X</button>
    </li>
  );
}
