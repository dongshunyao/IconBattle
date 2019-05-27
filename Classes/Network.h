#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "cocos2d.h"
#include <cstdio>
#include <winsock2.h>
#include "Util.h"
#pragma comment(lib,"WS2_32.lib")

USING_NS_CC;
using std::vector;
using std::string;
using std::to_string;

class Network
{
public:
	static Network* getInstance();

	string getNews();
	string getScore(const string& user, bool mode);
	bool postScore(const string& name, const string& score, bool mode);

private:
	WSADATA wsd;
	SOCKET sockClient;
	SOCKADDR_IN addressServer;

	bool connected = false;

	char receiveBuf[300];
	char sendBuf[300];

	const string news = "GET_NEWS";
	const string score = "GET_SCORE";
	const string mode1 = "MODE1";
	const string mode2 = "MODE2";
	const string post = "POST";

	static Network* instance;

	void closeConnect() const;
	Network();
};

#endif
