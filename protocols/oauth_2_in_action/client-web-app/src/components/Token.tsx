import { useServerConfig } from '../stores/serverStatus';
import { Header } from './Header';

interface Props {
  token: string;
}

export function Token({ token }: Props) {
  const serverConfig = useServerConfig();
  const decoded = atob(token).split(':');
  return (
    <>
      <h1>Token Page</h1>
      <Header />

      <main>
        <p className="warning">
          <em>This is a terrible security practice!</em>
        </p>
        <p>Token Type: {decodeURIComponent(decoded[0]).trim()}</p>
        <p>Token: {decodeURIComponent(decoded[1]).trim()}</p>
        <a
          href={
            serverConfig ? serverConfig.client.fetchResourceEndpoint : '/error'
          }
          className={serverConfig ? '' : 'hidden'}
        >
          Get Protected Resource
        </a>
      </main>
    </>
  );
}
