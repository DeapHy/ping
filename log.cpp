/* Собственно работать вы будете тут
* Пишите тут любую инфу, которую захотите
* Думаю стоит указать что включает в себя это модуль, и конкретнее описать каждую функцию
* 
*/
#include "ping.h"
#include "log.h"


// Выводит ошибки на экран
void errorOutput(string error) {
    cout << error << endl;          // Вывод ошибки
}

// Создание файла лога
int createLog(ofstream& log) {
    try {
        char buffer[256];               
        DWORD size;                     
        size = sizeof(buffer);          
        GetUserNameA(buffer, &size);    
        string userName = buffer;       

        log.open("C:/Users/" + userName + "/Desktop/Ping_log.txt", std::ios::app);
        log.close();
        return 0;
    }
    catch (std::exception& e) {
        // error = e.what();
        return 1;
    }
}

// Выводит статистику работы программы (не готово)
void resultsOutput() {

}