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

variable "port" {
  description = "Port to receive incoming traffic."
  type        = number
  default     = 8080
}

variable "instance_name" {
  description = "EC2 instance name."
  type        = string
  default     = "single-ec2-example"
}

resource "aws_security_group" "instance" {
  name        = "ec2-security-group"
  description = "Firewall for the EC2 instance."

  tags = {
    Name = "${var.instance_name}-security-group"
  }
}

resource "aws_vpc_security_group_ingress_rule" "allow_ping" {
  description = "Allow ping on EC2 instance."

  security_group_id = aws_security_group.instance.id

  cidr_ipv4   = "0.0.0.0/0"
  ip_protocol = "icmp"
  from_port   = -1
  to_port     = -1
}

resource "aws_vpc_security_group_ingress_rule" "allow_inbound" {
  description = "Allow inbound traffic to server port."

  security_group_id = aws_security_group.instance.id

  cidr_ipv4   = "0.0.0.0/0"
  ip_protocol = "tcp"
  from_port   = var.port
  to_port     = var.port
}

resource "aws_vpc_security_group_egress_rule" "allow_outbound" {
  description = "Allow outbound traffic."

  security_group_id = aws_security_group.instance.id

  cidr_ipv4   = "0.0.0.0/0"
  ip_protocol = "-1"
}


resource "aws_instance" "example" {
  ami           = "ami-0ecb62995f68bb549"
  instance_type = "t2.micro"

  tags = {
    Name = var.instance_name
  }

  # Networking

  vpc_security_group_ids = [aws_security_group.instance.id]

  # Startup Script

  user_data = <<-EOF
              #!/bin/bash
              echo "Hello, world!" > index.html
              nohup busybox httpd -f -p 8080 &
              EOF

  user_data_replace_on_change = true
}

output "website_uri" {
  description = "URI to access hosted website."
  value       = "http://${aws_instance.example.public_ip}:${var.port}"
}
