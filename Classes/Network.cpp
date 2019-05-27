#include "Network.h"

Network* Network::instance = nullptr;

Network* Network::getInstance()
{
	if (instance == nullptr) instance = new Network;
	return instance;
}

string Network::getNews()
{
	auto temp = GET_NEWS;
	temp += "\t";
	strcpy(sendBuf, temp.data());

	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0)
	{
		// TODO: 发送失败
	}

	recv(sockClient, recvBuf, 300, 0);

	if (recvBuf[0] == '\0')
	{
		// TODO: 处理接收消息超时或链接断开提示
		return "";
	}
	string data = recvBuf;
	closeConnect();
	return data;
}

string Network::getScore(const string user, const bool mode)
{
	if (mode)
	{
		auto temp = GET_SCORE;
		temp += "\t";
		temp += MODE1;
		temp += "\t";
		temp += user;
		strcpy(sendBuf, temp.data());
	}

	else
	{
		auto temp = GET_SCORE;
		temp += "\t";
		temp += MODE2;
		temp += "\t";
		temp += user;
		strcpy(sendBuf, temp.data());
	}

	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0)
	{
		// TODO: 发送失败
	}

	recv(sockClient, recvBuf, 100, 0);

	if (recvBuf[0] == '\0')
	{
		// TODO: 处理接收消息超时或链接断开提示
		return "";
	}

	string data = recvBuf;
	closeConnect();

	log(data.c_str());

	return data;
}

void Network::postScore(const string name, const string score, const bool mode)
{
	// TODO: 跑哈希
	if (mode)
	{
		auto temp = POST;
		temp += "\t";
		temp += MODE1;
		temp += name;
		temp += "\t";
		temp += score;
		strcpy(sendBuf, temp.data());
	}
	else
	{
		auto temp = POST;
		temp += "\t";
		temp += MODE2;
		temp += name;
		temp += "\t";
		temp += score;
		strcpy(sendBuf, temp.data());
	}

	const auto check = send(sockClient, sendBuf, strlen(sendBuf), 0);
	if (check < 0)
	{
		// TODO: 发送失败
	}

	// TODO: 接受post成功与否的服务器回信

	closeConnect();
}

void Network::init()
{
	memset(recvBuf, 0, 300);
	memset(sendBuf, 0, 300);

	auto nNetTimeout = 2000;

	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		printf("start up failed!\n");
		return;
	}

	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	setsockopt(sockClient, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&nNetTimeout), sizeof(int));

	const auto check = connect(sockClient, reinterpret_cast<SOCKADDR*>(&addrSrv), sizeof(SOCKADDR));
	if (check < 0)
	{
		// TODO: 处理链接失败提示
	}
}

void Network::closeConnect() const
{
	closesocket(sockClient);
	WSACleanup();
}
