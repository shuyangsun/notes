import { useState, useEffect } from 'react';
import { ServerStatus } from './ServerStatus';
import './App.css';

interface ClientConfig {
  clientId: string;
  clientSecret: string;
  redirectUris: string[];
}

interface AuthServerConfig {
  authEndpoint: string;
  tokenEndpoint: string;
}

function ClientInfo({ clientId, clientSecret, redirectUris }: ClientConfig) {
  return (
    <>
      <ul>
        <li>Client ID: {clientId}</li>
        <li>Client Secret: {clientSecret}</li>
        <li>
          Redirect URIs:
          <ul>
            {redirectUris.map((uri) => (
              <li key={uri}>{uri}</li>
            ))}
          </ul>
        </li>
      </ul>
    </>
  );
}

function AuthServerInfo({ authEndpoint, tokenEndpoint }: AuthServerConfig) {
  return (
    <>
      <ul>
        <li>Auth endpoint: {authEndpoint}</li>
        <li>Token endpoint: {tokenEndpoint}</li>
      </ul>
    </>
  );
}

function App() {
  const clientInfoEndpoint = 'http://localhost:9001/client-info';
  const authServerInfoEndpoint = 'http://localhost:9001/auth-server-info';

  const [clientConfig, setClientConfig] = useState<ClientConfig | undefined>(
    undefined
  );
  const [authServerConfig, setAuthServerConfig] = useState<
    AuthServerConfig | undefined
  >(undefined);

  useEffect(() => {
    const controller = new AbortController();

    const fetchData = async () => {
      try {
        const clientInfoResponse = await fetch(clientInfoEndpoint);
        if (!clientInfoResponse.ok) {
          throw new Error(
            `HTTP error fetching client info! Status: ${clientInfoResponse.status}`
          );
        }
        const clientConf = (await clientInfoResponse.json()) as ClientConfig;
        setClientConfig(clientConf);

        const serverInfoResponse = await fetch(authServerInfoEndpoint);
        if (!serverInfoResponse.ok) {
          throw new Error(
            `HTTP error fetching auth server info! Status: ${serverInfoResponse.status}`
          );
        }
        const serverConf =
          (await serverInfoResponse.json()) as AuthServerConfig;
        setAuthServerConfig(serverConf);
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    };
    void fetchData();

    return () => controller.abort();
  }, []);

  const allUrisSet = new Set<string>([
    new URL(clientInfoEndpoint).origin,
    new URL(authServerInfoEndpoint).origin,
  ]);
  try {
    for (const uri of clientConfig?.redirectUris ?? []) {
      allUrisSet.add(new URL(uri).origin);
    }
  } catch (error) {
    console.log(`Error creating URI: ${String(error)}`);
  }
  const allUris = Array.from(allUrisSet).sort();

  return (
    <>
      <h1>OAuth 2.0 Web Client</h1>
      <h2>Server Status</h2>
      <ul>
        {allUris.map((uri) => {
          return (
            <li key={uri}>
              {/* TODO: don't use hardcoded online status */}
              <ServerStatus uri={uri} online={true} />
            </li>
          );
        })}
      </ul>
      <h2>Client Info</h2>
      {clientConfig ? (
        <ClientInfo {...clientConfig} />
      ) : (
        <p>Could not get client info.</p>
      )}
      <h2>Auth Server Info</h2>
      {authServerConfig ? (
        <AuthServerInfo {...authServerConfig} />
      ) : (
        <p>Could not get auth server info.</p>
      )}
    </>
  );
}

export default App;
