#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "cocos2d.h"
#include <cstdio>
#include <winsock2.h>
#pragma comment(lib,"WS2_32.lib")

USING_NS_CC;
using std::vector;
using std::string;

class Network
{
public:
	static Network* getInstance();

	void init();
	void closeConnect() const;
	string getNews();
	string getScore(bool mode);
	void postScore(const string name, const string score, bool mode);

private:
	WSADATA wsd;
	SOCKET sockClient;
	SOCKADDR_IN addrSrv;

	char recvBuf[300];
	char sendBuf[300];

	const string GET_NEWS = "GET_NEWS";
	const string GET_SCORE = "GET_SCORE";
	const string MODE1 = "MODE1";
	const string MODE2 = "MODE2";
	const string POST = "POST";

	static Network* instance;

	Network() = default;
};


#endif
