import { Hono } from 'hono';

const app = new Hono();

app.get('/', (c) => {
  return c.text('Hello OAuth client server!');
});

export default app;
