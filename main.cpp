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
    cout << "������ ���� �����:" << endl;
    int id_from = check();
    while (!g.has_vertex(id_from))
    {
        cout << "����� ������� ���, ��������� �������" << endl;
        id_from = check();
    }
    cout << "���� ���� �����:" << endl;
    int id_to = check();
    while (!g.has_vertex(id_to))
    {
        cout << "����� ������� ���, ��������� �������" << endl;
        id_to = check();
    }
    cout << "��� �����: ";
    int weight = check();
    while (weight < 0)
    {
        cout << "��� ����� ������ ���� ������������� (�� � ��� ��� ��������): ";
        weight = check();
    }
    g.add_edge(id_from, id_to, weight);
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

void walk(Graph& g)
{
    cout << "� ����� ������� ������ �����?" << endl;
    int id = check();
    vector<Vertex> way = g.walk(id);
    for (auto i = way.begin(); i != way.end(); i++)
        cout << i->id_v << " -> ";
    cout << "NULL" << endl;
    getchar();
}

void shortest_path(Graph& g)
{
    cout << "�� ����� ������� ����?" << endl;
    int id_from = check();
    while (!g.has_vertex(id_from))
    {
        cout << "����� ������� ���, ��������� �������" << endl;
        id_from = check();
    }
    cout << "�� ����� ������� ����?" << endl;
    int id_to = check();
        while (!g.has_vertex(id_to))
    {
        cout << "����� ������� ���, ��������� �������" << endl;
        id_to = check();
    }
    vector<Vertex> way = g.shortest_path(id_from, id_to);
   
    double len_way = 0;
    double delta = 0;
    cout << "����:" << endl;
    for (auto w = way.begin(); w != way.end(); w++)
    {
        
        if(w->id_v != id_from)
            cout<< " -(" << w->d - delta << ")-> " << w->id_v ;
        else
            cout << w->id_v;
        if (w->id_v == id_to) len_way = w->d;
        delta = w->d;
    }
    
    cout << endl << "����� ����: " << len_way << endl;
    
    getchar();
}
float round_two(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

void task(Graph& g)
{
    vector<Vertex> tmp = g.get_vertexes();
    vector < double > pair = g.find_storage();
    cout << "�����: " << tmp[int(pair[0])].id_v << endl;
    cout << "������� ���������� �� ���� ������: " << pair[1] << endl << endl;
    int id_from = tmp[int(pair[0])].id_v;
    double count = 0;
    cout << "��� ���� �� "<< id_from << ":";
    for(int i = 0 ; i< tmp.size(); i++)
    {
        vector<Vertex> way = g.shortest_path(id_from, tmp[i].id_v);
        if(id_from != tmp[i].id_v)
        {
            
            double len_way = 0;
            double delta = 0;
            cout << endl << "����:" << endl;
            for (auto w = way.begin(); w != way.end(); w++)
            {

                if (w->id_v != id_from)
                {
                    count += w->d - delta;
                    cout << " -(" << w->d - delta << ")-> " << w->id_v;
                }
                else
                    cout << w->id_v;
                if (w->id_v == tmp[i].id_v) len_way = w->d;
                delta = w->d;
            }
        }
       
    }
    cout << endl << endl << "�������� �������� ����: " << round_two(count / (tmp.size() - 1));
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
void create_graph(Graph & g)
{
    g.add_vertex(6);
    g.add_vertex(8);
    g.add_vertex(4);
    g.add_vertex(3);
    g.add_vertex(5);
    g.add_vertex(12);
    g.add_vertex(9);
    g.add_edge(8, 6, 1);
    g.add_edge(6, 12, 8);
    g.add_edge(4, 8, 2);
    g.add_edge(4, 6, 4);

    g.add_edge(8, 12, 10);
    g.add_edge(8, 5, 7);
    g.add_edge(8, 3, 1);
    g.add_edge(3, 5, 5);
    g.add_edge(3, 9, 3);

}

void create_sviaz_graph(Graph& g)
{
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(6);
    g.add_vertex(5);
    g.add_vertex(4);

    g.add_edge(1, 5, 3);
    g.add_edge(1, 4, 1);
    g.add_edge(2, 1, 9);
    g.add_edge(4, 2, 8);
    g.add_edge(4, 3, 5);

    g.add_edge(3, 2, 2);
    g.add_edge(3, 5, 4);

    g.add_edge(5, 6, 7);
    g.add_edge(6, 1, 2);

}
int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Graph test_graph, sviaz_graph ;
    create_graph(test_graph);
    create_sviaz_graph(sviaz_graph);
    int menu = -1;
    
    void (*operatoin[12])(Graph & obj) = { add_vertex,add_edge,find_vertex,find_edge,
        delete_vertex,delete_edge, degree, order, walk, shortest_path, task };
    cout<< test_graph.find_edge(4, 6);
    while (menu < 13)
    {
        system("cls");
        cout << "����:" << endl;
        print(test_graph);
        info();
        menu = check_info();
        while (menu < 0 || menu > 11)
        {
            cout << "������� ���������� ��������!";
            menu = check_info();
        }
        if (menu == 0)
            return 0;
        else if (menu <= 10)
        {
            try
            {
                operatoin[menu - 1](test_graph);
            }
            catch (const char* error_message)
            {
                cout << "������: " << error_message;
                getchar();
            }
            getchar();
        }
        else if (menu == 11)
        {

            try
            {
                system("cls");
                cout << "����:" << endl;
                print(sviaz_graph);
                cout << endl;
                operatoin[10](sviaz_graph);
            }
            catch (const char* error_message)
            {
                cout << "������: " << error_message;
                getchar();
            }
            getchar();

        }
    }
    return 0;
}