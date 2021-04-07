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

//заголовок IP 
struct IpHeader
{
    unsigned char verhlen;	        // Длина заголовка в dwords
    unsigned char tos : 6;          // тип сервиса 
    unsigned char additional : 2;   // параметры (до 320 бит)
    unsigned short totallent;       // Длина пакета в dwords
    unsigned short id;              // Уникальный идентификатор процесса
    unsigned short offset;          // флаги и смещение
    unsigned char ttl;              // Time to live
    unsigned char proto;            // протокол 
    unsigned short checksum;        // контрольная сумма 
    unsigned int source;            // IP-адрес отправителя 
    unsigned int destination;       // IP-адрес назначения 
};

//заголовок ICMP
struct IcmpHeader
{
    unsigned char i_type;
    unsigned char i_code;
    unsigned short i_seq;
    unsigned short i_crc;
    unsigned short i_id;
};

// Структура, хранящая в себе информацию об ошибке (нужна для логирования)
struct LOGINFO {
    string error;         // Текст ошибки
    int errorCode;      // Код ошибки
    char* datetime;     // Системное время ошибки
    /*
    time_t now = time(0);
    char* dt = ctime(&now);
    Так получать строку, которая содержит в себе системное время (для Насти и Алины)
    */
};