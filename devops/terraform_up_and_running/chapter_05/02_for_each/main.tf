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
  default     = ["alice", "bob", "carol"]
}

variable "custom_tags" {
  description = "Custom tags for all users."
  type        = map(string)
  default = {
    "team" : "platform",
    "owner" : "shuyangsun",
  }
}

# ------------------------------------ Main ------------------------------------

resource "aws_iam_user" "users" {
  for_each = toset(var.usernames)
  name     = "test-user-${each.key}"

  tags_all = merge(
    {
      Name = "IAM user for ${each.key}"
    },
    var.custom_tags
  )
}

# ---------------------------------- Outputs -----------------------------------

output "asg_groups" {
  description = "Arns of all users"
  value       = values(aws_iam_user.users)[*].arn
}
