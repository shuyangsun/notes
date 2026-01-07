resource "aws_launch_template" "instance_template" {
  name_prefix   = "zdd-instance-"
  instance_type = var.instance_type
  image_id      = var.ami

  vpc_security_group_ids = var.security_group_ids

  user_data = base64encode(templatefile("${path.module}/user_data.sh.tftpl", {
    server_port = var.server_port
    title       = var.page_title
  }))

  # Required when using a launch configuration with ASG.
  lifecycle {
    create_before_destroy = true
  }
}
