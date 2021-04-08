#include "main.h"
#include "response.h"


// јнализ полученного пакета
unsigned int analyze(int i, char* data, SOCKADDR_IN* adr) //разбор ответа
{
    try {
        char* Ip;
        IpHeader* pHe = (IpHeader*)data;
        char Name[NI_MAXHOST] = { 0 };
        char servInfo[NI_MAXSERV] = { 0 };
        Ip = inet_ntoa(adr->sin_addr);
        int TTL = (int)pHe->ttl;
        data += sizeof(IpHeader);
        IcmpHeader* ic = (IcmpHeader*)data;
        if (GetCurrentProcessId() == ic->i_id) //проверка что это мы слали.
            cout << i << ": " << "Reply from " << Ip << " with TTL = " << TTL << ".\n";
        else
            cout << "Fake packet\n";
        memset(data, 0, 0);
        return 0;
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
}

// ѕолучение ICMP ответа
int response(SOCKET listn, char bf[], SOCKADDR_IN& out_, int k) {
    try {
        bool timedout = false;
        int outlent = sizeof(out_);
        if (recvfrom(listn, bf, BUFFER_SIZE, 0, (sockaddr*)&out_, &outlent) == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAETIMEDOUT)
            {
                cout << "Request timeout\n";
                timedout = true;
            }
        }
        if (!timedout) {
            analyze(k + 1, bf, &out_);
        }
        return 0;
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
}