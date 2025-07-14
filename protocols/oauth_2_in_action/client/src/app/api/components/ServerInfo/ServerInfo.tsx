import { ServerConfigs } from '@/app/lib/model/config';

import ClientServerInfo from './ClientServerInfo';
import AuthServerInfo from './AuthServerInfo';
import ProtectedResourceServerInfo from './ProtectedResourceServerInfo';
import { ServerStatus } from '@/app/lib/model/status';

interface ServerInfoProps {
  serverConfigs: ServerConfigs;
  clientServerStatus: ServerStatus;
  authServerStatus: ServerStatus;
  protectedResourceServerStatus: ServerStatus;
}

export default function ServerInfo({
  serverConfigs,
  clientServerStatus,
  authServerStatus,
  protectedResourceServerStatus,
}: ServerInfoProps) {
  return (
    <aside>
      <ClientServerInfo
        config={serverConfigs.clientConfig}
        status={clientServerStatus}
      />
      <AuthServerInfo
        config={serverConfigs.authServerConfig}
        status={authServerStatus}
      />
      <ProtectedResourceServerInfo
        config={serverConfigs.protectedResourceServerConfig}
        status={protectedResourceServerStatus}
      />
    </aside>
  );
}
