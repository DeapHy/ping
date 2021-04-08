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

// ============================================ СОЗДАНИЕ ВСЕХ НЕОБХОДИМЫХ ПЕРЕМЕННЫХ, СТРКУТУР И ПРОЧЕГО ВСЕГО ============================================
ofstream logStream;                           // Объект класса для работы с файлом лога
int returnCode;                         // Код возврата
SOCKET listn;                           // Объект сокета, с которым работает программа в процессе отправки и принятия аргументов
char* Icmp;                             // Переменная, в которой будет храниться
IcmpHeader pac;                         // Структура, содержащая ICMP заголовок
IcmpHeader* Packet;                     // Указатель на структуру, содержащую ICMP заголовок
int incr;                               // Переменная, используемая в цикле
char bf[BUFFER_SIZE];                   // Буфер для ответа
LOGINFO logger;                         // Структура для хранения текста ошибки, кода ошибки и времени когда произошла ошибка
SOCKADDR_IN list_adr;                   // Структура SOCKADDR_IN описывает сокет для работы с протоколами IP. Данная структура используется для удаленного устройства
SOCKADDR_IN bnd;                        // Данная структура используется для локального устройства
SOCKADDR_IN out_;                       // Данная структура используется для обработки полученного ответа
WSADATA wsd;                            // Структура содержит информацию о реализации сокета
char* Ip;                               // Пингуемый адрес
// ========================================================================================================================================================