variable "launch_template_id" {
  description = "AWS launch template ID."
  type        = string
}

variable "min_size" {
  description = "Minimum number of instances."
  type        = number

  validation {
    condition     = var.min_size > 0
    error_message = "Minimum size must be greater than 0."
  }
}

variable "max_size" {
  description = "Maximum number of instances."
  type        = number

  validation {
    condition     = var.max_size >= var.min_size
    error_message = "Maximum size (${var.max_size}) must be greater than or equal to the minimum size (${var.min_size})."
  }
}

variable "subnet_ids" {
  description = "VPC subnet IDs."
  type        = list(string)
}

variable "target_group_arns" {
  description = "Target group ARNs to register with this ASG."
  type        = list(string)
}
