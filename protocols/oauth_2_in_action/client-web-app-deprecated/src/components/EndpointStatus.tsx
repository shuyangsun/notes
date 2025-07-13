import type { OnlineStatus } from '../stores/serverStatus';
import './EndpointStatus.css';

interface Props {
  uri: string;
  status: OnlineStatus;
}

export function EndpointStatus({ uri, status }: Props) {
  try {
    return (
      <>
        <a href={`${uri}/ping`}>{uri}</a>
        <span className={`indicator ${status}`}></span>
      </>
    );
  } catch (error) {
    return <p>{`Cannot create URL ${uri}, error: ${String(error)}`}</p>;
  }
}
