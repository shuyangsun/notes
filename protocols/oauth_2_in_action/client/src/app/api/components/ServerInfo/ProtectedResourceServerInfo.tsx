import { ProtectedResourceServerConfig, } from '@/app/lib/model/config';
import ServerStatusHeader from './ServerInfoHeader';
import useServerStatus from '@/app/hooks/use-server-status';

interface ProtectedResourceServerStatusProps {
  config: ProtectedResourceServerConfig;
}

export default function ProtectedResourceServerInfo({
  config,
}: ProtectedResourceServerStatusProps,) {
  const status = useServerStatus(config.baseUri,);
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
