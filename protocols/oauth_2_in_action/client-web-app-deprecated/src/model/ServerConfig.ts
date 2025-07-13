import type { AuthServerConfig } from './AuthServerConfig';
import type { ClientConfig } from './ClientConfig';
import type { ResourceServerConfig } from './ResourceServerConfig';

export interface ServerConfigResponse {
  client: ClientConfig;
  auth: AuthServerConfig;
  resource: ResourceServerConfig;
}
