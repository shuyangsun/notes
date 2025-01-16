FROM alpine:3.21.2 AS build

# Install dependencies.

## build dependencies
RUN apk add build-base linux-headers perl git cmake ninja

## pcre2
WORKDIR /build
RUN wget github.com/PCRE2Project/pcre2/releases/download/pcre2-10.44/pcre2-10.44.tar.gz
RUN tar -zxf pcre2-10.44.tar.gz
RUN rm pcre2-10.44.tar.gz
WORKDIR /build/pcre2-10.44
RUN ./configure
RUN make
RUN make install

## zlib
WORKDIR /build
RUN wget http://zlib.net/zlib-1.3.1.tar.gz
RUN tar -zxf zlib-1.3.1.tar.gz
RUN rm zlib-1.3.1.tar.gz
WORKDIR /build/zlib-1.3.1
RUN ./configure
RUN make
RUN make install

## openssl
# WORKDIR /build
# RUN wget http://www.openssl.org/source/openssl-3.4.0.tar.gz
# RUN tar -zxf openssl-3.4.0.tar.gz
# RUN rm openssl-3.4.0.tar.gz
# WORKDIR /build/openssl-3.4.0
# RUN ./config
# RUN make
# RUN make install

## boringssl
WORKDIR /build
RUN git clone https://boringssl.googlesource.com/boringssl
WORKDIR /build/boringssl
RUN git checkout 0.20241209.0
# RUN cmake -GNinja -B build -DCMAKE_BUILD_TYPE=Release
# RUN ninja -C build

RUN mkdir -p /build/boringssl/.openssl/lib
WORKDIR /build/boringssl/.openssl
RUN ln -s ../include include
# RUN cp /build/boringssl/build/crypto/libcrypto.a lib
# RUN cp /build/boringssl/build/ssl/libssl.a lib

# Download nginx.
WORKDIR /build
RUN wget https://nginx.org/download/nginx-1.27.3.tar.gz
RUN tar -xvzf nginx-1.27.3.tar.gz
RUN rm nginx-1.27.3.tar.gz
WORKDIR /build/nginx-1.27.3
RUN ./configure --with-threads \
    --with-file-aio \
    --with-http_ssl_module \
    --with-http_v2_module \
    --with-http_v3_module \
    --with-http_realip_module \
    --with-http_gunzip_module \
    --with-http_gzip_static_module \
    --with-http_slice_module \
    --with-http_stub_status_module \
    --with-http_sub_module \
    --without-select_module \
    --without-poll_module \
    --without-mail_pop3_module \
    --without-mail_imap_module \
    --without-mail_smtp_module \
    --with-openssl="/build/boringssl" \
    --with-openssl-opt="-I /build/boringssl/.openssl/include/ -L /build/boringssl/.openssl/lib/"\
    --with-cc-opt="-g -O3 -fPIE -fstack-protector-all -D_FORTIFY_SOURCE=2 -Wformat -Werror=format-security -I /build/boringssl/.openssl/include/" \
    --with-ld-opt="-Wl,-Bsymbolic-functions -Wl,-z,relro -L /build/boringssl/.openssl/lib/"
RUN touch "/build/boringssl/.openssl/include/openssl/ssl.h"
RUN make
RUN make install
