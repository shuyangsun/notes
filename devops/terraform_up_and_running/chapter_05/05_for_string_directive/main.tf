# --------------------------------- Providers ----------------------------------

terraform {
  required_version = "~> 1.14.3"
}

# --------------------------------- Variables ----------------------------------

variable "names" {
  description = "User names."
  type        = list(string)
  default     = ["Alice", "Bob", "Eve"]
}

# ---------------------------------- Outputs -----------------------------------

output "all_names" {
  description = "All user names."
  value       = "%{for idx, name in var.names}(${idx}) ${name}, %{endfor}"
}
