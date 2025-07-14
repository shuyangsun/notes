import { ProtectedResourceServerConfig, } from '@/app/lib/model/config';
import { ServerStatus, } from '@/app/lib/model/status';
import ServerStatusHeader from './ServerInfoHeader';

interface ProtectedResourceServerStatusProps {
  config: ProtectedResourceServerConfig;
  status: ServerStatus;
}

export default function ProtectedResourceServerInfo({
  config,
  status,
}: ProtectedResourceServerStatusProps,) {
  return (
    <section>
      <ServerStatusHeader
        name='Protected Resource Server'
        baseUri={config.baseUri}
        status={status}
      />
    </section>
  );
}
