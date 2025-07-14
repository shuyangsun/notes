import ClientServerInfo from './ClientServerInfo';
import AuthServerInfo from './AuthServerInfo';
import ProtectedResourceServerInfo from './ProtectedResourceServerInfo';
import { serverConfigs, } from '@/app/lib/model/config';

export default function ServerInfo() {
  return (
    <aside>
      <ClientServerInfo config={serverConfigs.clientConfig} />
      <AuthServerInfo config={serverConfigs.authServerConfig} />
      <ProtectedResourceServerInfo
        config={serverConfigs.protectedResourceServerConfig}
      />
    </aside>
  );
}
