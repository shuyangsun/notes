variable "security_group_ids" {
  description = "List of security group IDs."
  type        = list(string)
}

variable "instance_type" {
  description = "EC2 instance type."
  type        = string
}

variable "ami" {
  description = "AMI image ID."
  type        = string
}

variable "server_port" {
  description = "EC2 instance hosting port."
  type        = number
}

variable "page_title" {
  description = "Title text on the index HTML page."
  type        = string
}
