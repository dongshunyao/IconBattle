#include "Network.h"

Network* Network::instance = nullptr;

Network* Network::getInstance()
{
	if (instance == nullptr) instance = new Network;
	return instance;
}

string Network::getNews()
{
	memset(receiveBuf, 0, 300);
	memset(sendBuf, 0, 300);

	if (!connected) return "网络连接失败，请重试......";

	//根据需要拼接发送字符串
	auto temp = news;
	temp += "\t";
	strcpy(sendBuf, temp.data());

	//发送消息
	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0) return "网络连接失败，请重试......";

	//接收消息
	recv(sockClient, receiveBuf, 300, 0);
	if (receiveBuf[0] == '\0') return "网络连接失败，请重试......";

	string data = receiveBuf;
	closeConnect();

	return data;
}

// 发送失败返回串-1
string Network::getScore(const string& user, const bool mode)
{
	memset(receiveBuf, 0, 300);
	memset(sendBuf, 0, 300);

	if (!connected) return "-1";

	// 根据模式拼接发送字符串
	if (mode)
	{
		auto temp = score;
		temp += "\t";
		temp += mode1;
		temp += "\t";
		temp += user;
		strcpy(sendBuf, temp.data());
	}
	else
	{
		auto temp = score;
		temp += "\t";
		temp += mode2;
		temp += "\t";
		temp += user;
		strcpy(sendBuf, temp.data());
	}

	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0)
	{
		closeConnect();
		return "-1";
	}

	recv(sockClient, receiveBuf, 100, 0);
	if (receiveBuf[0] == '\0')
	{
		closeConnect();
		return "-1";
	}

	string data = receiveBuf;
	closeConnect();

	return data;
}

bool Network::postScore(const string& name, const string& score, const bool mode)
{
	memset(receiveBuf, 0, 300);
	memset(sendBuf, 0, 300);

	if (!connected) return false;

	//得到哈希值并根据模式拼接发送字符串
	auto hashStr = to_string(Util::getStringHash(name));
	if (mode)
	{
		auto temp = post;
		temp += "\t";
		temp += mode1;
		temp += "\t";
		temp += name;
		temp += "\t";
		temp += score;
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
		temp += score;
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

Network::Network()
{
	memset(receiveBuf, 0, 300);
	memset(sendBuf, 0, 300);

	auto nNetTimeout = 2000;
	//socket启动失败
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) return;

	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addressServer.sin_addr.S_un.S_addr = inet_addr("39.107.229.247"); //设置地址
	addressServer.sin_family = AF_INET;
	addressServer.sin_port = htons(27003); //设置端口号

	//设置接受消息延时2s
	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&nNetTimeout), sizeof(int));
	//连接服务器
	const auto check = connect(sockClient, reinterpret_cast<SOCKADDR*>(&addressServer), sizeof(SOCKADDR));
	if (check < 0) return;
	connected = true;
}

void Network::closeConnect() const
{
	closesocket(sockClient);
	WSACleanup();
}
