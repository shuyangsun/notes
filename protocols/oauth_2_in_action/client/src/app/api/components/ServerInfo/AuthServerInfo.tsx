import { AuthServerConfig, } from '@/app/lib/model/config';
import { ServerStatus, } from '@/app/lib/model/status';
import ServerStatusHeader from './ServerInfoHeader';

interface AuthServerStatusProps {
  config: AuthServerConfig;
  status: ServerStatus;
}

export default function AuthServerInfo({
  config,
  status,
}: AuthServerStatusProps,) {
  return (
    <section>
      <ServerStatusHeader
        name='Auth Server'
        baseUri={config.baseUri}
        status={status}
      />
    </section>
  );
}
