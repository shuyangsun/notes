locals {
  custom_tags_filtered = {
    for key, value in var.custom_tags : key => value if key != "Name"
  }
}
