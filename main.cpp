#include <iostream>
#include "graph.h"
#include <Windows.h>
using namespace std;

int check()
{
    int number;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "������������ ��������:" << endl;
    }
    return number;
}

int check_info()
{
    int n = check();
    while (n > 13 || n < 0)
    {
        cout << "������������ ��������" << endl << "��������� ������� �����: ";
        n = check();
    }
    return n;
}

void print(Graph& g)
{
    g.print();
}

void add_vertex(Graph& g)
{
    cout << "������� �������, ������� ������ ��������: " << endl;
    int id = check();
    g.add_vertex(id);
}


void add_edge(Graph& g)
{
    cout << "������� ������� ��� �������� �����: " << endl;
    cout << "������ ���� �����: ";
    int from = check();
    cout << "���� ���� �����: ";
    int to = check();
    cout << "��� �����: ";
    int weight = check();
    g.add_edge(from, to, weight);
}


void find_vertex(Graph& g)
{
    cout << "����� ������� ������ �����: " << endl;
    int id = check();
    if (g.find_vertex(id) != -1)
        cout << "������� �������)" << endl;
    else
        cout << "������� �� �������(";
    getchar();
}


void find_edge(Graph& g)
{
    cout << "�������:" << endl;
    cout << "������ ���� �����: ";
    int from = check();
    cout << "���� ���� �����: ";
    int to = check();
    if (g.has_edge(from, to))
        cout << "����� ����� ����)" << endl;
    else
        cout << "������ ����� ���(";
    getchar();
}


void delete_vertex(Graph& g)
{
    cout << "����� ������� ������ �������?" << endl;
    int id = check();
    g.remove_vertex(id);
}


void delete_edge(Graph& g)
{
    cout << "����� ����� ������ �������?" << endl;
    cout << "������ ���� �����: ";
    int from = check();
    cout << "���� ���� �����: ";
    int to = check();
    g.remove_edge(from, to);
}

void degree(Graph& g)
{
    cout << "��� ����� ������� ������� �������?" << endl;
    int id = check();
    cout << "������� ������� " << id << " = " << g.degree(id);
    getchar();
}

void order(Graph& g)
{
    cout << "������� �����: " << g.order();
    getchar();
}


void info()
{
    cout << endl;
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
    cout << "0 - ��������� ������" << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Graph test_graph;
    test_graph.add_vertex(6);
    test_graph.add_vertex(7);
    test_graph.add_vertex(4);
    test_graph.add_vertex(1);
    test_graph.add_edge(7, 1, 1);
    test_graph.add_edge(6, 4, 2);
    test_graph.add_edge(4, 7, 20);
    test_graph.add_edge(4, 6, 6);
    int menu = -1;
    
    void (*operatoin[12])(Graph & obj) = { add_vertex,add_edge,find_vertex,find_edge,
        delete_vertex,delete_edge, degree, order };
    
    while (menu < 13)
    {
        system("cls");
        cout << "����:" << endl;
        print(test_graph);
        info();
        menu = check_info();
        while (menu < 0 || menu > 8)
        {
            cout << "������� ���������� ��������!";
            menu = check_info();
        }
        if (menu == 0)
            return 0;
        try 
        {
            operatoin[menu - 1](test_graph);
        }
        catch (const char* error_message)
        {
            cout<<"������: "<< error_message;
            getchar();
        }
        getchar();
    }
    return 0;
}