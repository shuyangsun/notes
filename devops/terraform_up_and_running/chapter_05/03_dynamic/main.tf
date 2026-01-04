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

variable "custom_tags" {
  description = "Custom tags for all users."
  type        = map(string)
  default = {
    "team" : "platform",
    "owner" : "shuyangsun",
  }
}

# ------------------------------------ Main ------------------------------------

resource "aws_launch_template" "instance_template" {
  name_prefix   = "test-ec2"
  image_id      = "ami-08d7aabbb50c2c24e"
  instance_type = "t2.micro"
}

resource "aws_autoscaling_group" "asg" {
  name = "asg-test"

  min_size = 1
  max_size = 2

  launch_template {
    id = aws_launch_template.instance_template.id
  }

  dynamic "tag" {
    for_each = var.custom_tags

    content {
      key                 = tag.key
      value               = tag.value
      propagate_at_launch = true
    }
  }
}

# ---------------------------------- Outputs -----------------------------------

output "user_arns" {
  description = "ASG"
  value       = aws_autoscaling_group.asg
}
