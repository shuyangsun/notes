export interface ListItem {
  id: string;
  title: string;
  description: string;
}

type Props = Omit<ListItem, 'id'>;

export function Item({ title, description }: Props) {
  return (
    <li>
      <span className="title">{title}</span>
      {' - '}
      <span className="description">{description}</span>
    </li>
  );
}
