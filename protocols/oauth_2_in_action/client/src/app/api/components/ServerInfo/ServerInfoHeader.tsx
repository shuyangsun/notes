import { ServerStatus } from '@/app/lib/model/status';
import './ServerInfoHeader.css';

interface ServerInfoHeaderProps {
  name: string;
  baseUri: string;
  status: ServerStatus;
}

export default function ServerInfoHeader({
  name,
  baseUri,
  status,
}: ServerInfoHeaderProps) {
  return (
    <>
      <div>
        <h2>{name}</h2>
        <span className={`indicator ${status}`}></span>
      </div>
      <a href={`${baseUri}/ping`}>{baseUri}</a>
    </>
  );
}
