provider "aws" {
  region = "us-east-1"
}

variable "server_port" {
  description = "The port number to receive HTTP requests."
  type        = number
  default     = 8080
}

resource "aws_security_group" "instance" {
  name = "terraform-example-instance"

  ingress {
    from_port   = var.server_port
    to_port     = var.server_port
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }
}

resource "aws_instance" "example" {
  ami                    = "ami-0ecb62995f68bb549"
  instance_type          = "t2.nano"
  vpc_security_group_ids = [aws_security_group.instance.id]

  tags = {
    Name = "terraform-example"
  }

  user_data_replace_on_change = true

  user_data = <<-EOF
              #!/bin/bash
              echo "Hello, world" > index.html
              nohup busybox httpd -f -p ${var.server_port} &
              EOF
}

output "public_uri" {
  description = "The public URI to access the webpage."
  # Use `curl $(tf output public_uri | tr -d '"')` to test.
  value = "http://${aws_instance.example.public_ip}:${var.server_port}"
}
