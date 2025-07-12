import { Hono } from 'hono';
import { cors } from 'hono/cors';
import { buildGetTokenURL, encodeClientCredentials } from './helper';

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

interface TokenResponse {
  access_token: string;
  token_type: string;
  state?: string;
}

const clientWebAppBaseUri = 'http://localhost:5173';
const clientBaseUri = 'http://localhost:9000';
const authServerBaseUri = 'http://localhost:9001';

let state: string | undefined = undefined;

const clientConf: ClientConfig = {
  clientId: 'oauth-client-1',
  clientSecret: 'oauth-client-secret-1',
  redirectUris: [`${clientBaseUri}/callback`],
};

const authServerConf: AuthServerConfig = {
  authEndpoint: `${authServerBaseUri}/authorize`,
  tokenEndpoint: `${authServerBaseUri}/token`,
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

app.get('/authorize', (c) => {
  state = Math.random().toString(36).substring(2, 15);
  // Send the user to the authorization server.
  const url = buildGetTokenURL(
    authServerConf.authEndpoint,
    clientConf.clientId,
    clientConf.redirectUris[0],
    state
  );
  console.log(`Auth URL: ${url}`);
  return c.redirect(url);
});

app.get('/callback', async (c) => {
  // Parse the response from the authorization server and get a token.
  console.log(`ASDF: ${c.req}`);
  const code = c.req.query('code');
  if (!code) {
    return c.text('Missing authorization code', 400);
  }
  if (c.req.query('state') !== state) {
    return c.text('Unauthorized, state does not match', 401);
  }
  const formData = new URLSearchParams({
    grant_type: 'authorization_code',
    code: code,
    redirect_uri: clientConf.redirectUris[0],
  });
  const credentials = encodeClientCredentials(clientConf.clientId, clientConf.clientSecret);
  const headers = {
    'Content-Type': 'application/x-www-form-urlencoded',
    Authorization: `Basic ${credentials}`,
  };

  const response = await fetch(authServerConf.tokenEndpoint, {
    method: 'POST',
    headers,
    body: formData.toString(),
  });

  const data = (await response.json()) as TokenResponse;
  // Do NOT expose tokens! This is a terrible security practice.
  return c.redirect(
    `${clientWebAppBaseUri}/tokens/${encodeClientCredentials(`${data.token_type} `, data.access_token)}`
  );
});

app.get('/fetch-resource', (c) => {
  // Use the access token to call the resource server.
  return c.json({});
});

export default app;
