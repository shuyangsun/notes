variable "vpc_id" {
  description = "VPC ID."
  type        = string
}

variable "internet_gateway_id" {
  description = "Internet Gateway ID for public subnet routing."
  type        = string
}

variable "num_available_zones" {
  description = "Number of availalble zones. Set to -1 to create subnets at all available zones."
  type        = number

  validation {
    condition     = var.num_available_zones > 0 || var.num_available_zones == -1
    error_message = "Number of available zones must be greater than 0 or equal to -1 (all available zones)."
  }
}
