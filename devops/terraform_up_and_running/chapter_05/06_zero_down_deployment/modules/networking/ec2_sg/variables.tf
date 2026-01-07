variable "vpc_id" {
  description = "VPC ID."
  type        = string
}

variable "host_port" {
  description = "Internal web server hosting port."
  type        = number
}

variable "ingress_security_group_id" {
  description = "The security group to allow ingress traffic from."
  type        = string
}
