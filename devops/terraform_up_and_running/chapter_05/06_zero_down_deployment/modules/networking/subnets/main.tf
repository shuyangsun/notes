output "availability_zones_names" {
  description = "All available zones."
  value       = local.available_zone_names
}

resource "aws_subnet" "public" {
  for_each = { for idx, az in local.available_zone_names : idx => az }

  vpc_id            = var.vpc_id
  cidr_block        = "10.0.${each.key + 1}.0/24"
  availability_zone = each.value
  tags = {
    Name = "zdd-public-${each.key}"
  }
}

resource "aws_subnet" "private" {
  for_each = { for idx, az in local.available_zone_names : idx => az }

  vpc_id            = var.vpc_id
  cidr_block        = "10.0.${each.key + 1 + length(local.available_zone_names)}.0/24"
  availability_zone = each.value
  tags = {
    Name = "zdd-private-${each.key}"
  }
}

resource "aws_route_table" "public" {
  vpc_id = var.vpc_id

  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = var.internet_gateway_id
  }

  tags = {
    Name = "zdd-public-rt"
  }
}

resource "aws_route_table_association" "public" {
  for_each = aws_subnet.public

  subnet_id      = each.value.id
  route_table_id = aws_route_table.public.id
}
