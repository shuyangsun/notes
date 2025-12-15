import { buildGetTokenURL } from "@/app/lib/utils/url";
import { serverConfigs } from "@/app/lib/model/config";
import { NextResponse } from "next/server";
import { cookies } from "next/headers";

import loggerFactory from "@/app/lib/logging/logger";

const { randomBytes } = await import("node:crypto");

let state: string | undefined = undefined;

export async function GET() {
  const logger = loggerFactory.loggerForEndpoint("api/auth/authorize");
  logger.logDelimiterBegin();
  logger.log("Send resource owner to authorization server.");

  // Set state before sending request.
  state = randomBytes(32).toString("base64url");
  (await cookies()).set("state", state, {
    httpOnly: true,
    secure: true,
    sameSite: "lax",
    maxAge: 60, // 1 minute
    path: "/",
  });

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
  return NextResponse.redirect(url);
}
