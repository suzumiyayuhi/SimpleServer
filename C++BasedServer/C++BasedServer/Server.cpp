#include<stdio.h>
#include<tchar.h>
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
#include<strstream>
#include<winsock.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
int main()
{
	WSADATA wsadata;

	WSAStartup(MAKEWORD(2, 2), &wsadata);
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;							//IPV4地址族
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");		//指定服务器ip地址
	sockAddr.sin_port = htons(31022);						//指定服务器端口号

	bind(serverSocket, (sockaddr*)&sockAddr, sizeof(sockAddr));
	listen(serverSocket, 10);

	//处理客户端请求
	sockaddr_in clientAddr;
	int addrLen = sizeof(clientAddr);
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &addrLen);

	std::string str = "";
	while (str != "finish")
	{
		char tem[1000];
		strcpy_s(tem, str.c_str());
		if (recv(clientSocket, (char*)&str, 1000, NULL))
		{
			sockaddr_in tem = (sockaddr_in)clientAddr;
			cout << inet_ntoa(clientAddr.sin_addr) << "\t\t" << str << endl;
		}

	}

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

