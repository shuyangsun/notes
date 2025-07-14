import { AuthServerConfig, } from '@/app/lib/model/config';
import ServerStatusHeader from './ServerInfoHeader';
import useServerStatus from '@/app/hooks/use-server-status';

interface AuthServerStatusProps {
  config: AuthServerConfig;
}

export default function AuthServerInfo({ config, }: AuthServerStatusProps,) {
  const status = useServerStatus(config.baseUri,);

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
