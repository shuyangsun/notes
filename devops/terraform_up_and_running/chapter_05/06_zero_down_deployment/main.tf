module "vpc" {
  source = "./modules/networking/vpc"
}

module "subnets" {
  source              = "./modules/networking/subnets"
  vpc_id              = module.vpc.id
  internet_gateway_id = module.vpc.internet_gateway_id
  num_available_zones = 2
}

module "lb_sg" {
  source      = "./modules/networking/lb_sg"
  vpc_id      = module.vpc.id
  public_port = var.public_port
}

module "ec2_sg" {
  source                    = "./modules/networking/ec2_sg"
  vpc_id                    = module.vpc.id
  host_port                 = var.hosting_port
  ingress_security_group_id = module.lb_sg.security_group_id
}

data "aws_ami" "ubuntu" {
  most_recent = true
  owners      = ["099720109477"] # Canonical

  filter {
    name   = "name"
    values = ["ubuntu/images/hvm-ssd/ubuntu-focal-20.04-amd64-server-*"]
  }

  filter {
    name   = "virtualization-type"
    values = ["hvm"]
  }
}

module "launch_template" {
  source = "./modules/launch_template"

  instance_type = "t2.micro"
  ami           = data.aws_ami.ubuntu.id
  server_port   = var.hosting_port
  page_title    = "Zero-Downtime Deployment Test"

  security_group_ids = [module.ec2_sg.security_group_id]
}

module "asg" {
  source = "./modules/asg"

  launch_template_id = module.launch_template.launch_template_id

  min_size = 2
  max_size = 3

  subnet_ids = module.subnets.private_ids

  target_group_arns = [module.lb.target_group_arn]
}

module "lb" {
  source = "./modules/lb"

  vpc_id            = module.vpc.id
  security_group_id = module.lb_sg.security_group_id
  subnet_ids        = module.subnets.public_ids

  public_port = var.public_port
  host_port   = var.hosting_port
}
