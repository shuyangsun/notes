import './EndpointStatus.css';

interface Props {
  uri: string;
  online: boolean;
}

export function EndpointStatus({ uri, online }: Props) {
  try {
    const origin = new URL(uri).origin;
    return (
      <>
        <a href={`${origin}/ping`}>{origin}</a>
        <span className={`indicator ${online ? 'online' : 'offline'}`}></span>
      </>
    );
  } catch (error) {
    return <p>{`Cannot create URL ${uri}, error: ${String(error)}`}</p>;
  }
}
