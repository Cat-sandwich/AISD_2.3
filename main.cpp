#include <iostream>
#include "graph.h"
using namespace std;

int check()
{
    int number;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Incorrect value" << endl;
    }
    return number;
}

int check_info()
{
    int n = check();
    while (n > 13 || n <= 0)
    {
        cout << "������������ ��������" << endl << "��������� ������� �����: ";
        n = check();
    }
    return n;
}


void info()
{
    cout << "�������:" << endl;
    cout << "1 - �������� �������" << endl;
    cout << "2 - �������� �����" << endl;
    cout << "3 - ����� �������" << endl;
    cout << "4 - ����� �����" << endl;
    cout << "5 - ������� �������" << endl;
    cout << "6 - ������� �����" << endl;
    cout << "7 - ������� �������" << endl;
    cout << "8 - ������� (���-�� ������)" << endl;
    cout << "9 - �����" << endl;
    cout << "10 - �������� ��������" << endl;
    cout << "11 - �������" << endl;
    cout << "0 - go out" << endl;
}

int main()
{
    int menu;
    info();
    menu = check_info();
    while (menu < 13)
    {
        
        
        
        menu = check_info();
    }
    return 0;
}