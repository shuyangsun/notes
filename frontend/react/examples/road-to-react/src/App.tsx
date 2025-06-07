import './App.css';

import { Header } from './components/Header';
import { Main } from './components/Main';
import { logRender } from './util/log';

function App() {
  logRender('App');
  return (
    <>
      <Header />
      <Main />
    </>
  );
}

export default App;
