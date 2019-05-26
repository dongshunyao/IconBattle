#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "cocos2d.h"
#include <vector>
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"

USING_NS_CC;
using std::vector;
using std::string;
using network::HttpRequest;
using network::HttpClient;
using network::HttpResponse;
using std::stringstream;

class Network
{
public:
	static Network* getInstance();

	string getNews();

private:
	vector<string> header;
	vector<string> gotData;

	void createRequest(const string data);
	void receive(HttpClient* sender, HttpResponse* response);

	static Network* instance;
	Network();
};


#endif
