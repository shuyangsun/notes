"use client";

import { OAuthInfo } from "./OAuthInfo";
import { ProtectedResourceInfo } from "./ProtectedResourceInfo";

export function Main() {
  return (
    <main>
      <h1>OAuth 2.0 Client</h1>
      <OAuthInfo />

      <ProtectedResourceInfo />
    </main>
  );
}
