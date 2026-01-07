variable "vpc_id" {
  description = "VPC ID."
  type        = string
}

variable "public_port" {
  description = "Public port LB is listenin on, defaults to 80."
  type        = number
}
