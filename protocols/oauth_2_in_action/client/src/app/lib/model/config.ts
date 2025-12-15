const clientBaseUri = "http://localhost:9000";
const authServerBaseUri = "http://localhost:9001";
const resourceServerBaseUri = "http://localhost:9002";

export interface ClientConfig {
  baseUri: string;
  clientId: string;
  clientSecret: string;
  authorizeEndpoint: string;
  fetchResourceEndpoint: string;
  redirectUris: string[];
}

export interface AuthServerConfig {
  baseUri: string;
  authEndpoint: string;
  tokenEndpoint: string;
}

export interface ProtectedResourceServerConfig {
  baseUri: string;
  resourceEndpoint: string;
}

export interface ServerConfigs {
  clientConfig: ClientConfig;
  authServerConfig: AuthServerConfig;
  protectedResourceServerConfig: ProtectedResourceServerConfig;
}

const clientConf: ClientConfig = {
  baseUri: clientBaseUri,
  clientId: "oauth-client-1",
  clientSecret: "oauth-client-secret-1",
  authorizeEndpoint: `${clientBaseUri}/api/auth/authorize`,
  fetchResourceEndpoint: `${clientBaseUri}/api/fetch-resource`,
  redirectUris: [`${clientBaseUri}/api/auth/callback`],
};

const authServerConf: AuthServerConfig = {
  baseUri: authServerBaseUri,
  authEndpoint: `${authServerBaseUri}/authorize`,
  tokenEndpoint: `${authServerBaseUri}/token`,
};

const protectedResourceServerConf: ProtectedResourceServerConfig = {
  baseUri: resourceServerBaseUri,
  resourceEndpoint: `${resourceServerBaseUri}/resource`,
};

export const serverConfigs: ServerConfigs = {
  clientConfig: clientConf,
  authServerConfig: authServerConf,
  protectedResourceServerConfig: protectedResourceServerConf,
};
