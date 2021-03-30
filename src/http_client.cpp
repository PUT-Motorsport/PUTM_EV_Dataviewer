#include "http_client.h"

using namespace std;

http_client::http_client(string address, int port)
{
		this->session = new HTTPClientSession(address,port);
}

http_client::~http_client()
{
	delete this->session;
}

void http_client::send_request(stringstream* oss,bool verbose)
{
	string path = "/";
	HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
	this->session->sendRequest(req);
	HTTPResponse res;
	if(verbose) cout << res.getStatus() << " " << res.getReason() << endl;
	istream &is = this->session->receiveResponse(res);
	//std::stringstream oss;
	StreamCopier::copyStream(is, *oss);
	//return *oss;
}

void tFunction(Data_container* dataPointer)
{
	//cout<<"a"<<endl;
	Data_container data = *dataPointer;
	//cout<<"Test: "<<data.peek_a()<<" "<<data.peek_b()<<endl;
	http_client client("127.0.0.1",8000);
	stringstream response;
	string word;
	string a[4]; //TODO: Change that to something more safe then static declaration
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
			data.push_to_vector(0,stof(a[0]));
			data.push_to_vector(1,stof(a[1]));
			data.push_to_vector(2,stof(a[2]));
			data.push_to_vector(3,stof(a[3])); //TODO: Kinda the same
			data.raise_data_flag();
			usleep(0.25*1000000);
		}
		catch(Exception &e)
		{
			cout<<e.displayText()<<endl;
		}
	}
}