resource "aws_vpc" "main" {
  cidr_block = "10.0.0.0/16"
  tags = merge({
    Name = "zdd-vpc"
  }, local.custom_tags_filtered)
}

resource "aws_internet_gateway" "main" {
  vpc_id = aws_vpc.main.id
  tags = merge({
    Name = "zdd-igw"
  }, local.custom_tags_filtered)
}
