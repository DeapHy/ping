#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define TIMEOUT 5000
#define BUFFER_SIZE 256
#define PACKET_SIZE 42
#define PACKET_ Packet
#define SENDING_TIMEOUT 1000

#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Ws2ipdef.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <fstream>

#include <typeinfo>

#pragma comment (lib,"Ws2_32.lib")

using std::endl;
using std::string;
using std::cout;
using std::ofstream;

//��������� IP 
struct IpHeader
{
    unsigned char verhlen;	        // ����� ��������� � dwords
    unsigned char tos : 6;          // ��� ������� 
    unsigned char additional : 2;   // ��������� (�� 320 ���)
    unsigned short totallent;       // ����� ������ � dwords
    unsigned short id;              // ���������� ������������� ��������
    unsigned short offset;          // ����� � ��������
    unsigned char ttl;              // Time to live
    unsigned char proto;            // �������� 
    unsigned short checksum;        // ����������� ����� 
    unsigned int source;            // IP-����� ����������� 
    unsigned int destination;       // IP-����� ���������� 
};

//��������� ICMP
struct IcmpHeader
{
    unsigned char i_type;
    unsigned char i_code;
    unsigned short i_seq;
    unsigned short i_crc;
    unsigned short i_id;
};

// ���������, �������� � ���� ���������� �� ������ (����� ��� �����������)
struct LOGINFO {
    string error;         // ����� ������
    int errorCode;      // ��� ������
    char* datetime;     // ��������� ����� ������
    /*
    time_t now = time(0);
    char* dt = ctime(&now);
    ��� �������� ������, ������� �������� � ���� ��������� ����� (��� ����� � �����)
    */
};