import loggerFactory from '@/app/lib/logging/logger';
import { buildGetTokenURL, } from '@/app/lib/utils/url';
import { serverConfigs, } from '@/app/lib/model/config';

let state: string | undefined = undefined;

export function GET() {
  const logger = loggerFactory.loggerForEndpoint('authorize',);
  logger.logDelimiterBegin();
  logger.log('Send resource owner to authorization server.',);

  // Set state before sending request.
  state = Math.random().toString(36,).substring(2, 15,);

  // Send the user to the authorization server.
  const url = buildGetTokenURL(
    serverConfigs.authServerConfig.authEndpoint,
    serverConfigs.clientConfig.clientId,
    serverConfigs.clientConfig.redirectUris[0],
    state,
  );
  logger.log(
    `Redirecting user to auth server authorization endpoint:\n  ${url}`,
  );

  logger.logDelimiterEnd();
  return Response.redirect(url,);
}
