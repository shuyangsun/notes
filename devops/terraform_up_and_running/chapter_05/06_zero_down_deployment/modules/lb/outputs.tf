output "website_url" {
  description = "The DNS name of the load balancer to access the website"
  value       = "http://${aws_lb.web_server.dns_name}"
}

output "target_group_arn" {
  description = "ARN of the application target group."
  value       = aws_lb_target_group.app_target.arn
}
