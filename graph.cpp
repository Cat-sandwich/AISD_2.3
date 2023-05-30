#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "graph.h"
#include <algorithm>
#include <queue>
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
int Graph::find_edge(int from, int to)
{
	if (vertexes.size() == 0) return false;
	int index_from = find_vertex(from);
	int index_to = find_vertex(to);
	if (index_from == -1 || index_to == -1) throw "Нет искомой вершины ОТКУДА или КУДА";

	for (auto i = vertexes[index_from].edges.begin(); i != vertexes[index_from].edges.end(); i++)
	{
		if (i->id_to == to)
			return int(i - vertexes[index_from].edges.begin());
	}
	return -1;
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



void Graph::weakening(Vertex& u, Vertex& v)
{
	double w = 0;
	auto current = u.edges.begin();
	auto end = u.edges.end();

	while (current != end)
	{
		if (current->id_to == v.id_v)
			w = current->weight;
		current++;
	}
	if (v.d > u.d + w)
	{
		vertexes[find_vertex(v.id_v)].d = u.d + w;
		vertexes[find_vertex(v.id_v)].id_prev = u.id_v;
	}
}

void Graph::initialize_for_dijkstra(int from)
{
	for (auto i = this->vertexes.begin(); i != this->vertexes.end(); i++)
	{
		i->d = INT_MAX;
		i->id_prev = INT_MAX;
	}
	this->vertexes[from].d = 0;
}

int min_index(queue<Vertex>& Q, int sortedIndex)
{
	int min_i = -1;
	double min_val = INT_MAX;
	int n = Q.size();
	for (int i = 0; i < n; i++)
	{
		Vertex curr = Q.front();
		Q.pop();
		if (curr.d <= min_val && i <= sortedIndex)
		{
			min_i = i;
			min_val = curr.d;
		}
		Q.push(curr);
	}
	return min_i;
}

void insert_min_to_rear(queue<Vertex>& Q, int min_i)
{
	Vertex min_val(INT_MAX);
	int n = Q.size();
	for (int i = 0; i < n; i++)
	{
		Vertex curr = Q.front();
		Q.pop();
		if (i != min_i)
			Q.push(curr);
		else
			min_val = curr;
	}
	Q.push(min_val);
}


void Graph::sorted_Q(queue<Vertex>& Q)
{
	for (int i = 1; i <= Q.size(); i++)
	{
		int min_i = min_index(Q, Q.size() - i);
		insert_min_to_rear(Q, min_i);
	}
}
queue<Vertex> Graph::new_queue() const
{
	queue<Vertex> new_v;
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		new_v.push(vertexes[find_vertex(v->id_v)]);
	}
	return new_v;
}

queue<Vertex>Graph::update_queue(queue<Vertex> Q)
{
	queue<Vertex> new_q;
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		for (auto v = vertexes.begin(); v != vertexes.end(); v++)
		{
			if (u.id_v == v->id_v) new_q.push(vertexes[find_vertex(v->id_v)]);
		}
		Q.pop();
	}
	return new_q;
}

vector<Vertex> Graph::dijkstra(int from)
{
	if (vertexes.size() == 0) throw "Вершин нет";
	if (find_vertex(from) == -1) throw "Вершина не найдена";
	initialize_for_dijkstra(from);

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->d = INT_MAX;
		v->id_prev = INT_MAX;
	}
	vertexes[find_vertex(from)].d = 0;

	vector<Vertex> S;
	queue<Vertex> Q = new_queue();

	while (Q.empty() == false)
	{
		sorted_Q(Q);
		Vertex u = Q.front();
		Q.pop();
		S.push_back(u);
		vector<Vertex> v_neighbour = neighbours(u.id_v);
		for (auto v = v_neighbour.begin(); v != v_neighbour.end(); v++)
		{
			int i = find_vertex(v->id_v);
			weakening(u, vertexes[i]);
		}
		Q = update_queue(Q);
	}
	return S;
}

vector<Vertex> Graph::shortest_path(int id_from, int id_to)
{
	int index_from = find_vertex(id_from);
	dijkstra(vertexes[index_from].id_v);
	int index_to = find_vertex(id_to);

	vector<Vertex> way;

	while (index_to != index_from)
	{
		if (index_to != -1)
		{
			way.push_back(vertexes[index_to]);
			int id_prev = vertexes[index_to].id_prev;
			index_to = find_vertex(id_prev);
		}
		else
		{
			way.clear();
			return way;
		}
	}
	way.push_back(vertexes[index_from]);
	for (int i = 0; i < way.size() / 2; i++)
	{
		swap(way[i], way[(way.size() - 1) - i]);
	}
	return way;
}