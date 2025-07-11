import { ServerStatus } from './ServerStatus';
import { ClientInfo } from './ClientInfo';
import {
  useServerConfig,
  type ServerConfigResponse,
} from './model/ServerConfig';
import './App.css';
import { AuthServerInfo } from './AuthServerInfo';

const serverConfigEndpoint = 'http://localhost:9000/server-config';

function useOriginUris(
  serverConfig: ServerConfigResponse | undefined
): Set<string> {
  const result = new Set<string>([new URL(serverConfigEndpoint).origin]);
  if (serverConfig === undefined) {
    return result;
  }
  if (serverConfig?.auth !== undefined) {
    result.add(new URL(serverConfig?.auth.authEndpoint).origin);
    result.add(new URL(serverConfig?.auth.tokenEndpoint).origin);
  }
  return result;
}

function App() {
  const serverConfig = useServerConfig(serverConfigEndpoint);
  const uris = useOriginUris(serverConfig);

  return (
    <>
      <h1>OAuth 2.0 Web Client</h1>

      <header>
        <div>
          <ServerStatus uris={uris} />
        </div>
        <div>
          <ClientInfo clientConfig={serverConfig?.client} />
        </div>
        <div>
          <AuthServerInfo authServerConfig={serverConfig?.auth} />
        </div>
      </header>
    </>
  );
}

export default App;
