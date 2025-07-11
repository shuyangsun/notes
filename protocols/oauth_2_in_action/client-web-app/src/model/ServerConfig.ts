import { useEffect, useState } from 'react';
import type { AuthServerConfig } from './AuthServerConfig';
import type { ClientConfig } from './ClientConfig';

export interface ServerConfigResponse {
  client: ClientConfig;
  auth: AuthServerConfig;
}

export function useServerConfig(
  endpoint: string
): ServerConfigResponse | undefined {
  const [config, setConfig] = useState<ServerConfigResponse | undefined>(
    undefined
  );

  useEffect(() => {
    const controller = new AbortController();

    const fetchData = async () => {
      try {
        const serverConfigResponse = await fetch(endpoint);
        if (!serverConfigResponse.ok) {
          throw new Error(
            `HTTP error fetching server config! Status: ${serverConfigResponse.status}`
          );
        }
        const serverConfig =
          (await serverConfigResponse.json()) as ServerConfigResponse;
        setConfig(serverConfig);
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };
    void fetchData();

    return () => controller.abort();
  }, [endpoint]);

  return config;
}
