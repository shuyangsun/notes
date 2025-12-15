export default function Square({ value, onClick }) {
  const cursorStyle = { cursor: value === " " ? "pointer" : "not-allowed" };

  return (
    <button className="square" onClick={onClick} style={cursorStyle}>
      {value}
    </button>
  );
}
