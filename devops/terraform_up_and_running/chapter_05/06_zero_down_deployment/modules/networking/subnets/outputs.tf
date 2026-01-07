output "public_ids" {
  description = "Public subnet IDs."
  value       = values(resource.aws_subnet.public)[*].id
}

output "private_ids" {
  description = "Private subnet IDs."
  value       = values(resource.aws_subnet.private)[*].id
}
