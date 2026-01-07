resource "aws_security_group" "lb" {
  name        = "zdd-lb-sg"
  description = "Allow inbound access to port 80 from the internet."
  vpc_id      = var.vpc_id

  tags_all = {
    Name = "zdd-lb-sg"
  }
}

resource "aws_vpc_security_group_ingress_rule" "allow_inbound_ipv4" {
  security_group_id = aws_security_group.lb.id

  ip_protocol = "tcp"
  from_port   = var.public_port
  to_port     = var.public_port
  cidr_ipv4   = "0.0.0.0/0"
}

resource "aws_vpc_security_group_ingress_rule" "allow_inbound_ipv6" {
  security_group_id = aws_security_group.lb.id

  ip_protocol = "tcp"
  from_port   = var.public_port
  to_port     = var.public_port
  cidr_ipv6   = "::/0"
}

resource "aws_vpc_security_group_egress_rule" "allow_outbound_ipv4" {
  security_group_id = aws_security_group.lb.id

  ip_protocol = "-1"
  cidr_ipv4   = "0.0.0.0/0"
}

resource "aws_vpc_security_group_egress_rule" "allow_outbound_ipv6" {
  security_group_id = aws_security_group.lb.id

  ip_protocol = "-1"
  cidr_ipv6   = "::/0"
}
