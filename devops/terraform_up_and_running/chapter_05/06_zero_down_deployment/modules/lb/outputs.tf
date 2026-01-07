output "website_url" {
  description = "The DNS name of the load balancer to access the website"
  value       = "http://${aws_lb.web_server.dns_name}"
}
