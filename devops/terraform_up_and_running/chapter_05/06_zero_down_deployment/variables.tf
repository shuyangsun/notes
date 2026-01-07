variable "public_port" {
  description = "Public port for HTTP access."
  type        = number
  default     = 80
}

variable "hosting_port" {
  description = "Internal server app hosting port"
  type        = number
  default     = 8080
}
