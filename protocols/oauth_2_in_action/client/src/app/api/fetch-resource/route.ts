import { NextResponse } from "next/server";
import loggerFactory from "@/app/lib/logging/logger";
import { cookies } from "next/headers";
import { serverConfigs } from "@/app/lib/model/config";
import { ProtectedResource } from "@/app/lib/model/protected-resource";

export async function GET() {
  const logger = loggerFactory.loggerForEndpoint("fetch-resource");
  logger.logDelimiterBegin();
  const cookieStore = await cookies();
  const accessToken = cookieStore.get("access_token")?.value;
  if (!accessToken) {
    return NextResponse.json({ error: "Unauthorized" }, { status: 401 });
  }
  const headers = {
    Authorization: `Bearer ${accessToken}`,
  };

  logger.log(
    `Sending POST request to protected resource server.\n  Header: ${JSON.stringify(
      headers,
    )}`,
  );
  const response = await fetch(
    serverConfigs.protectedResourceServerConfig.resourceEndpoint,
    {
      method: "POST",
      headers,
    },
  );

  if (!response.ok) {
    return NextResponse.json(
      { error: "Failed to fetch protected resource." },
      { status: response.status },
    );
  }

  const text = await response.text();
  if (!text) {
    console.error("Empty response");
    return NextResponse.json({ error: "Empty response" }, { status: 500 });
  }

  try {
    const data = JSON.parse(text) as ProtectedResource;
    logger.log(
      `Got response from protected resource server:\n  ${JSON.stringify(data)}`,
    );
    logger.logDelimiterEnd();
    return NextResponse.json(data);
  } catch {
    return NextResponse.json(
      { error: "Internal Server Error" },
      { status: 500 },
    );
  }
}
