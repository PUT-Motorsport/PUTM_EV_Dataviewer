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