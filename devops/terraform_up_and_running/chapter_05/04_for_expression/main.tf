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
  region  = "us-east-1"
  profile = "shuyang"
}

# --------------------------------- Variables ----------------------------------

variable "usernames" {
  description = "All usernames"
  type        = list(string)
  default     = ["Alice", "Bob", "Carol"]
}

locals {
  names_upper = [for name in var.usernames : lower(name)]
}


# ------------------------------------ Main ------------------------------------

resource "aws_iam_user" "users" {
  for_each = toset(local.names_upper)
  name     = "test-user-${each.key}"
}

# ---------------------------------- Outputs -----------------------------------

output "users" {
  description = "User names."
  value       = values(aws_iam_user.users)[*].name
}
