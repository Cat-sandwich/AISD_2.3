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
        cout << "Некорректное значение" << endl << "Повторите попытку ввода: ";
        n = check();
    }
    return n;
}


void info()
{
    cout << "Введите:" << endl;
    cout << "1 - добавить вершину" << endl;
    cout << "2 - добавить ребро" << endl;
    cout << "3 - найти вершину" << endl;
    cout << "4 - найти ребро" << endl;
    cout << "5 - удалить вершину" << endl;
    cout << "6 - удалить ребро" << endl;
    cout << "7 - степень вершины" << endl;
    cout << "8 - порядок (кол-во вершин)" << endl;
    cout << "9 - обход" << endl;
    cout << "10 - алгоритм Дейкстры" << endl;
    cout << "11 - задание" << endl;
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