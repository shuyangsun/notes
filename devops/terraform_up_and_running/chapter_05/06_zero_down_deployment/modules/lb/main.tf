resource "aws_lb" "web_server" {
  name               = "zdd-lb"
  internal           = false
  load_balancer_type = "application"
  security_groups    = [var.security_group_id]
  subnets            = var.subnet_ids
}

resource "aws_lb_target_group" "app_target" {
  name = "zdd-app-target"

  port     = var.host_port
  protocol = "HTTP"
  vpc_id   = var.vpc_id

  health_check {
    path = "/"
    port = var.host_port
  }
}

resource "aws_lb_listener" "web" {
  load_balancer_arn = aws_lb.web_server.arn
  port              = var.public_port
  protocol          = "HTTP"
  default_action {
    type             = "forward"
    target_group_arn = aws_lb_target_group.app_target.arn
  }
}
