#include "Network.h"

Network* Network::instance = nullptr;

Network* Network::getInstance()
{
	if (instance == nullptr) instance = new Network;
	return instance;
}

string Network::getNews()
{
	if (!initConnect()) return "抱歉! 网络连接失败!";

	//根据需要拼接发送字符串
	auto temp = news;
	temp += "\t";
	strcpy(sendBuf, temp.data());

	//发送消息
	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0) return "抱歉! 网络连接失败!";

	//接收消息
	recv(sockClient, receiveBuf, 300, 0);
	if (receiveBuf[0] == '\0') return "抱歉! 网络连接失败!";

	string data = receiveBuf;
	closeConnect();

	return data;
}

vector<pair<string, int>> Network::getRank(const bool isClassical)
{
	if (!initConnect()) return rankOriginal;

	// 根据模式拼接发送字符串
	if (isClassical)
	{
		auto temp = rank;
		temp += "\t";
		temp += mode1;
		strcpy(sendBuf, temp.data());
	}
	else
	{
		auto temp = rank;
		temp += "\t";
		temp += mode2;
		strcpy(sendBuf, temp.data());
	}

	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0)
	{
		closeConnect();
		return rankOriginal;
	}

	recv(sockClient, receiveBuf, 100, 0);
	if (receiveBuf[0] == '\0')
	{
		closeConnect();
		return rankOriginal;
	}

	const string data = receiveBuf;
	closeConnect();

	return handleRankVector(data);
}

bool Network::postScore(const string& name, const int score, const bool isClassical)
{
	if (!initConnect()) return false;

	//得到哈希值并根据模式拼接发送字符串
	auto hashStr = to_string(Util::getStringHash(name));
	if (isClassical)
	{
		auto temp = post;
		temp += "\t";
		temp += mode1;
		temp += "\t";
		temp += name;
		temp += "\t";
		temp += std::to_string(score);
		temp += "\t";
		temp += hashStr;
		strcpy(sendBuf, temp.data());
	}
	else
	{
		auto temp = post;
		temp += "\t";
		temp += mode2;
		temp += "\t";
		temp += name;
		temp += "\t";
		temp += std::to_string(score);
		temp += "\t";
		temp += hashStr;
		strcpy(sendBuf, temp.data());
	}

	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0)
	{
		closeConnect();
		return false;
	}
	// 可以接受post成功与否的服务器回信

	closeConnect();
	return true;
}

bool Network::initConnect()
{
	memset(receiveBuf, 0, 300);
	memset(sendBuf, 0, 300);

	auto nNetTimeout = 2000;
	//socket启动失败
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) return false;

	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addressServer.sin_addr.S_un.S_addr = inet_addr("39.107.229.247"); //设置地址
	addressServer.sin_family = AF_INET;
	addressServer.sin_port = htons(27003); //设置端口号

	//设置接受消息延时2s
	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&nNetTimeout), sizeof(int));
	//连接服务器
	const auto check = connect(sockClient, reinterpret_cast<SOCKADDR*>(&addressServer), sizeof(SOCKADDR));
	return check >= 0;
}

void Network::closeConnect() const
{
	closesocket(sockClient);
	WSACleanup();
}

vector<pair<string, int>> Network::handleRankVector(const string rank)
{
	char buf[300];
	strcpy(buf, rank.data());

	vector<string> name;
	vector<string> score;
	vector<pair<string, int>> final;

	auto count = 1;
	auto* split = "\t";
	auto str = strtok(buf, split);
	while (str != nullptr)
	{
		if (count % 2 != 0)
			name.emplace_back(str);
		else
			score.emplace_back(str);

		str = strtok(nullptr, split);
		count++;
	}

	for (auto i = 0; i < name.size(); i++)
	{
		// BUG score[] Out of range!
		final.emplace_back(pair<string, int>(name[i], atoi(score[i].c_str())));
	}

	return final;
}
