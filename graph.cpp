#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "graph.h"
#include <algorithm>
using namespace std;


Graph::~Graph()
{
	delete_graph();
}

void Graph::delete_graph()
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->edges.clear();
	}
	vertexes.clear();
}

bool Graph::has_vertex(const int id_v) const
{
	if (vertexes.size() == 0) return false;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (i->id_v == id_v)
			return true;
	}
	return false;
}

void Graph::add_vertex(int add_v)
{
	if (has_vertex(add_v)) throw "Вершина с таким ID уже есть";
	Vertex v(add_v);
	vertexes.push_back(add_v);
}

int Graph::find_vertex(const int id_v) const
{
	if (vertexes.size() == 0) return -1;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (i->id_v == id_v)
			return int(i - vertexes.begin());
	}	
	return -1;
}

bool Graph::has_edge(int from, const int to) const
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Нет искомой вершины ОТКУДА или КУДА";

	for (auto i = vertexes[index_from].edges.begin(); i != vertexes[index_from].edges.end(); i++)
	{
		if (i->id_to == to)
			return true;
	}
	return false;
}

bool Graph::remove_edge(int from, int to)
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Нет искомой вершины ОТКУДА или КУДА";
	int index_erase = 0;

	for (auto i = vertexes[index_from].edges.begin(); i != vertexes[index_from].edges.end(); i++)
	{
		
		if (i->id_to == to)
		{
			break;
		}
		index_erase++;
	}
	vertexes[index_from].edges.erase(vertexes[index_from].edges.begin() + index_erase);
	return true;	
}

bool Graph::remove_vertex(int remove_v)
{
	if (vertexes.size() == 0) return false;
	int remove_index = find_vertex(remove_v);
	if (remove_index == -1) throw "Нет такой вершины";

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if(has_edge(v->id_v, remove_v))
			remove_edge(v->id_v, remove_v);
	}

	vertexes[remove_index].edges.clear();
	vertexes.erase(vertexes.begin() + remove_index);
	return true;
}

void Graph::add_edge(int from, int to, int weight)
{
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Нет искомой вершины ОТКУДА или КУДА";

	Edge tmp(to, weight);
	vertexes[index_from].edges.push_back(tmp);
}

void Graph::print() const
{
	bool flag = false;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		flag = false;
		for (auto j = i->edges.begin(); j != i->edges.end(); j++)
		{
			cout << i->id_v << " --("<< j->weight<<")--> ";
			cout << j->id_to<< " ; ";
			flag = true;
		}
		if (flag == false)
			cout << i->id_v << " -|";
		cout << endl;
	}
}

vector<Edge> Graph::edges(int id_from)
{
	int index = find_vertex(id_from);
	if (index == -1) throw "Вершина не найдена";

	return vertexes[index].edges;
}

size_t Graph::order() const
{
	return int(vertexes.size());
}

size_t Graph::degree(int id_from) const
{
	if (vertexes.size() == 0) throw "Вершин нет";
	int index = find_vertex(id_from);
	if (index == -1) throw "Вершина не найдена";
	int count = 0;
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (has_edge(i->id_v, id_from))
			count++;
	}
	return count + vertexes[index].edges.size();
}

vector<int> Graph::shortest_path(int from, int to, int& weight)const
{
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Нет искомой вершины ОТКУДА или КУДА";

	
}

vector<Vertex> Graph::neighbours(int id_v)
{
	if (vertexes.size() == 0) throw "Вершин нет";
	int index = find_vertex(id_v);
	if (index == -1) throw "Вершина не найдена";

	vector<Vertex> v_neighbours;

	for (auto i = vertexes[index].edges.begin(); i != vertexes[index].edges.end(); i++)
	{
		int v = find_vertex(i->id_to);
		if(v != -1)
			v_neighbours.push_back(vertexes[v]);
	}
	return v_neighbours;
}
void Graph::initialize()
{
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		i->color = white;
		i->id_prev = INT_MAX;
	}
}

vector<Vertex> Graph::search_in_width(Vertex& start_v)
{
	vector<Vertex> way;
	queue<Vertex> Q;
	vertexes[find_vertex(start_v.id_v)].color = gray;
	Q.push(vertexes[find_vertex(start_v.id_v)]);
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		Q.pop();
		way.push_back(u);
		vector<Vertex> v_neighbours = neighbours(u.id_v);
		for (auto v = v_neighbours.begin(); v != v_neighbours.end(); v++)
		{
			if (v->color == white)
			{
				int id = find_vertex(v->id_v);
				if (id != 0)
				{
					vertexes[id].color = gray;
					vertexes[id].id_prev = u.id_v;
				}
				Q.push(vertexes[id]);

				
			}
		}
		vertexes[find_vertex(u.id_v)].color = black;
	}
	return way;
}

vector<Vertex> Graph::walk(int id_first)
{

	this->initialize();
	int index_first = find_vertex(id_first);
	return search_in_width(vertexes[index_first]);
}