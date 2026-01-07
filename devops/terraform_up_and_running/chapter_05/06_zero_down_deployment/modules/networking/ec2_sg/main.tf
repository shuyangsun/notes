resource "aws_security_group" "instance" {
  name        = "zdd-instance-sg"
  description = "Allow inbound traffic from LB security group."
  vpc_id      = var.vpc_id

  tags_all = {
    Name = "zdd-instance-sg"
  }
}

resource "aws_vpc_security_group_ingress_rule" "allow_inbound_from_lb" {
  security_group_id = aws_security_group.instance.id

  ip_protocol = "tcp"
  from_port   = var.host_port
  to_port     = var.host_port

  referenced_security_group_id = var.ingress_security_group_id
}

resource "aws_vpc_security_group_egress_rule" "allow_outbound_ipv4" {
  security_group_id = aws_security_group.instance.id

  ip_protocol = "-1"
  cidr_ipv4   = "0.0.0.0/0"
}

resource "aws_vpc_security_group_egress_rule" "allow_outbound_ipv6" {
  security_group_id = aws_security_group.instance.id

  ip_protocol = "-1"
  cidr_ipv6   = "::/0"
}
