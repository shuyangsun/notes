import { Hono } from 'hono';

const app = new Hono();

interface ClientConfig {
  clientId: string;
  clientSecret: string;
  redirectUris: string[];
}

interface AuthServerConfig {
  authEndpoint: string;
  tokenEndpoint: string;
}

const clientConf: ClientConfig = {
  clientId: 'oauth-client-1',
  clientSecret: 'oauth-client-secret-1',
  redirectUris: ['http://localhost:9000/callback'],
};

const authServerConf: AuthServerConfig = {
  authEndpoint: 'http://localhost:9001/authorize',
  tokenEndpoint: 'http://localhost:9001/token',
};

app.get('/client-info', (c) => {
  return c.json(clientConf);
});

app.get('/auth-server-info', (c) => {
  return c.json(authServerConf);
});

export default app;
