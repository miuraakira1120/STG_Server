#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "UDPServer.h"
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>	// WinSock�p
#include <ws2tcpip.h>	// WinSock�p
#include<string>
#include "Engine/GameObject.h"
#include "Player.h"

#pragma comment( lib, "ws2_32.lib" )

//const u_short SERVERPORT = 8080;
const unsigned short PORT = 8080;	// �T�[�o�̃|�[�g�ԍ�
const char* SERVERIPADDRESS = "127.0.0.1";	// �������g���T�[�o�̏ꍇ

SOCKET sock; 
WSADATA wsaData;

//�|�[�g�ԍ����蓖��(�\�P�b�g�A�h���X�\����)
SOCKET  s;
SOCKADDR_IN  bindAddr;
struct sockaddr_in toAddr;

SOCKADDR_IN fromAddr;

float playerPosX = 0;
float moveTransX = 0;

bool playerShotFlag = false;
bool enemyShotFlag = false;

bool isStart = true;
bool recvIsStart = false;

bool isWin = false;
bool isLose = false;


//������
void UDPServer::Initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		// error
	}
	// UDP�\�P�b�g�̍쐬
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		// error
	}
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;					// IPv4�A�h���X�g�p
	bindAddr.sin_port = htons(PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//�m���u���b�L���O���[�h
	u_long arg = 0x01;
	ioctlsocket(sock, FIONBIO, &arg);

	//�|�[�g�ԍ����蓖��
	if (bind(sock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) == SOCKET_ERROR)
	{
		//error
	}
}

//�X�V
void UDPServer::Update()
{
	////////////////////���M////////////////////////////
	playerPosX += 1000;
	int sendValue = htonf(playerPosX);
	int rettt = sendto(sock, (char*)&sendValue, sizeof(sendValue), 0, (SOCKADDR*)&fromAddr, sizeof(fromAddr));

	int sendPlayerShotFlag = htonl((long)playerShotFlag);
	int rettt2 = sendto(sock, (char*)&sendPlayerShotFlag, sizeof(sendPlayerShotFlag), 0, (SOCKADDR*)&fromAddr, sizeof(fromAddr));

		int sendStartFlag = htonl((long)isStart);
		int rettt3 = sendto(sock, (char*)&sendStartFlag, sizeof(sendStartFlag), 0, (SOCKADDR*)&fromAddr, sizeof(fromAddr));
	
	/////////////// �����l�̎�M///////////////////////
	// ���M���̃A�h���X�����i�[����\�P�b�g�A�h���X�\����
	int recvCount;
	int fromlen = sizeof(fromAddr);

	// ��M������������i�[
	int ret = recvfrom(sock, (char*)&recvCount, sizeof(recvCount), 0, (SOCKADDR*)&fromAddr, &fromlen);
	if (ret < 0)
	{
		//error
	}
	else
	{
		// �ƂĂ��厖�ȏ��� ... ���o�C�g�f�[�^������	???()
		moveTransX = ntohf(recvCount);
		moveTransX -= 1000;
	}

	int recvEnemyShotFlag;
	int fromlen2 = sizeof(fromAddr);

	// ��M������������i�[
	int ret2 = recvfrom(sock, (char*)&recvEnemyShotFlag, sizeof(recvEnemyShotFlag), 0, (SOCKADDR*)&fromAddr, &fromlen2);
	if (ret2 < 0)
	{
		//error
	}
	else
	{
		// �ƂĂ��厖�ȏ��� ... ���o�C�g�f�[�^������	???()
		enemyShotFlag = ntohl(recvEnemyShotFlag);
	}

	int recvStartFlag;
	int fromlen3 = sizeof(fromAddr);

		// ��M������������i�[
		int ret3 = recvfrom(sock, (char*)&recvStartFlag, sizeof(recvStartFlag), 0, (SOCKADDR*)&fromAddr, &fromlen3);
		if (ret3 < 0)
		{
			//error
		}
		else
		{
			// �ƂĂ��厖�ȏ��� ... ���o�C�g�f�[�^������	???()
			recvIsStart = ntohl(recvStartFlag);
		}
}

float UDPServer::GetMoveX()
{
	return moveTransX;
}

bool UDPServer::GetEnemyShotFlag()
{
	return enemyShotFlag;
}

bool UDPServer::GetIsStart()
{
	return recvIsStart;
}

bool UDPServer::GetIsLose()
{
	return isLose;
}

void UDPServer::SetMoveX(float posX)
{
	playerPosX = posX;
}

void UDPServer::SetPlayerShotFlag(bool bullet)
{
	playerShotFlag = bullet;
}

void UDPServer::SetIsLose()
{
	isLose = true;
}

void UDPServer::SetIsStart(bool startFlag)
{
	isStart = startFlag;
}

