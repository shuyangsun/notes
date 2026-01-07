output "security_group_id" {
  description = "Instance security group ID."
  value       = aws_security_group.instance.id
}
