import Square from "./Square";
import React, { useState } from "react";

function calculateWinner(squares) {
  const lines = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];
  for (let i = 0; i < lines.length; i++) {
    const [a, b, c] = lines[i];
    if (
      squares[a] != " " &&
      squares[a] &&
      squares[a] === squares[b] &&
      squares[a] === squares[c]
    ) {
      return squares[a];
    }
  }
  return null;
}

export default function Board() {
  const [values, setValues] = useState(Array(9).fill(" "));
  const [turn, setTurn] = useState("O");

  function onClick(idx) {
    return function () {
      if (values[idx] !== " " || calculateWinner(values)) {
        return;
      }
      setValues(values.map((value, index) => (index === idx ? turn : value)));
      setTurn(turn === "O" ? "X" : "O");
    };
  }

  const winner = calculateWinner(values);
  let status;
  if (winner) {
    status = "Winner: " + winner;
  } else {
    status = "Next player: " + turn;
  }

  return (
    <>
      <div className="status">{status}</div>
      <div className="board-row">
        <Square value={values[0]} onClick={onClick(0)} />
        <Square value={values[1]} onClick={onClick(1)} />
        <Square value={values[2]} onClick={onClick(2)} />
      </div>
      <div className="board-row">
        <Square value={values[3]} onClick={onClick(3)} />
        <Square value={values[4]} onClick={onClick(4)} />
        <Square value={values[5]} onClick={onClick(5)} />
      </div>
      <div className="board-row">
        <Square value={values[6]} onClick={onClick(6)} />
        <Square value={values[7]} onClick={onClick(7)} />
        <Square value={values[8]} onClick={onClick(8)} />
      </div>
    </>
  );
}
