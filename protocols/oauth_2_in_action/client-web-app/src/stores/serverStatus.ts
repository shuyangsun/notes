import { Store, useStore } from '@tanstack/react-store';
import type { ServerConfigResponse } from '../model/ServerConfig';

export type OnlineStatus = 'unknown' | 'online' | 'offline';
type StatusMap = Record<string, OnlineStatus>;

export const serverConfigEndpoint = 'http://localhost:9000/server-config';

const serverConfigStore = new Store<ServerConfigResponse | undefined>(
  undefined
);

const serverStatusStore = new Store<{ status: StatusMap }>({ status: {} });

export function useServerConfig(): ServerConfigResponse | undefined {
  return useStore(serverConfigStore, (state) => state);
}

export function setServerConfig(config: ServerConfigResponse) {
  serverConfigStore.setState(() => config);
  for (const uri of config.client.redirectUris) {
    addUriToServerStatusStore(uri);
  }
  addUriToServerStatusStore(config.auth.authEndpoint);
  addUriToServerStatusStore(config.auth.tokenEndpoint);
}

export function useServersStatus(): [
  StatusMap,
  (statusMap: StatusMap) => void,
] {
  const status = useStore(serverStatusStore, (state) => state.status);
  const setStatus = (statusMap: StatusMap) => {
    serverStatusStore.setState(() => {
      return { status: statusMap };
    });
  };
  return [status, setStatus];
}

export function addUriToServerStatusStore(uri: string) {
  const origin = new URL(uri).origin;
  serverStatusStore.setState((state) => {
    if (origin in Object.keys(state.status)) {
      return state;
    }
    const res = { status: { ...state.status } };
    res.status[origin] = 'unknown';
    return res;
  });
}
