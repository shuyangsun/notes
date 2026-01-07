data "aws_availability_zones" "available" {
  state = "available"
}

locals {
  _names         = data.aws_availability_zones.available.names
  _use_all_zones = var.num_available_zones == -1 || var.num_available_zones >= length(local._names)

  available_zone_names = local._use_all_zones ? local._names : slice(sort(tolist(toset(local._names))), 0, var.num_available_zones)
}
