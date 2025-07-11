import { useState, useEffect } from 'react';
import { EndpointStatus } from './EndpointStatus';
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

async function checkServerStatus(uri: string) {
  try {
    const response = await fetch(`${uri}/ping`);
    return response.ok;
  } catch {
    return false;
  }
}

function App() {
  const clientInfoEndpoint = 'http://localhost:9000/client-info';
  const authServerInfoEndpoint = 'http://localhost:9000/auth-server-info';

  const [clientConfig, setClientConfig] = useState<ClientConfig | undefined>(
    undefined
  );
  const [authServerConfig, setAuthServerConfig] = useState<
    AuthServerConfig | undefined
  >(undefined);
  const [serverStatus, setServerStatus] = useState<Record<string, boolean>>({});

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

  useEffect(() => {
    const pingServers = async () => {
      const allUrisSet = new Set<string>([
        new URL(clientInfoEndpoint).origin,
        new URL(authServerInfoEndpoint).origin,
      ]);
      if (authServerConfig !== undefined) {
        allUrisSet.add(new URL(authServerConfig.authEndpoint).origin);
        allUrisSet.add(new URL(authServerConfig.tokenEndpoint).origin);
      }
      try {
        for (const uri of clientConfig?.redirectUris ?? []) {
          allUrisSet.add(new URL(uri).origin);
        }
      } catch (error) {
        console.log(`Error creating URI: ${String(error)}`);
      }

      const statusUpdates: Record<string, boolean> = {};
      for (const uri of allUrisSet) {
        statusUpdates[uri] = await checkServerStatus(uri);
        console.log(`ASDF: ${uri}: ${statusUpdates[uri]}`);
      }
      setServerStatus(statusUpdates);
    };

    const interval = setInterval(pingServers, 5000);
    void pingServers();

    return () => clearInterval(interval);
  }, [clientConfig, authServerConfig]);

  return (
    <>
      <h1>OAuth 2.0 Web Client</h1>
      <h2>Server Status</h2>
      <ul>
        {Object.entries(serverStatus).map(([uri, isOnline]) => {
          return (
            <li key={uri}>
              <EndpointStatus uri={uri} online={isOnline} />
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
