#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>
#include <queue>
using namespace std;

struct Edge
{
    int id_to;
    double weight;
    Edge(int id_to, double weight) : id_to(id_to)
    {
        if (weight < 0)
        {
            this->weight = 0;
        }
        this->weight = weight;
    }
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

    Vertex() {};
    Vertex(int id_v)
    {
        this->id_v = id_v;
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
    int find_edge(int from, int to);
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
    void weakening(Vertex& u, Vertex& v);
    vector<Vertex> shortest_path(int id_from, int id_to);
    void initialize_for_dijkstra(int from);
    void dijkstra(int from);
    void sorted_Q(queue<Vertex>& Q);
    queue<Vertex> update_queue(queue<Vertex> Q);

    vector<double> find_storage();
    vector<Vertex> get_vertexes();
    bool sviaz();
};