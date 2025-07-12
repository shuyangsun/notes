import { createFileRoute, type FileRoutesByPath } from '@tanstack/react-router';
import { Token } from '../components/Token';

export const Route = createFileRoute(
  '/tokens/$token' as keyof FileRoutesByPath
)({
  component: Component,
});

function Component() {
  const { token }: { token: string } = Route.useParams();
  return Token({ token: token });
}
