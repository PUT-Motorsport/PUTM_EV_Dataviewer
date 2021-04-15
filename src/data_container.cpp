#include "data_container.h"

using namespace std;

Data_container::Data_container(int num_data)
{
	this->num_data = num_data;
	for(int i=0;i<num_data;i++)
	{
		this->data.push_back(new vector<double>);
	}
	this->new_data_flag = false;
}

Data_container::~Data_container()
{
	for(auto i : this->data)
		free(i);
	
}
void Data_container::push_to_vector(int num,double value)
{
	//Potential TODO: add exceptions
	if(num >= this->num_data)
	{
		cerr<<"No data field allocated"<<endl;
		exit(1);
	}
	this->data[num]->push_back(value);
}

double Data_container::pop_from_vector(int num)
{
	if(num >= this->num_data)
	{
		cerr<<"No data field allocated"<<endl;
		exit(1);
	}
	double a = *(this->data[num]->end());
	this->data[num]->pop_back();
	return a;
}

void Data_container::raise_data_flag()
{
	this->new_data_flag = true;
}

void Data_container::pull_data_flag()
{
	this->new_data_flag = false;
}

bool Data_container::peek_data_flag()
{
	return this->new_data_flag;
}

double* Data_container::get_vector_data_ptr(int num)
{
	if(num >= this->num_data)
	{
		cerr<<"No data field allocated"<<endl;
		exit(1);
	}
	return this->data[num]->data();
}

unsigned int Data_container::get_vector_size(int num)
{
	if(num >= this->num_data)
	{
		cerr<<"No data field allocated"<<endl;
		exit(1);
	}
	return this->data[num]->size();
}

int Data_container::get_num_data()
{
	return this->num_data;
}

void  Data_container::push_name(string a)
{
	this->names.push_back(a);
}
string* Data_container::get_names()
{
	return this->names.data();
}
string  Data_container::pop_name()
{
	string a = *(this->names.end());
	this->names.pop_back();
	return a;
}