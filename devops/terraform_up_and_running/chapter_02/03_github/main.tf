terraform {
  required_providers {
    github = {
      source  = "integrations/github"
      version = "~> 6.9.0"
    }
  }
}

provider "github" {}

resource "github_repository" "example" {
  name        = "terraform-example-repo"
  description = "Example repository created by Terraform."

  visibility = "private"
}
