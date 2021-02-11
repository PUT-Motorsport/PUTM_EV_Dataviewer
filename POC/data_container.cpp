#include "data_container.h"

data_container::data_container(unsigned int init_var_a, unsigned int init_var_b)
{
	this->var_a = new unsigned int;
	this->var_b = new unsigned int;
	*this->var_a = init_var_a;
	*this->var_b = init_var_b; 
	this->new_data_flag = new bool;
	*this->new_data_flag = false;
}

data_container::data_container()
{
	*this->new_data_flag = false;
}

data_container::~data_container()
{
	delete var_b;
	delete var_a;
}

void data_container::assign_a(unsigned int x)
{
	*this->var_a = x;
}
void data_container::assign_b(unsigned int x)
{
	*this->var_b = x;
}

int data_container::peek_a()
{
	return *this->var_a;
}
int data_container::peek_b()
{
	return *this->var_b;
}

void data_container::pull_up_data_flag()
{
	*this->new_data_flag = true;
}
void data_container::pull_down_data_flag()
{
	*this->new_data_flag = false;
}
bool data_container::get_data_flag()
{
	return *this->new_data_flag;
}
