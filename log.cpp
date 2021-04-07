/* ���������� �������� �� ������ ���
* ������ ��� ����� ����, ������� ��������
* ����� ����� ������� ��� �������� � ���� ��� ������, � ���������� ������� ������ �������
* 
*/
#include "ping.h"
#include "log.h"


// ������� ������ �� �����
void errorOutput(string error) {
    cout << error << endl;          // ����� ������
}

// �������� ����� ����
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

// ������� ���������� ������ ��������� (�� ������)
void resultsOutput() {

}