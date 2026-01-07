resource "aws_autoscaling_group" "main" {
  name = "zdd-asg"

  desired_capacity = var.min_size
  min_size         = var.min_size
  max_size         = var.max_size

  launch_template {
    id      = var.launch_template_id
    version = "$Latest"
  }

  vpc_zone_identifier = var.subnet_ids

  tag {
    key                 = "Name"
    value               = "zdd-asg"
    propagate_at_launch = true
  }
}
