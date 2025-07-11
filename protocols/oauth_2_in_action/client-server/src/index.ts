import { Hono } from 'hono';
import { cors } from 'hono/cors';

const app = new Hono();

app.use(
  '/*',
  cors({
    origin: (origin) => {
      if (!origin) return origin;
      const url = new URL(origin);
      if (url.hostname === 'localhost' || url.hostname === '127.0.0.1') {
        return origin;
      }
      return null;
    },
    allowHeaders: ['X-Custom-Header', 'Upgrade-Insecure-Requests'],
    allowMethods: ['GET', 'POST'],
    exposeHeaders: ['Content-Length', 'X-Kuma-Revision'],
    maxAge: 600,
    credentials: true,
  })
);

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

app.get('/ping', (c) => {
  return c.text('pong');
});

app.get('/server-config', (c) => {
  return c.json({
    client: clientConf,
    auth: authServerConf,
  });
});

export default app;
