export function encodeClientCredentials(
  clientId: string,
  clientSecret: string,
): string {
  const encoded = `${encodeURIComponent(clientId)}:${encodeURIComponent(
    clientSecret,
  )}`;
  return Buffer.from(encoded).toString('base64');
}

export function buildAuthHeaders(
  clientId: string,
  clientSecret: string,
): Record<string, string> {
  const credentials = encodeClientCredentials(clientId, clientSecret);
  return {
    'Content-Type': 'application/x-www-form-urlencoded',
    Authorization: `Basic ${credentials}`,
  };
}
