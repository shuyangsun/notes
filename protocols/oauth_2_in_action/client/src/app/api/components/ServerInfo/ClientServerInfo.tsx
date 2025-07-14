import { ClientConfig, } from '@/app/lib/model/config';
import { ServerStatus, } from '@/app/lib/model/status';
import ServerStatusHeader from './ServerInfoHeader';

interface ClientServerStatusProps {
  config: ClientConfig;
  status: ServerStatus;
}

export default function ClientServerInfo({
  config,
  status,
}: ClientServerStatusProps,) {
  return (
    <section>
      <ServerStatusHeader
        name='Client'
        baseUri={config.baseUri}
        status={status}
      />
    </section>
  );
}
