import { NextRequest, NextResponse } from "next/server";
import { serverConfigs } from "@/app/lib/model/config";
import { cookies } from "next/headers";
import { buildAuthHeaders } from "@/app/lib/utils/credential";
import loggerFactory from "@/app/lib/logging/logger";

interface TokenResponse {
  access_token: string;
  token_type: string;
}

interface CallbackArguments {
  authorizationCode: string | undefined;
}

async function parseCallbackRequest(
  req: NextRequest,
): Promise<[CallbackArguments, ResponseError[]]> {
  const errors: ResponseError[] = [];

  const storedState = (await cookies()).get("state")?.value;
  (await cookies()).delete("state");

  const { searchParams } = new URL(req.url);
  const authState = searchParams.get("state");

  // Make sure state matches.
  if (authState !== storedState) {
    errors.push({
      message: "unauthorized, state does not match.",
      status: 401,
    });
  }

  // Make sure the authorization code from auth server is present.
  const code = searchParams.get("code");
  if (!code) {
    errors.push({
      message: "auth server did not provide authorization code",
      status: 400,
    });
  }
  return [{ authorizationCode: code ?? undefined }, errors];
}

export async function GET(request: NextRequest) {
  const logger = loggerFactory.loggerForEndpoint("api/auth/callback");
  logger.logDelimiterBegin();
  logger.log(
    "Got authorization code from auth server, need to get access token now.",
  );

  const errors = await parseCallbackRequest(request);
  if (errors) {
    const errorMessages = errors.map((err) => err.message);
    logger.log(`!ERROR!\n  ${errorMessages.join("  \n")}`);
    logger.logDelimiterEnd();
    return new NextResponse(errorMessages.join("\n"), {
      status: errors[0].status,
    });
  }

  logger.log(`auth server returned authorization code "${code}"`);

  const clientConfig = serverConfigs.clientConfig;
  const formData = new URLSearchParams({
    grant_type: "authorization_code",
    code: code,
    redirect_uri: clientConfig.redirectUris[0],
  });
  const headers = buildAuthHeaders(
    clientConfig.clientId,
    clientConfig.clientSecret,
  );
  logger.log(
    `encoded client ID "${clientConfig.clientId}" and client secret "${clientConfig.clientSecret}" for Authorization header.`,
  );
  logger.log(
    `sending POST request to auth server token endpoint:\n  Header: ${JSON.stringify(
      headers,
    )}\n  Body: ${formData.toString()}`,
  );

  const authServerConfig = serverConfigs.authServerConfig;
  const response = await fetch(authServerConfig.tokenEndpoint, {
    method: "POST",
    headers,
    body: formData.toString(),
  });

  const data = (await response.json()) as TokenResponse;
  logger.log(`Got tokens from auth server:\n  ${JSON.stringify(data)}`);

  const cookieStore = await cookies();
  cookieStore.set("access_token", data.access_token, {
    httpOnly: true,
    secure: true,
    sameSite: "strict",
    path: "/",
  });
  cookieStore.set("token_type", data.token_type, {
    httpOnly: true,
    secure: true,
    sameSite: "strict",
    path: "/",
  });

  logger.log(
    `Redirecting user to display access token.\n  DO NOT DO THIS IN A REAL CLIENT! Token should be opaque from the client, and it should be securely stored as a secret.\n  Redirect URL: ${clientConfig.baseUri}`,
  );
  logger.logDelimiterEnd();
  return Response.redirect(clientConfig.baseUri);
}
