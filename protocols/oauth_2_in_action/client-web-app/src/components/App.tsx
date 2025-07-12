import { useServerConfig, serverConfigEndpoint } from '../model/ServerConfig';
import { Header } from './Header';
import './App.css';

export function App() {
  const serverConfig = useServerConfig(serverConfigEndpoint);

  return (
    <>
      <h1>OAuth 2.0 Web Client</h1>

      {serverConfig ? (
        <Header serverConfig={serverConfig} />
      ) : (
        <p className="error">Error fetching server config.</p>
      )}

      <main>
        <a href="http://localhost:9000/authorize">Get Access Token</a>
      </main>
    </>
  );
}

export default App;
