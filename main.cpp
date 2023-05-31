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
    cout << "Откуда идет ребро:" << endl;
    int id_from = check();
    while (!g.has_vertex(id_from))
    {
        cout << "такой вершины нет, повторите попытку" << endl;
        id_from = check();
    }
    cout << "Куда идет ребро:" << endl;
    int id_to = check();
    while (!g.has_vertex(id_to))
    {
        cout << "Такой вершины нет, повторите попытку" << endl;
        id_to = check();
    }
    cout << "Вес ребра: ";
    int weight = check();
    while (weight < 0)
    {
        cout << "Вес ребра должен быть положительным (тк у нас тут Дейкстра): ";
        weight = check();
    }
    g.add_edge(id_from, id_to, weight);
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
    while (!g.has_vertex(id_from))
    {
        cout << "такой вершины нет, повторите попытку" << endl;
        id_from = check();
    }
    cout << "До какой вершины идти?" << endl;
    int id_to = check();
        while (!g.has_vertex(id_to))
    {
        cout << "Такой вершины нет, повторите попытку" << endl;
        id_to = check();
    }
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
float round_two(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

void task(Graph& g)
{
    vector<Vertex> tmp = g.get_vertexes();
    vector < double > pair = g.find_storage();
    cout << "Склад: " << tmp[int(pair[0])].id_v << endl;
    cout << "Среднее расстояние до всех вершин: " << pair[1] << endl << endl;
    int id_from = tmp[int(pair[0])].id_v;
    double count = 0;
    cout << "Все пути из "<< id_from << ":";
    for(int i = 0 ; i< tmp.size(); i++)
    {
        vector<Vertex> way = g.shortest_path(id_from, tmp[i].id_v);
        if(id_from != tmp[i].id_v)
        {
            
            double len_way = 0;
            double delta = 0;
            cout << endl << "Путь:" << endl;
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
    cout << endl << endl << "Проверка среднего пути: " << round_two(count / (tmp.size() - 1));
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
        cout << "Граф:" << endl;
        print(test_graph);
        info();
        menu = check_info();
        while (menu < 0 || menu > 11)
        {
            cout << "Введите корректное значение!";
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
                cout << "Ошибка: " << error_message;
                getchar();
            }
            getchar();
        }
        else if (menu == 11)
        {

            try
            {
                system("cls");
                cout << "Граф:" << endl;
                print(sviaz_graph);
                cout << endl;
                operatoin[10](sviaz_graph);
            }
            catch (const char* error_message)
            {
                cout << "Ошибка: " << error_message;
                getchar();
            }
            getchar();

        }
    }
    return 0;
}