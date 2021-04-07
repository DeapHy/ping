#include "ping.h"
#include "init.h"


/*� ������ ����� �������� ��� �������, ��������� � ��������� �������������� ���������
* ��� ��������� � ������ �����:
* 1. �������� ������� ����������
* 2. ������������� ����������� ��������
*/

// �������� ����������
int checkArgs(int argc, LOGINFO& logger) {
    if (argc < 2) {                                 // �������� �� ���������� �������� ����������
        cout << "usage: ping <IP_or_Host>" << endl;
        // error = "Wrong arguments.";
        return 1;                                   // ���������� � �������
    }
    return 0;                                       // �������� ����������
}

// ������������� ���� ��������, � ����� ������
int init(char* Ip, SOCKADDR_IN& list_adr, SOCKADDR_IN& bnd, SOCKADDR_IN& out_, WSADATA& wsd, SOCKET& listn, LOGINFO& logger) {
    try {
        int timeout = TIMEOUT;                          // ������� ��� �������� ECHO-��������� �������
        list_adr.sin_addr.S_un.S_addr = inet_addr(Ip);  // ����� ��� ������
        list_adr.sin_family = AF_INET;                  // ������ ����� ��������
        list_adr.sin_port = htons(6666);                // ���� ��� ������ (htons ��������� ���� � ��� ��� ������ � TCP/IP. ���� ��� 0, �� �� ������� ��������� ���� ����)

        bnd.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   // ��������� ����� �� ����� ���������� ������������
        bnd.sin_family = AF_INET;                       // ������ ����� ��������
        bnd.sin_port = htons(6666);                     // ���� ��� ������ (htons ��������� ���� � ��� ��� ������ � TCP/IP. ���� ��� 0, �� �� ������� ��������� ���� ����)

        out_.sin_family = AF_INET;
        if (WSAStartup(0x202, &wsd) != 0) {             // ������������� ���������� WinSock.dll (<������?>, <��������� �� ��������� WSADATA>) (����� ���������� �� ������ �� ������)
            // ������ ������
            return 1;
        }                                                   

        listn = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, 0, WSA_FLAG_OVERLAPPED);        // ������� ����� ��� ������������ ����� (https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsasocketa)
        setsockopt(listn, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));         // ������� ��������� (https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-setsockopt)
        return 0;
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
}

// �������������� DNS � IP
int getIPByName(SOCKADDR_IN& list_adr, SOCKADDR_IN& bnd, char* Ip, SOCKET& listn, LOGINFO& logger) {
    struct hostent* hp = NULL;
    if (list_adr.sin_addr.S_un.S_addr == INADDR_NONE) {
        if ((hp = gethostbyname(Ip)) != NULL) // ���� �� ������� IP, ���������� ������� ��������� �����
        {
            // memcpy(1,2,3) �������� � ��������� ���������� �� 2 �������� 3 � 1 
            // 1 - ���� ������, 2 - ���� � ������ � ����������� �����, 3 ����� ������ � ������
            memcpy(&(list_adr.sin_addr.S_un.S_addr), hp->h_addr_list[0], hp->h_length);
            list_adr.sin_family = hp->h_addrtype; // �������������� ��������������
            cout << "Pinging address = " << Ip << " (" << inet_ntoa(list_adr.sin_addr) << ")\n";
        }
        else {
            // error = "DNS error: IP isn't found.";
            return 1;
        }
    }
    else cout << "Pinging address: " << Ip << "\n";
    return 0;
}

// ���������� ���������
void finish(char* icmp, SOCKET listn) {
    closesocket(listn);                             // �������� ������
    delete[] icmp;                                  // �������� ���������
    WSACleanup();                                   // �������� ���������� Ws2_32.dll
}