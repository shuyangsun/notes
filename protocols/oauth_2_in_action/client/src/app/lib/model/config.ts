export const clientBaseUri = 'http://localhost:9000';
export const authServerBaseUri = 'http://localhost:9001';
export const resourceServerBaseUri = 'http://localhost:9002';

export interface ClientConfig {
  clientId: string;
  clientSecret: string;
  authorizeEndpoint: string;
  fetchResourceEndpoint: string;
  redirectUris: string[];
}

export interface AuthServerConfig {
  authEndpoint: string;
  tokenEndpoint: string;
}

export interface ResourceServerConfig {
  resourceEndpoint: string;
}

export const clientConf: ClientConfig = {
  clientId: 'oauth-client-1',
  clientSecret: 'oauth-client-secret-1',
  authorizeEndpoint: `${clientBaseUri}/authorize`,
  fetchResourceEndpoint: `${clientBaseUri}/fetch-resource`,
  redirectUris: [`${clientBaseUri}/callback`,],
};

export const authServerConf: AuthServerConfig = {
  authEndpoint: `${authServerBaseUri}/authorize`,
  tokenEndpoint: `${authServerBaseUri}/token`,
};

export const resourceServerConf: ResourceServerConfig = {
  resourceEndpoint: `${resourceServerBaseUri}/resource`,
};
