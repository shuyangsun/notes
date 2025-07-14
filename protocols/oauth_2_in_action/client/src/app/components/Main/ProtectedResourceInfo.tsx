import { ProtectedResource } from '@/app/lib/model/protected-resource';

export function ProtectedResourceInfo({
  name,
  description,
}: Partial<ProtectedResource>) {
  return (
    <section>
      <p>
        name: <span>{name ?? 'NONE'}</span>
      </p>
      <p>
        description: <span>{description ?? 'NONE'}</span>
      </p>
      <button
        onClick={() => (window.location.href = '/api/auth/fetch-resource')}
      >
        Fetch Protected Resource
      </button>
    </section>
  );
}
