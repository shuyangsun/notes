import { useEffect, useState } from 'react';
import { useServerConfig } from '../stores/serverStatus';
import { Header } from './Header';
import type { ResourceResponse } from '../model/ResourceServerConfig';

interface Props {
  token: string;
}

export function Token({ token }: Props) {
  const [resource, setResource] = useState<ResourceResponse | undefined>(
    undefined
  );
  const serverConfig = useServerConfig();
  const decoded = atob(token).split(':');
  const resourceEndpoint = serverConfig?.client.fetchResourceEndpoint;
  useEffect(() => {
    const fetchData = async () => {
      if (resourceEndpoint) {
        const res = await fetch(resourceEndpoint);
        const json = (await res.json()) as ResourceResponse;
        setResource(json);
      }
    };
    void fetchData();
  }, [resourceEndpoint, setResource]);

  return (
    <>
      <h1>Token Page</h1>
      <Header />

      <main>
        <p className="warning">
          <em>This is a terrible security practice!</em>
        </p>
        <p>Token Type: {decodeURIComponent(decoded[0]).trim()}</p>
        <p>Token: {decodeURIComponent(decoded[1]).trim()}</p>
        <h3>Resource</h3>
        <ul>
          <li>name: {resource?.name ?? 'undefined'}</li>
          <li>description: {resource?.description ?? 'undefined'}</li>
        </ul>
      </main>
    </>
  );
}
