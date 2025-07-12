import { type ClientConfig } from '../model/ClientConfig';

function ClientInfoList({
  clientId,
  clientSecret,
  redirectUris,
}: ClientConfig) {
  return (
    <ul>
      <li>Client ID: {clientId}</li>
      <li>Client Secret: {clientSecret}</li>
      <li>
        Redirect URIs:
        <ul>
          {redirectUris.map((uri) => (
            <li key={uri}>
              <a href={uri}>{uri}</a>
            </li>
          ))}
        </ul>
      </li>
    </ul>
  );
}

export function ClientInfo({
  clientConfig,
}: {
  clientConfig: ClientConfig | undefined;
}) {
  return (
    <>
      <h2>Client Info</h2>
      {clientConfig ? (
        <ClientInfoList {...clientConfig} />
      ) : (
        <p className="error">Could not get client info.</p>
      )}
    </>
  );
}
