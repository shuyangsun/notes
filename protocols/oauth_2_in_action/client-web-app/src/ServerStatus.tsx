import { EndpointStatus } from './EndpointStatus';
import { useState, useEffect } from 'react';

interface ServerStatusProps {
  uris: Set<string>;
}

async function checkServerStatus(uri: string) {
  try {
    const response = await fetch(`${uri}/ping`);
    return response.ok;
  } catch {
    return false;
  }
}

export function ServerStatus({ uris }: ServerStatusProps) {
  const [serverStatus, setServerStatus] = useState<Record<string, boolean>>({});

  useEffect(() => {
    const pingServers = async () => {
      const allEndpoints = new Set<string>(
        Array.from(uris).map((uri) => new URL(uri).origin)
      );

      const result: Record<string, boolean> = {};
      for (const uri of allEndpoints) {
        result[uri] = await checkServerStatus(uri);
      }

      setServerStatus(result);
    };

    void pingServers();
    const interval = setInterval(pingServers, 5000);
    return () => clearInterval(interval);
  }, [uris]);

  return (
    <>
      <h2>Server Status</h2>
      <ul>
        {Object.entries(serverStatus)
          .sort(([a], [b]) => a.localeCompare(b))
          .map(([uri, online]) => (
            <li key={uri}>
              <EndpointStatus uri={uri} online={online} />
            </li>
          ))}
      </ul>
    </>
  );
}
