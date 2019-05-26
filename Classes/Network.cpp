#include "Network.h"

Network* Network::instance = nullptr;

Network* Network::getInstance()
{
	if (instance == nullptr) instance = new Network;
	return instance;
}

string Network::getNews()
{
	gotData.clear();

	return "";
}

void Network::createRequest(const string data)
{
	auto request = new(std::nothrow) HttpRequest();
	request->setUrl("http://www.huaji.store");
	request->setRequestType(HttpRequest::Type::POST);
	request->setHeaders(header);
	request->setResponseCallback(CC_CALLBACK_2(Network::receive, this));
	request->setRequestData(data.c_str(), strlen(data.c_str()));

	HttpClient::getInstance()->sendImmediate(request);
	request->release();
}

void Network::receive(HttpClient* sender, HttpResponse* response)
{
	if (!response) return;
	const auto buffer = response->getResponseData();

	stringstream stream;
	for (auto i : *buffer) stream << i;
	string s;
	stream >> s;

	auto index = 0;
	const int length = s.length();
	for (auto i = 0; i < length; i++)
	{
		if (s[i] == '\n')
		{
			gotData.emplace_back(s.substr(index, i));
			index = i + 1;
		}
	}
}

Network::Network()
{
	header.emplace_back("Host:");
	header.emplace_back("Accept:");
	header.emplace_back("Accept-Encoding:");
	header.emplace_back("Content-Length:");
	header.emplace_back("Content-Type:");
}
