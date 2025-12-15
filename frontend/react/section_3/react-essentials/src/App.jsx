function Header({ startWord }) {
  return (
    <header>
      <img src="src/assets/react-core-concepts.png" alt="Stylized atom" />
      <h1>React Essentials</h1>
      <p>
        {startWord} React concepts you will need for almost any app you are
        going to build!
      </p>
    </header>
  );
}

function App() {
  return (
    <div>
      <Header startWord={"Core"} />
      <main>
        <h2>Time to get started!</h2>
      </main>
    </div>
  );
}

export default App;
