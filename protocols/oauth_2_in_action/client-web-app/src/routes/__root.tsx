import { useEffect } from 'react';
import { createRootRoute, Outlet } from '@tanstack/react-router';
import { TanStackRouterDevtools } from '@tanstack/react-router-devtools';
import {
  serverConfigEndpoint,
  setServerConfig,
  useServersStatus,
  type OnlineStatus,
} from '../stores/serverStatus';
import type { ServerConfigResponse } from '../model/ServerConfig';

export const Route = createRootRoute({
  component: RootComponent,
});

function RootComponent() {
  const [serverStatus, setServerStatus] = useServersStatus();

  useEffect(() => {
    const controller = new AbortController();

    const fetchData = async () => {
      try {
        const serverConfigResponse = await fetch(serverConfigEndpoint);
        if (!serverConfigResponse.ok) {
          throw new Error(
            `HTTP error fetching server config! Status: ${serverConfigResponse.status}`
          );
        }
        const serverConfig =
          (await serverConfigResponse.json()) as ServerConfigResponse;
        if (serverConfig) {
          setServerConfig(serverConfig);
        }
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };
    void fetchData();

    return () => controller.abort();
  }, []);

  useEffect(() => {
    const pingServers = async () => {
      const allEndpoints = new Set<string>(Object.keys(serverStatus));

      const result: Record<string, OnlineStatus> = {};
      for (const uri of allEndpoints) {
        result[uri] = (await checkServerStatus(uri)) ? 'online' : 'offline';
      }

      setServerStatus(result);
    };

    void pingServers();
    const interval = setInterval(pingServers, 5000);
    return () => clearInterval(interval);
  }, [serverStatus, setServerStatus]);

  return (
    <>
      <Outlet />
      <TanStackRouterDevtools />
    </>
  );
}

async function checkServerStatus(uri: string): Promise<boolean> {
  try {
    const response = await fetch(`${uri}/ping`);
    return response.ok;
  } catch {
    return false;
  }
}
