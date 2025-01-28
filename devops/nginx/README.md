[Home](../../README.md) >> [DevOps](../../README.md#devops) >> [Nginx HTTP Server](./README.md)

# [Nginx HTTP Server](devops/nginx/README.md) by Gabriel Ouiran

## Example configurations

[Core module](./examples/base_module/nginx.conf)

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

### 3. Exploring the HTTP configuration

Block containing order: `http` -> `server` -> `location`.

- `http`: Only needs one block, since later blocks overrides earlier ones.
- `server`: A virtual host (website) identified by either hostname or IP address and port combination.
- `location`: A Particular URI pattern within a `server` block.

#### 3.1 Directives

`server_name`

Assigns one or more hostnames to the `server` block. When Nginx receives an HTTP request, it matches the host header of the request against all `server` blocks. The first `server` block to match this hostname is selected.

If no server block matches the desired host, Nginx selects the first `server` block that matches the parameters of the `listen` directive, giving priority to the `default_server`.

`server_names_in_redirect`

Applies to internal redirects. If set to `on`, uses `server_name` for redirects; if `off`, use `Host` header. Default `off`.

`index`

List of index pages to serve if file is not specified in the request, first match is served. Absolute path starting with `/` can only be the last argument.

`error_page`

Specify error page for error code, optionally changing error code in response.

`keepalive_requests`

Max number of requets a single keep-alive connection can serve. Default value is `100`.

#### 3.2 Location block

Syntax: `location [=|~|~*|^~|@] pattern { ... }`

| Modifier     | Description                                                   |
| ------------ | ------------------------------------------------------------- |
| No modifier. | Begins with.                                                  |
| `=`          | Exact.                                                        |
| `~`          | Regex.                                                        |
| `~*`         | Regex (case-insensitive).                                     |
| `^~`         | Begins with, and stops searching. Order matters for this one. |
| `@`          | Named location block.                                         |

Matching order and priority:

1. `=` - try exact matches.
2. None - try exact matches (without modifier).
3. `^~` - try begin with matches, ignores the rest if found.
4. `~` - try regex mathces.
5. `~*` - try case-insensitive regex mathces.
6. None - try begin with matches.

### 4. Exploring Module Configuration

#### 4.1 Rewrite module

The `error_page` and `index` directives generate internal redirects, they do not just simply serve the page.

It's possible to have recursive internal redirects, but the maximum recursion depth is 10.

Conditional structure examples:

```
if ($request_method = POST) {
  # ...
}

if ($request_method != GET) {
  # ...
}

if ($string) {
  # Not empty and not starting with character `0`.
}

if ($request_filename !~ "^.*txt$") {
  # If is not requesting JavaScript file.
}

if (-f $request_filename) {
  # If file exists.
}

if (!-f $request_filename) {
  # If file does not exist.
}

if (-e $request_path) {
  # If file, directory or symbolic link exists.
}

if (-x $request_file) {
  # If exists and is executable.
}
```
