#include "http_client.h"
#include "data_container.h"

using namespace std;

void tFunction(data_container* dataPointer)
{
	//cout<<"a"<<endl;
	data_container data = *dataPointer;
	//cout<<"Test: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
	http_client client("127.0.0.1",8000);
	stringstream response;
	string word;
	string a[2];
	while(true)
	{
		try
		{
			response.str(std::string());
			response.clear();
			//cout<<"stream content: "<<response.str()<<endl;
			int iterator = 0;	
			client.send_request(&response,0);
			while(getline(response, word, ',')) 
				a[iterator++] = word;
			//cout<<"Data: "<<a[0]<<" "<<a[1]<<endl;
			data.assign_a(stoi(a[0]));
			data.assign_b(stoi(a[1]));
			data.pull_up_data_flag();
			sleep(1);
		}
		catch(Exception &e)
		{
			cout<<e.displayText()<<endl;
		}
		//cout<<"Peek: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
	}
}


int main()
{
	data_container data(0,0);
	thread http_thread(tFunction,&data);
	http_thread.detach();
	while(true)
	{
		//cout<<data.get_data_flag()<<endl;
		if(data.get_data_flag()==true)
		{
			cout<<"Peek: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
			data.pull_down_data_flag();
		}
		// usleep(1000000/2);
	}
	return 0;
}
