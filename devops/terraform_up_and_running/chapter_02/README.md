[Home](../../../README.md) >> [DevOps](../../../README.md#devops) >> [Terraform: Up and Running](../README.md) >> [2. Getting Started with Terraform](./README.md)

# 2. Getting Started with Terraform

There are three tiers of providers: `official`, `partner`, and `community`. For `partner` and `community` tiers, `terraform { reqreuiered_providers { ... } }` blocks are required.

```terraform
terraform {
  required_providers {
    digitalocean = {
      # https://registry.terraform.io/providers/digitalocean/digitalocean/
      source = "digitalocean/digitalocean"
      version = "2.27.0"
    }
  }
}
```
