import { useEffect, useState, } from 'react';
import { ServerStatus, } from '../lib/model/status';

export default function useServerStatus(uri: string,): ServerStatus {
  const [status, setStatus,] = useState<ServerStatus>('unknown',);
  const origin = new URL(uri,).origin;
  const ping = `${origin}/ping`;

  useEffect(() => {
    let isMounted = true;
    const checkStatus = async () => {
      try {
        const res = await fetch(ping,);
        if (isMounted) {
          setStatus(res.ok ? 'online' : 'offline',);
        }
      } catch {
        if (isMounted) {
          setStatus('offline',);
        }
      }
    };

    checkStatus();
    const interval = setInterval(checkStatus, 5000,);

    return () => {
      isMounted = false;
      clearInterval(interval,);
    };
  }, [ping,],);

  return status;
}
