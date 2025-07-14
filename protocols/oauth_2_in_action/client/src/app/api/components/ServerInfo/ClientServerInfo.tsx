import { ClientConfig } from '@/app/lib/model/config';
import ServerStatusHeader from './ServerInfoHeader';
import useServerStatus from '@/app/hooks/use-server-status';

interface ClientServerStatusProps {
  config: ClientConfig;
}

export default function ClientServerInfo({ config }: ClientServerStatusProps) {
  const status = useServerStatus(`${config.baseUri}/api/ping`);
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
