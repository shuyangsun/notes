import { type AuthServerConfig } from '../model/AuthServerConfig';

function AuthServerInfoList(authServerConfig: AuthServerConfig) {
  const authUri = authServerConfig.authEndpoint;
  const tokenUri = authServerConfig.tokenEndpoint;
  return (
    <ul>
      <li key={authUri}>
        Auth endpoint:&nbsp;
        <a href={authUri}>{authUri}</a>
      </li>
      <li key={tokenUri}>
        Token endpoint:&nbsp;
        <a href={tokenUri}>{tokenUri}</a>
      </li>
    </ul>
  );
}

export function AuthServerInfo({
  authServerConfig,
}: {
  authServerConfig: AuthServerConfig | undefined;
}) {
  return (
    <>
      <h2>Auth Server Info</h2>
      {authServerConfig ? (
        <AuthServerInfoList {...authServerConfig} />
      ) : (
        <p className="error">Could not get auth server info.</p>
      )}
    </>
  );
}
