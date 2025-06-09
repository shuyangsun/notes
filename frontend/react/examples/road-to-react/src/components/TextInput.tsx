import React, { useRef, useEffect } from 'react';
import { logRender } from '../util/log';

interface Props {
  id: string;
  placeholder: string;
  text: string;
  type: string;
  isFocused: boolean;
  onValueChange: (event: React.ChangeEvent<HTMLInputElement>) => void;
  children?: React.ReactNode;
}

export function TextInput({
  id,
  placeholder,
  text,
  type,
  isFocused,
  onValueChange,
  children,
}: Props) {
  logRender('TextInput');
  const inputRef = useRef<HTMLInputElement | null>(null);

  useEffect(() => {
    if (isFocused && inputRef.current) {
      inputRef.current?.focus();
    }
  }, [isFocused]);
  return (
    <>
      <label htmlFor={id}>{children}</label>
      &nbsp;
      <input
        ref={inputRef}
        id={id}
        type={type}
        placeholder={placeholder}
        value={text}
        onChange={onValueChange}
      ></input>
    </>
  );
}
