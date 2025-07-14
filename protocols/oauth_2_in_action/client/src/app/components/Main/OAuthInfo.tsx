'use client';

import { useSearchParams } from 'next/navigation';

export function OAuthInfo() {
  const searchParams = useSearchParams();
  const tokenType = searchParams.get('token-type');
  const accessToken = searchParams.get('access-token');
  const refreshToken = searchParams.get('refresh-token');

  return (
    <section>
      <p>
        Token type: <span>{tokenType ?? 'NONE'}</span>
      </p>
      <p>
        Access token: <span>{accessToken ?? 'NONE'}</span>
      </p>
      <p>
        Refresh token: <span>{refreshToken ?? 'NONE'}</span>
      </p>
      <p>
        Scope: <span>NONE</span>
      </p>
      <button onClick={() => (window.location.href = '/api/auth/authorize')}>
        Get Access Token
      </button>
    </section>
  );
}
