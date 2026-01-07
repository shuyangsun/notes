variable "vpc_id" {
  description = "VPC ID."
  type        = string
}

variable "security_group_id" {
  description = "Application load balancer security group ID."
  type        = string
}

variable "subnet_ids" {
  description = "Public subnet IDs."
  type        = list(string)
}

variable "host_port" {
  description = "App's internal hosting port on the instance."
  type        = number

}

variable "public_port" {
  description = "Public port users use to access the website."
  type        = number
}
