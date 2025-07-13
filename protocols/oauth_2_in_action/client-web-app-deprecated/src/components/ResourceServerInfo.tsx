import { type ResourceServerConfig } from '../model/ResourceServerConfig';

function ResourceServerInfoList(resourceServerConfig: ResourceServerConfig) {
  const resourceUri = resourceServerConfig.resourceEndpoint;
  return (
    <ul>
      <li key={resourceUri}>
        Resource endpoint:&nbsp;
        <a href={resourceUri}>{resourceUri}</a>
      </li>
    </ul>
  );
}

export function ResourceServerInfo({
  resourceServerConfig,
}: {
  resourceServerConfig: ResourceServerConfig | undefined;
}) {
  return (
    <>
      <h2>Resource Server</h2>
      {resourceServerConfig ? (
        <ResourceServerInfoList {...resourceServerConfig} />
      ) : (
        <p className="error">Could not get resource server info.</p>
      )}
    </>
  );
}
