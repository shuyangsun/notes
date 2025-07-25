import { Hono } from 'hono';
import { cors } from 'hono/cors';
import { buildGetTokenURL, encodeClientCredentials } from './helper';
import { LoggerFactory } from './logging';

const clientWebAppBaseUri = 'http://localhost:5173';
const clientBaseUri = 'http://localhost:9000';
const authServerBaseUri = 'http://localhost:9001';
const resourceServerBaseUri = 'http://localhost:9002';

const loggerFactory = new LoggerFactory('CLIENT');

let state: string | undefined = undefined;
let accessToken: string | undefined = undefined;

interface ClientConfig {
  clientId: string;
  clientSecret: string;
  authorizeEndpoint: string;
  fetchResourceEndpoint: string;
  redirectUris: string[];
}

interface AuthServerConfig {
  authEndpoint: string;
  tokenEndpoint: string;
}

interface ResourceServerConfig {
  resourceEndpoint: string;
}

interface TokenResponse {
  access_token: string;
  token_type: string;
  state?: string;
}

interface ResourceResponse {
  name: string;
  description: string;
}

const clientConf: ClientConfig = {
  clientId: 'oauth-client-1',
  clientSecret: 'oauth-client-secret-1',
  authorizeEndpoint: `${clientBaseUri}/authorize`,
  fetchResourceEndpoint: `${clientBaseUri}/fetch-resource`,
  redirectUris: [`${clientBaseUri}/callback`],
};

const authServerConf: AuthServerConfig = {
  authEndpoint: `${authServerBaseUri}/authorize`,
  tokenEndpoint: `${authServerBaseUri}/token`,
};

const resourceServerConf: ResourceServerConfig = {
  resourceEndpoint: `${resourceServerBaseUri}/resource`,
};

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

app.get('/ping', (c) => {
  return c.text('pong');
});

app.get('/server-config', (c) => {
  return c.json({
    client: clientConf,
    auth: authServerConf,
    resource: resourceServerConf,
  });
});

app.get('/authorize', (c) => {
  const logger = loggerFactory.loggerForEndpoint('authorize');
  logger.logDelimiterBegin();
  logger.log('Send resource owner to authorization server.');

  // Set state before sending request.
  state = Math.random().toString(36).substring(2, 15);

  // Send the user to the authorization server.
  const url = buildGetTokenURL(
    authServerConf.authEndpoint,
    clientConf.clientId,
    clientConf.redirectUris[0],
    state
  );
  logger.log(`Redirecting user to auth server authorization endpoint:\n  ${url}`);
  logger.logDelimiterEnd();
  return c.redirect(url);
});

app.get('/callback', async (c) => {
  const logger = loggerFactory.loggerForEndpoint('callback');
  logger.logDelimiterBegin();
  logger.log('Got authorization code from auth server, need to get access token now.');

  // Make sure state matches.
  if (c.req.query('state') !== state) {
    logger.log('!ERROR! state values did not match.');
    return c.text('Unauthorized, state does not match', 401);
  }
  logger.log(`state values ("${state}") matched.`);

  // Make sure the authorization code from auth server is present.
  const code = c.req.query('code');
  if (!code) {
    logger.log('!ERROR! auth server did not provide authorization code.');
    return c.text('Missing authorization code', 400);
  }
  logger.log(`auth server returned authorization code "${code}"`);

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
  logger.log(
    `encoded client ID "${clientConf.clientId}" and client secret "${clientConf.clientSecret}" for Authorization header.`
  );

  logger.log(
    `sending POST request to auth server token endpoint:\n  Header: ${JSON.stringify(headers)}\n  Body: ${formData.toString()}`
  );
  const response = await fetch(authServerConf.tokenEndpoint, {
    method: 'POST',
    headers,
    body: formData.toString(),
  });

  const data = (await response.json()) as TokenResponse;
  logger.log(
    `Got access token from auth server:\n  token_type: ${data.token_type}\n  access_token: ${data.access_token}`
  );
  accessToken = data.access_token;

  const tokenDisplayURL = `${clientWebAppBaseUri}/tokens/${encodeClientCredentials(`${data.token_type} `, data.access_token)}`;
  logger.log(
    `Redirecting user to display access token.\n  DO NOT DO THIS IN A REAL CLIENT! Token should be opaque from the client, and it should be securely stored as a secret.\n  Redirect URL: ${tokenDisplayURL}`
  );
  logger.logDelimiterEnd();
  // Do NOT expose tokens! This is a terrible security practice.
  return c.redirect(tokenDisplayURL);
});

app.get('/fetch-resource', async (c) => {
  const logger = loggerFactory.loggerForEndpoint('fetch-resource');
  logger.logDelimiterBegin();
  const headers = {
    Authorization: `Bearer ${accessToken}`,
  };

  logger.log(
    `Sending POST request to protected resource server.\n  Header: ${JSON.stringify(headers)}`
  );
  const response = await fetch(resourceServerConf.resourceEndpoint, {
    method: 'POST',
    headers,
  });
  const data = (await response.json()) as ResourceResponse;
  logger.log(`Got response from protected resource server:\n  ${JSON.stringify(data)}`);
  logger.logDelimiterEnd();
  return c.json(data);
});

export default app;
