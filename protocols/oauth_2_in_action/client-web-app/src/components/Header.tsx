import { ServerStatus } from './ServerStatus';
import { ClientInfo } from './ClientInfo';
import { AuthServerInfo } from './AuthServerInfo';
import {
  serverConfigEndpoint,
  type ServerConfigResponse,
} from '../model/ServerConfig';

import './Header.css';

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

interface Props {
  serverConfig: ServerConfigResponse;
}

export function Header({ serverConfig }: Props) {
  const uris = useOriginUris(serverConfig);
  return (
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
  );
}
