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
        cout << "Некорректное значение:" << endl;
    }
    return number;
}

int check_info()
{
    int n = check();
    while (n > 13 || n < 0)
    {
        cout << "Некорректное значение" << endl << "Повторите попытку ввода: ";
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
    cout << "Введите вершину, которую хотиет добавить: " << endl;
    int id = check();
    g.add_vertex(id);
}


void add_edge(Graph& g)
{
    cout << "Введите вершины для создания ребра: " << endl;
    cout << "Откуда идет ребро: ";
    int from = check();
    cout << "Куда идет ребро: ";
    int to = check();
    cout << "Вес ребра: ";
    int weight = check();
    g.add_edge(from, to, weight);
}


void find_vertex(Graph& g)
{
    cout << "Какую вершину хотите найти: " << endl;
    int id = check();
    if (g.find_vertex(id) != -1)
        cout << "вершина найдена)" << endl;
    else
        cout << "вершина не найдена(";
    getchar();
}


void find_edge(Graph& g)
{
    cout << "Введите:" << endl;
    cout << "Откуда идет ребро: ";
    int from = check();
    cout << "Куда идет ребро: ";
    int to = check();
    if (g.has_edge(from, to))
        cout << "Такое ребро есть)" << endl;
    else
        cout << "Такого ребра нет(";
    getchar();
}


void delete_vertex(Graph& g)
{
    cout << "Какую вершину хотите удалить?" << endl;
    int id = check();
    g.remove_vertex(id);
}


void delete_edge(Graph& g)
{
    cout << "Какое ребро хотите удалить?" << endl;
    cout << "Откуда идет ребро: ";
    int from = check();
    cout << "Куда идет ребро: ";
    int to = check();
    g.remove_edge(from, to);
}

void degree(Graph& g)
{
    cout << "Для какой вершины считаем степень?" << endl;
    int id = check();
    cout << "Степень вершины " << id << " = " << g.degree(id);
    getchar();
}

void order(Graph& g)
{
    cout << "Порядок графа: " << g.order();
    getchar();
}

void walk(Graph& g)
{
    cout << "С какой вершины начнем обход?" << endl;
    int id = check();
    vector<Vertex> way = g.walk(id);
    for (auto i = way.begin(); i != way.end(); i++)
        cout << i->id_v << " -> ";
    cout << "NULL" << endl;
    getchar();
}

void shortest_path(Graph& g)
{
    cout << "От какой вершины идти?" << endl;
    int id_from = check();
    cout << "До какой вершины идти?" << endl;
    int id_to = check();
    vector<Vertex> way = g.shortest_path(id_from, id_to);
   
    double len_way = 0;
    double delta = 0;
    cout << "Путь:" << endl;
    for (auto w = way.begin(); w != way.end(); w++)
    {
        
        if(w->id_v != id_from)
            cout<< " -(" << w->d - delta << ")-> " << w->id_v ;
        else
            cout << w->id_v;
        if (w->id_v == id_to) len_way = w->d;
        delta = w->d;
    }
    
    cout << endl << "Длина пути: " << len_way << endl;
    getchar();
}
void info()
{
    cout << endl;
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
    cout << "0 - завершить работу" << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Graph test_graph;
    test_graph.add_vertex(6);
    test_graph.add_vertex(8);
    test_graph.add_vertex(4);
    test_graph.add_vertex(3);
    test_graph.add_vertex(5);
    test_graph.add_vertex(12);
    test_graph.add_vertex(9);
    test_graph.add_edge(8, 6, 1);
    test_graph.add_edge(6, 12, 8);
    test_graph.add_edge(4, 8, 2);
    test_graph.add_edge(4, 6, 4);

    test_graph.add_edge(8, 12, 10);
    test_graph.add_edge(8, 5, 7);
    test_graph.add_edge(8, 3, 1);
    test_graph.add_edge(3, 5, 5);
    test_graph.add_edge(3, 9, 3);

    int menu = -1;
    
    void (*operatoin[12])(Graph & obj) = { add_vertex,add_edge,find_vertex,find_edge,
        delete_vertex,delete_edge, degree, order, walk, shortest_path };
    cout<< test_graph.find_edge(4, 6);
    while (menu < 13)
    {
        system("cls");
        cout << "Граф:" << endl;
        print(test_graph);
        info();
        menu = check_info();
        while (menu < 0 || menu > 10)
        {
            cout << "Введите корректное значение!";
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
            cout<<"Ошибка: "<< error_message;
            getchar();
        }
        getchar();
    }
    return 0;
}