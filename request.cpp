#include "main.h"
#include "request.h"


// ����������� ����� (RFC1071)
USHORT crc2(USHORT* addr, int count)
{
    // http://www.ietf.org/rfc/rfc1071.txt ������� CRC
    register long sum = 0;
    while (count > 1) {
        /*  This is the inner loop */
        sum += *(unsigned short*)addr++;
        count -= 2;
    }
    /*  Add left-over byte, if any */
    if (count > 0)
        sum += *(unsigned char*)addr;
    /*  Fold 32-bit sum to 16 bits */
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);
    return (USHORT)(~sum);
}

// ������ ������ + ������� �����
int assembling(IcmpHeader& pac, IcmpHeader*& Packet, char*& Icmp) {
    try {
        pac = { 8, 0, 0x2, 0, (USHORT)GetCurrentProcessId() }; // ���� �� ��������� ��� ��������� ��� � ���� ����
        // "�������������" � ������ 32 "Z", ����� ��������� ��� �������� �����
        Icmp = new char[PACKET_SIZE];
        memcpy(Icmp, &pac, sizeof(pac));
        memset(Icmp + sizeof(pac), 'Z', 32);
        Packet = (IcmpHeader*)Icmp;
        Packet->i_crc = crc2((USHORT*)Packet, PACKET_SIZE); // ������� ����������� ����� ������, ��������� + ������
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
    return 0;
}

// �������� ICMP �������
int request(IcmpHeader* Packet, SOCKET listn, SOCKADDR_IN list_adr) {
    try {
        sendto(listn, (char*)PACKET_, PACKET_SIZE, 0, (sockaddr*)&list_adr, sizeof(list_adr)); // �������� ICMP
        Sleep(SENDING_TIMEOUT);
        return 0;
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
}