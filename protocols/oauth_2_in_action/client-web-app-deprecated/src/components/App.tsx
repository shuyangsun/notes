import { Header } from './Header';
import { useServerConfig } from '../stores/serverStatus';

import './App.css';

export function App() {
  const serverConfig = useServerConfig();
  return (
    <>
      <h1>OAuth 2.0 Web Client</h1>

      <Header />

      <main>
        <a
          href={serverConfig ? serverConfig.client.authorizeEndpoint : '/error'}
          className={serverConfig ? '' : 'hidden'}
        >
          Get Access Token
        </a>
      </main>
    </>
  );
}

export default App;
