# --------------------------------- Providers ----------------------------------

terraform {
  required_version = "~> 1.14.3"

  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 6.27.0"
    }
  }
}

provider "aws" {
  region = "us-east-1"
}

# --------------------------------- Variables ----------------------------------

variable "user_count" {
  description = "Number of IAM users to create."
  type        = number
  default     = 3
}

# ------------------------------------ Main ------------------------------------

resource "aws_iam_user" "users" {
  count = var.user_count
  name  = "test-user-${count.index}"
}

# ---------------------------------- Outputs -----------------------------------

output "user_arns" {
  description = "Arns of all users"
  value       = aws_iam_user.users[*].arn
}
