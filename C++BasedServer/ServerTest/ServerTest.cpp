#include<stdio.h>
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
#include<strstream>
#include<winsock.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	//�������Ϣ
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET;						//IPV4��ַ��
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//ָ��������ip��ַ
	sockAddr.sin_port = htons(31022);					//ָ���������˿ں�
														////////////////////////////////////////////////

	SOCKET severSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(severSocket, (sockaddr*)&sockAddr, sizeof(sockAddr));
	std::string tem;
	while (std::getline(std::cin, tem))
	{
		send(severSocket, tem.c_str(), 1000, NULL);		//���send������������len�����Ҿ���size����һ�㣿
		if (tem == "finish")
		{
			send(severSocket, tem.c_str(), 1000, NULL);
			break;
		}

	}

	closesocket(severSocket);
	WSACleanup();
	return 0;
}

