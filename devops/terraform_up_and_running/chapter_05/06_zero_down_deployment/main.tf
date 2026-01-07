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

module "launch_template" {
  source = "./modules/launch_template"

  instance_type = "t2.micro"
  ami           = "ami-08d7aabbb50c2c24e"
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
}

module "lb" {
  source = "./modules/lb"

  vpc_id            = module.vpc.id
  security_group_id = module.lb_sg.security_group_id
  subnet_ids        = module.subnets.public_ids

  public_port = var.public_port
  host_port   = var.hosting_port
}
