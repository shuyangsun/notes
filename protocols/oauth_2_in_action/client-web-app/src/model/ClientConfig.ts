export interface ClientConfig {
  clientId: string;
  clientSecret: string;
  authorizeEndpoint: string;
  fetchResourceEndpoint: string;
  redirectUris: string[];
}
