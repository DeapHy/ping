#include "ping.h"
#include "init.h"


/*В данном файле хранятся все функции, связанные с начальной инициализацией программы
* Что находится в данном файле:
* 1. Проверка входных параметров
* 2. Инициализация необходимых структур
*/

// Проверка аргументов
int checkArgs(int argc, LOGINFO& logger) {
    if (argc < 2) {                                 // Проверка на количество вводимых параметров
        cout << "usage: ping <IP_or_Host>" << endl;
        // error = "Wrong arguments.";
        return 1;                                   // Завершение с ошибкой
    }
    return 0;                                       // Успешное завершение
}

// Инициализация всех структур, а также сокета
int init(char* Ip, SOCKADDR_IN& list_adr, SOCKADDR_IN& bnd, SOCKADDR_IN& out_, WSADATA& wsd, SOCKET& listn, LOGINFO& logger) {
    try {
        int timeout = TIMEOUT;                          // Таймаут при отправке ECHO-сообщений сокетом
        list_adr.sin_addr.S_un.S_addr = inet_addr(Ip);  // Адрес для работы
        list_adr.sin_family = AF_INET;                  // Всегда такое значение
        list_adr.sin_port = htons(6666);                // Порт для работы (htons переводит порт в вид для работы с TCP/IP. Если тут 0, то ОС выделит свободный порт сама)

        bnd.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   // Связывает сокет со всеми доступными интерфейсами
        bnd.sin_family = AF_INET;                       // Всегда такое значение
        bnd.sin_port = htons(6666);                     // Порт для работы (htons переводит порт в вид для работы с TCP/IP. Если тут 0, то ОС выделит свободный порт сама)

        out_.sin_family = AF_INET;
        if (WSAStartup(0x202, &wsd) != 0) {             // Инициализация библиотеки WinSock.dll (<Версия?>, <Указатель на структуру WSADATA>) (НУЖНО ОБРАБОТАТЬ НА ОШИБКИ НА ВСЯКИЙ)
            // Ошибка сокета
            return 1;
        }                                                   

        listn = WSASocket(AF_INET, SOCK_RAW, IPPROTO_ICMP, 0, 0, WSA_FLAG_OVERLAPPED);        // Создает сокет для транспортных целей (https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsasocketa)
        setsockopt(listn, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));         // Таймаут получения (https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-setsockopt)
        return 0;
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
}

// Преобразование DNS в IP
int getIPByName(SOCKADDR_IN& list_adr, SOCKADDR_IN& bnd, char* Ip, SOCKET& listn, LOGINFO& logger) {
    struct hostent* hp = NULL;
    if (list_adr.sin_addr.S_un.S_addr == INADDR_NONE) {
        if ((hp = gethostbyname(Ip)) != NULL) // Ищем на сервере IP, подходящий данному доменному имени
        {
            // memcpy(1,2,3) копируем и вставляем информацию из 2 размером 3 в 1 
            // 1 - Айпи сокета, 2 - айпи в байтах к обращаемому хосту, 3 длина адреса в байтах
            memcpy(&(list_adr.sin_addr.S_un.S_addr), hp->h_addr_list[0], hp->h_length);
            list_adr.sin_family = hp->h_addrtype; // Переопределяем принадлежность
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

// Завершение программы
void finish(char* icmp, SOCKET listn) {
    closesocket(listn);                             // Закрытие сокета
    delete[] icmp;                                  // Удаление указателя
    WSACleanup();                                   // Закрытие библиотеки Ws2_32.dll
}