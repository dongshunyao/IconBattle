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
using std::pair;

class Network
{
public:
	static Network* getInstance();

	string getNews();
	vector<pair<string, int>> getRank(bool isClassical);
	bool postScore(const string& name, const int score, bool isClassical);

private:
	WSADATA wsd;
	SOCKET sockClient;
	SOCKADDR_IN addressServer;

	char receiveBuf[300];
	char sendBuf[300];

	vector<pair<string, int>> rankOriginal;

	const string news = "GET_NEWS";
	const string rank = "GET_RANK";
	const string mode1 = "MODE1";
	const string mode2 = "MODE2";
	const string post = "POST";

	static Network* instance;

	void closeConnect() const;
	vector<pair<string, int>> handleRankVector(const string rank);
	bool initConnect();
	Network() = default;
};

#endif
