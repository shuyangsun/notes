import type { AuthServerConfig } from './AuthServerConfig';
import type { ClientConfig } from './ClientConfig';

export interface ServerConfigResponse {
  client: ClientConfig;
  auth: AuthServerConfig;
}
