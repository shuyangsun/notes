variable "environment" {
  type        = string
  description = "Production, staging, or dev environment."

  validation {
    condition     = contains(["dev", "staging", "prod"], var.environment)
    error_message = "Environment \"${var.environment}\" is not one of \"dev\", \"staging\", or \"prod\"."
  }
}

variable "app_name" {
  type        = string
  description = "Name of the application, usually in lowercase separated by hyphens."
  default     = "terraform-asg-example"
}

variable "server_port" {
  description = "The port number to receive HTTP requests."
  type        = number
  default     = 8080
}
