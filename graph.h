#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>
using namespace std;

struct Edge
{
    Edge* next;
    int id_to;
    double weight;
    Edge(int id_to, double weight, Edge* next = NULL) : id_to(id_to), weight(weight) {}
};

enum Colors
{
    white = 0,
    gray = 1,
    black = 2
};

struct  Vertex
{
    int id_v;
    int id_prev;
    Colors color;
    double d;
    vector<Edge> edges;

    Vertex(int id_v)
    {
        this->id_v = id_v;
        d = 0;
    }
};


class Graph {
private:
    
    vector<Vertex> vertexes;
public:

    ~Graph();
    void delete_graph();
    //проверка-добавление-удаление вершин
    bool has_vertex(const int id_v) const;
    int find_vertex(const int id_v) const;
    void add_vertex(int add_v);
    bool remove_vertex(int remove_v);
   
    //проверка-добавление-удаление ребер
    void add_edge(int from, int to, int weight);
    bool remove_edge(int ftom, int to);
    bool has_edge(int from, const int to) const;
    
    void print() const;

    //получение всех ребер, выходящих из вершины
    vector<Edge> edges(int id_from);
    
    size_t order() const; //порядок
    size_t degree(int id_from) const; //степень

    //обход
    vector<Vertex> walk(int id_first);
    void initialize();
    vector<Vertex> neighbours(int id_v);
    vector<Vertex> search_in_width(Vertex& first_v);

    //поиск кратчайшего пути
    vector<int> shortest_path(int from, int to, int& weight) const;
    
};