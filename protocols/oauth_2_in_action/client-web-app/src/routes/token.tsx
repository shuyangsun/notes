import { createFileRoute } from '@tanstack/react-router';
import { Token } from '../components/token';

export const Route = createFileRoute('/token')({
  component: Token,
});
