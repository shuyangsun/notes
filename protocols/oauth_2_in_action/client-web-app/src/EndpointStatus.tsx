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
        <span
          style={{
            display: 'inline-block',
            width: '8px',
            height: '8px',
            borderRadius: '50%',
            backgroundColor: online ? 'green' : 'red',
            marginLeft: '8px',
          }}
        ></span>
      </>
    );
  } catch (error) {
    return <p>{`Cannot create URL ${uri}, error: ${String(error)}`}</p>;
  }
}
