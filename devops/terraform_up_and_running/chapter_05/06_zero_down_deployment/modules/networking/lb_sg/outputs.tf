output "security_group_id" {
  description = "LB security group ID."
  value       = aws_security_group.lb.id
}
