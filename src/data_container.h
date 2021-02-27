#pragma once

#include <bits/stdc++.h>

class Data_container
{
	std::vector<std::vector<float>*> data;
	int num_data;
	bool new_data_flag;
public:
	Data_container(int num_data);
	~Data_container();
	void push_to_vector(int num,float value);
	float pop_from_vector(int num);
	void raise_data_flag();
	void pull_data_flag();
	bool peek_data_flag();
	float* get_vector_data_ptr(int num);
	unsigned int get_vector_size(int num);
};