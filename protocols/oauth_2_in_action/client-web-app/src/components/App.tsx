import { Header } from './Header';
import './App.css';

export function App() {
  return (
    <>
      <h1>OAuth 2.0 Web Client</h1>

      <Header />

      <main>
        <a href="http://localhost:9000/authorize">Get Access Token</a>
      </main>
    </>
  );
}

export default App;
