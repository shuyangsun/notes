import {
  authServerConf,
  clientConf,
  protectedResourceServerConf,
} from '@/app/lib/model/config';

import ClientServerInfo from './ClientServerInfo';
import AuthServerInfo from './AuthServerInfo';
import ProtectedResourceServerInfo from './ProtectedResourceServerInfo';

export default function ServerInfo() {
  return (
    <aside>
      <ClientServerInfo config={clientConf} status='unknown' />
      <AuthServerInfo config={authServerConf} status='unknown' />
      <ProtectedResourceServerInfo
        config={protectedResourceServerConf}
        status='unknown'
      />
    </aside>
  );
}
