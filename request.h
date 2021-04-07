#pragma once
USHORT crc2(USHORT*, int);
int assembling(IcmpHeader&, IcmpHeader*&, char*&);
int request(IcmpHeader*, SOCKET, SOCKADDR_IN);