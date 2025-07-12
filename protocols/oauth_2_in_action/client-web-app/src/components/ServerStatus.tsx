import { useServersStatus } from '../stores/serverStatus';
import { EndpointStatus } from './EndpointStatus';

export function ServerStatus() {
  const [serverStatus] = useServersStatus();

  return (
    <>
      <h2>Server Status</h2>
      <ul>
        {Object.entries(serverStatus)
          .sort(([a], [b]) => a.localeCompare(b))
          .map(([uri, status]) => (
            <li key={uri}>
              <EndpointStatus uri={uri} status={status} />
            </li>
          ))}
      </ul>
    </>
  );
}
