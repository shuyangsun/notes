export function buildGetTokenURL(
  endpoint: string,
  clientId: string,
  redirectUri: string,
  state: string,
  responseType: string = 'code',
  hash: string | undefined = undefined,
) {
  const url = new URL(endpoint);
  url.search = '';
  url.searchParams.set('response_type', responseType);
  url.searchParams.set('client_id', clientId);
  url.searchParams.set('redirect_uri', redirectUri);
  url.searchParams.set('state', state);
  if (hash !== undefined) {
    url.hash = hash;
  }
  return url.toString();
}

export function encodeClientCredentials(
  clientId: string,
  clientSecret: string,
): string {
  const encoded = `${encodeURIComponent(clientId)}:${
    encodeURIComponent(clientSecret)
  }`;
  return Buffer.from(encoded).toString('base64');
}
