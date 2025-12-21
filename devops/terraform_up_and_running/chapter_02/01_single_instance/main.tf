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
  tags = {
    Name = "${var.instance_name}-security-group"
  }

  ingress {
    from_port   = var.port
    to_port     = var.port
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
