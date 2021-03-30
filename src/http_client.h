#pragma once

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <bits/stdc++.h>
#include "data_container.h"

using namespace Poco::Net;
using namespace Poco;
using namespace std;

void tFunction(Data_container* dataPointer);

class http_client
{
private:
	HTTPClientSession* session;
public:
	http_client(string address, int port);
	~http_client();
	void send_request(stringstream* oss,bool verbose);
};
