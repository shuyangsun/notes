import { NextRequest, NextResponse } from 'next/server';
import { serverConfigs } from '@/app/lib/model/config';
import { cookies } from 'next/headers';
import { encodeClientCredentials } from '@/app/lib/utils/credential';
import loggerFactory from '@/app/lib/logging/logger';

interface TokenResponse {
  access_token: string;
  token_type: string;
}

export async function GET(request: NextRequest) {
  const logger = loggerFactory.loggerForEndpoint('api/auth/callback');
  logger.logDelimiterBegin();
  logger.log(
    'Got authorization code from auth server, need to get access token now.',
  );

  const storedState = (await cookies()).get('state')?.value;
  (await cookies()).delete('state');

  const { searchParams } = new URL(request.url);
  const authState = searchParams.get('state');

  // Make sure state matches.
  if (authState !== storedState) {
    logger.log('!ERROR! state values did not match.');
    logger.logDelimiterEnd();
    return new NextResponse('Unauthorized, state does not match', {
      status: 401,
    });
  }
  logger.log(`state values ("${authState}") matched.`);

  // Make sure the authorization code from auth server is present.
  const code = searchParams.get('code');
  if (!code) {
    logger.log('!ERROR! auth server did not provide authorization code.');
    return new NextResponse('Missing authorization code', { status: 400 });
  }
  logger.log(`auth server returned authorization code "${code}"`);

  const clientConfig = serverConfigs.clientConfig;
  const formData = new URLSearchParams({
    grant_type: 'authorization_code',
    code: code,
    redirect_uri: clientConfig.redirectUris[0],
  });
  const credentials = encodeClientCredentials(
    clientConfig.clientId,
    clientConfig.clientSecret,
  );
  const headers = {
    'Content-Type': 'application/x-www-form-urlencoded',
    Authorization: `Basic ${credentials}`,
  };
  logger.log(
    `encoded client ID "${clientConfig.clientId}" and client secret "${clientConfig.clientSecret}" for Authorization header.`,
  );

  logger.log(
    `sending POST request to auth server token endpoint:\n  Header: ${
      JSON.stringify(headers)
    }\n  Body: ${formData.toString()}`,
  );

  const authServerConfig = serverConfigs.authServerConfig;
  const response = await fetch(authServerConfig.tokenEndpoint, {
    method: 'POST',
    headers,
    body: formData.toString(),
  });

  const data = (await response.json()) as TokenResponse;
  logger.log(
    `Got access token from auth server:\n  token_type: ${data.token_type}\n  access_token: ${data.access_token}`,
  );

  const tokenUrl = new URL(clientConfig.baseUri);
  tokenUrl.searchParams.append('token-type', data.token_type);
  tokenUrl.searchParams.append('access-token', data.access_token);

  logger.log(
    `Redirecting user to display access token.\n  DO NOT DO THIS IN A REAL CLIENT! Token should be opaque from the client, and it should be securely stored as a secret.\n  Redirect URL: ${tokenUrl}`,
  );
  logger.logDelimiterEnd();
  return Response.redirect(tokenUrl);
}
