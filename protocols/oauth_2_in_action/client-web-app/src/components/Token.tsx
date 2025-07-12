import { Header } from './Header';

interface Props {
  token: string;
}

export function Token({ token }: Props) {
  const decoded = atob(token).split(':');
  return (
    <>
      <h1>OAuth 2.0 Web Client Token</h1>
      <Header />
      <p className="warning">
        <em>This is a terrible security practice!</em>
      </p>
      <p>Token Type: {decodeURIComponent(decoded[0]).trim()}</p>
      <p>Token: {decodeURIComponent(decoded[1]).trim()}</p>
      <a href="/">Home</a>
    </>
  );
}
