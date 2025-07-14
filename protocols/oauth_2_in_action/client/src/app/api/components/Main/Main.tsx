'use client';

import { OAuthInfo } from './OAuthInfo';

export function Main() {
  return (
    <main>
      <h1>OAuth 2.0 Client</h1>
      <OAuthInfo />
      <button onClick={() => (window.location.href = '/api/auth/authorize')}>
        Get Access Token
      </button>
    </main>
  );
}
