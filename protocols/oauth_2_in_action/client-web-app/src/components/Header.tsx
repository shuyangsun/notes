import { ServerStatus } from './ServerStatus';
import { ClientInfo } from './ClientInfo';
import { AuthServerInfo } from './AuthServerInfo';

import './Header.css';
import { useServerConfig } from '../stores/serverStatus';

export function Header() {
  const serverConfig = useServerConfig();
  return serverConfig ? (
    <header>
      <div>
        <ServerStatus />
      </div>
      <div>
        <ClientInfo clientConfig={serverConfig.client} />
      </div>
      <div>
        <AuthServerInfo authServerConfig={serverConfig.auth} />
      </div>
    </header>
  ) : (
    <p className="error">Error fetching server config.</p>
  );
}
