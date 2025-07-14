export interface TokenResponse {
  access_token: string;
  token_type: string;
  state?: string;
}

export interface ResourceResponse {
  name: string;
  description: string;
}
