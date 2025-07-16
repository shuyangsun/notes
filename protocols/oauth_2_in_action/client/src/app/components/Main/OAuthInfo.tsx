'use client';

export function OAuthInfo() {
  const cookies = typeof window !== 'undefined'
    ? document.cookie.split('; ')
    : [];
  const accessToken = cookies
    .find((row) => row.startsWith('access_token='))
    ?.split('=')[1];
  const tokenType = cookies
    .find((row) => row.startsWith('token_type='))
    ?.split('=')[1];
  const refreshToken = cookies
    .find((row) => row.startsWith('refresh_token='))
    ?.split('=')[1];

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
