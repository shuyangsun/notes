[Home](../../README.md) >> [DevOps](../../README.md#devops) >> [Nginx HTTP Server](./README.md)

# [Nginx HTTP Server](devops/nginx/README.md) by Gabriel Ouiran

## Example configurations

[Core module](./examples/core_module/nginx.conf)

[Static file](./examples/static_file_server/nginx.conf)

## Build from source

> WARNING: not working yet!

[Docker file](./build_from_source/Dockerfile)

Features

| Feature       | Description    |
| ------------- | -------------- |
| `file_aio`    | Async file io. |
| `http_ssl`    |                |
| `http_v2`     |                |
| `http_v3`     |                |
| `http_gunzip` |                |

## Chapters

### 1. Downloading and Installing Nginx

If Nginx is not started with `root`, standard ports like 80 or 443 will not be accessible.

If the configuration is invalid, Nginx won't start or stop.

Use `nginx -V` to check build version and configured modules.

Use `nginx -t -c path/to/nginx.conf` to test if the configuration is valid.

### 2. Basic Nginx Configuration

Configurations are inherited within children blocks, and children blocks override parent blocks.

`include path/to/file` inserts the content of the file at the location of include.

Strings can be single or double quotes.

Variables staring with `$` will be expanded in strings, unless escaped.

Dimunitives for file size: `k` or `K`, `m` or `M`, `g` or `G`.

Dimunitives for time: `ms`, `s`, `m`, `h`, `d`, `w`, `M`, `y`.

### 3. HTTP server

Block containing order: http -> server -> location.

- `http`: Only needs one block, since later blocks overrides earlier ones.
- `server`: A website.
- `location`: A Particular URI pattern within a `server` block.
