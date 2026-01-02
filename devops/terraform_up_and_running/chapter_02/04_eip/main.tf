terraform {
  required_version = "~> 1.14.1"

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

resource "aws_instance" "ec2" {
  ami           = "ami-0ecb62995f68bb549"
  instance_type = "t2.micro"
}

resource "aws_eip" "ec2_ip" {
  instance = aws_instance.ec2.id
  domain   = "vpc"
}

output "public_ip" {
  description = "Public IP address of the elastic IP resource."
  value       = aws_eip.ec2_ip.public_ip
}

output "private_ip" {
  description = "Private IP address of the elastic IP resource."
  value       = aws_eip.ec2_ip.private_ip
  sensitive   = true
}

output "private_dns" {
  description = "Private DNS of the elastic IP resource."
  value       = aws_eip.ec2_ip.private_dns
  sensitive   = true
}
