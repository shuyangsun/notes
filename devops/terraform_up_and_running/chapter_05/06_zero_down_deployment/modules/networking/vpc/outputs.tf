output "id" {
  description = "VPC ID."
  value       = aws_vpc.main.id
}

output "internet_gateway_id" {
  description = "Internet Gateway ID."
  value       = aws_internet_gateway.main.id
}
