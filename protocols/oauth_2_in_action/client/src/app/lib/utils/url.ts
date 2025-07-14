export function buildGetTokenURL(
  endpoint: string,
  clientId: string,
  redirectUri: string,
  state: string,
  responseType: string = 'code',
  hash: string | undefined = undefined,
) {
  const url = new URL(endpoint);
  url.searchParams.append('response_type', responseType);
  url.searchParams.append('client_id', clientId);
  url.searchParams.append('redirect_uri', redirectUri);
  url.searchParams.append('state', state);
  if (hash !== undefined) {
    url.hash = hash;
  }
  return url.toString();
}
