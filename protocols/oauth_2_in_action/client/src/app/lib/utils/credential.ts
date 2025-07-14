export function encodeClientCredentials(
  clientId: string,
  clientSecret: string,
): string {
  const encoded = `${encodeURIComponent(clientId,)}:${
    encodeURIComponent(clientSecret,)
  }`;
  return Buffer.from(encoded,).toString('base64',);
}
