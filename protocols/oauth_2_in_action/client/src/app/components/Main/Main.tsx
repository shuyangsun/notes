'use client';

import { OAuthInfo } from './OAuthInfo';
import { useSearchParams } from 'next/navigation';
import { ProtectedResourceInfo } from './ProtectedResourceInfo';

export function Main() {
  const searchParams = useSearchParams();
  const accessToken = searchParams.get('access-token');

  const protectedResource = {
    // TODO: fetch protected resource.
  };

  return (
    <main>
      <h1>OAuth 2.0 Client</h1>
      <OAuthInfo />

      {accessToken && (
        <section>
          <ProtectedResourceInfo {...protectedResource} />
        </section>
      )}
    </main>
  );
}
