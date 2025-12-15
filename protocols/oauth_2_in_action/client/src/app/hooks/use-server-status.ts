import { useEffect, useState } from "react";
import { ServerStatus } from "../lib/model/status";

export default function useServerStatus(pingEndpoint: string): ServerStatus {
  const [status, setStatus] = useState<ServerStatus>("unknown");

  useEffect(() => {
    let isMounted = true;
    const checkStatus = async () => {
      try {
        const res = await fetch(pingEndpoint);
        if (isMounted) {
          setStatus(res.ok ? "online" : "offline");
        }
      } catch {
        if (isMounted) {
          setStatus("offline");
        }
      }
    };

    void checkStatus();
    const interval = setInterval(checkStatus, 5000);

    return () => {
      isMounted = false;
      clearInterval(interval);
    };
  }, [pingEndpoint]);

  return status;
}
