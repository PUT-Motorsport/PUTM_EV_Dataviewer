#ifndef __DATA_CONTAINER_H__
#define __DATA_CONTAINER_H__

class data_container
{
private:
	unsigned int* var_a;
	unsigned int* var_b;
	bool* new_data_flag;
public:
	data_container(unsigned int init_var_a, unsigned int init_var_b);
	data_container();

	void assign_a(unsigned int x);
	void assign_b(unsigned int x);
	
	int peek_a();
	int peek_b();

	void pull_up_data_flag();
	void pull_down_data_flag();
	bool get_data_flag();

	~data_container();
};

#endif