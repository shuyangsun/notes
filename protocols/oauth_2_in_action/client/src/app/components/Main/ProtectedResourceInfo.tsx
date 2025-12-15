"use client";

import { ProtectedResource } from "@/app/lib/model/protected-resource";
import { serverConfigs } from "@/app/lib/model/config";
import { useState } from "react";

export function ProtectedResourceInfo() {
  const [data, setData] = useState<ProtectedResource | undefined>(undefined);

  async function fetchData() {
    const response = await fetch(
      serverConfigs.clientConfig.fetchResourceEndpoint,
    );

    if (!response.ok) {
      console.error("Failed to fetch:", response.status, response.statusText);
      return;
    }

    const text = await response.text();
    if (!text) {
      console.error("Empty response");
      return;
    }

    try {
      const json = JSON.parse(text) as ProtectedResource;
      setData(json);
    } catch (error) {
      console.error("Failed to parse JSON:", error);
    }
  }

  return (
    <section>
      <p>
        name: <span>{data?.name ?? "NONE"}</span>
      </p>
      <p>
        description: <span>{data?.description ?? "NONE"}</span>
      </p>
      <button onClick={fetchData}>Fetch Protected Resource</button>
    </section>
  );
}
