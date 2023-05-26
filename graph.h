#pragma once
#include <vector>
#include <forward_list>
#include <stdio.h>
using namespace std;


class Graph {
private:
    struct Edge
    {
        Edge* next;
        int id_to;
        double weight;
        Edge(int id_to, double weight) : id_to(id_to), weight(weight) {}
    };

    enum Color
    {
        white = 0,
        gray = 1,
        black = 2
    };

    struct  Vertex
    {
        int id_v;
        Color color;
        double d;
        vector<Edge> edges;

        Vertex(int id_v)
        {
            this->id_v = id_v;
            color = white;
            d = 0;
        }
    };

    vector<Vertex> vertexes;
public:

    ~Graph();
    void delete_graph();
    //��������-����������-�������� ������
    bool has_vertex(const int id_v) const;
    int find_vertex(const int id_v) const;
    void add_vertex(int add_v);
    bool remove_vertex(int remove_v);
    vector<Vertex> vertices() const;


    //��������-����������-�������� �����
    void add_edge(int from, int to, int weight);
    bool remove_edge(int ftom, int to);
    bool remove_edge(const Edge& e); //c ������ ����������
    bool has_edge(int from, const int to) const;
    bool has_edge(const Edge& e); //c ������ ���������� � Edge

    void print() const;

    //��������� ���� �����, ��������� �� �������
    vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //�������
    size_t degree() const; //�������


    //����� ����������� ����
    vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //�����
    vector<Vertex>  walk(const Vertex& start_vertex)const;
};