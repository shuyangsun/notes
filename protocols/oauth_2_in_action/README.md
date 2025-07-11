[Home](../../README.md) >> [Protocols](../../README.md#protocols) >> [OAuth 2 in Action](./README.md)

# OAuth 2 in Action by [Justin Richer](https://www.manning.com/authors/justin-richer) and [Antonio Sanso](https://www.manning.com/authors/antonio-sanso)

## Chapter 1. What is OAuth 2.0 and why should you care?

OAuth 2.0 is a delegation protocol, it allows a software application to access certain resources on behalf of the resource owner without having to impersinating them. It does so by either orchestrating an approval interaction between the resource owner and the HTTP service, or by allowing third-party applications to obtain access on its own behalf.

Even though authentication methods can be built on top of the OAuth protocol, the protocol itself is not authentication protocol (are you who you say you are?), an authorization protocol (access to resource).

### Terminologies

- _Resource Owner_: entity with access to resource, usually a person.
- _Protected Resource_: the resource _Resource Owner_ has access to.
- _Client_: software that accesses the protected resource on behalf of the resource owner.
- _Scope_: a set of rights at a protected resoure represented by a space-separated list in string format.

### Key points

- OAuth is about how to get a token and how to use a token.
- OAuth doesn't define a token format, the content of the token is completely opaque to the client application.
- OAuth 2.0 defines no cryptographic methods (unlike OAuth 1.0).

## Chapter 2. The OAuth dance

### Overview

1. The _Resource Owner_ indicates to the _Client_ for delegation (e.g., fetch my photos from iCloud).
1. The _Client_ requets authorization from the _Resource Owner_ at the _Authorization Server_.
1. The _Resource Owner_ grants authorization to the _Client_.
1. The _Client_ receives a Token from the _Authorization Server_.
1. The _Client_ presents the Token to the _Protected Resource_.

The client is generally the simplest component. The token is a blackbox string to the client, the client doesn't have to understand the token, nor should it ever need to inspect the token's contents.

_The auth server authenticates both the client and the resource owner,_ then it provide mechanisms for the resource owner to authorize the client.

The client is generally the simplest component. The token is a blackbox string to the client, the client doesn't have to understand the token, nor should it ever need to inspect the token's contents.

_The auth server authenticates both the client and the resource owner,_ then it provide mechanisms for the resource owner to authorize the client.

In OAuth 2.0, the refresh token replaces long-lived token, which was a common bad practice.

## Chapter 3. Building a simple OAuth client

The _Authorization Code_ grant type sends the resource owner to authorization server's authorization endpoint. It is the most fundamental and complex core grant type, all other grant types are optimizations of this one.
