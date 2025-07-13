import { ServerStatus } from './ServerStatus';
import { ClientInfo } from './ClientInfo';
import { AuthServerInfo } from './AuthServerInfo';

import './Header.css';
import { useServerConfig } from '../stores/serverStatus';
import { ResourceServerInfo } from './ResourceServerInfo';

export function Header() {
  const serverConfig = useServerConfig();
  return serverConfig ? (
    <header>
      <nav>
        {' '}
        <a href="/">Home</a>{' '}
      </nav>

      <div>
        <ServerStatus />
      </div>
      <div>
        <ClientInfo clientConfig={serverConfig.client} />
      </div>
      <div>
        <AuthServerInfo authServerConfig={serverConfig.auth} />
      </div>
      <div>
        <ResourceServerInfo resourceServerConfig={serverConfig.resource} />
      </div>
    </header>
  ) : (
    <p className="error">Error fetching server config.</p>
  );
}
