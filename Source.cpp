#include <iostream>
#include <list>
#include <vector>


class Vertex
{
private:
	int num;
	int value;//можно задавать цвета(состояния)
	std::vector<Vertex *> adjacent_vertices;
	int power;
public:
	Vertex() {};
	Vertex(int num_) { num = num_; };
	Vertex(int num_, int value_) { num = num_; value = value_; };

	int get_num() { return num; };
	int get_value() { return value; };

	void set_value(int value_) { value = value_; };
	void set_adjacent(Vertex * ver)//прописать функцию, которая возвращает вектор смежных вершин
	{
		adjacent_vertices.push_back(ver);
		//будет постоянно увеличиваться при добавлении ребра
	};

	
};


class Edge
{
private:

	std::pair<Vertex *, Vertex *> position;//можно через указатели
	std::pair<int, int> pos;//либо прописывать номер вершины
	int value;

public:

	Edge(int num1, int num2) { pos.first = num1; pos.second = num2; };
	Edge(Vertex * num1, Vertex * num2)
	{
		position.first = num1; 
		position.second = num2;
		position.first->set_adjacent(position.second);
		position.second->set_adjacent(position.first);
		pos.first = position.first->get_num();
		pos.second = position.second->get_num();

	};

	std::pair<Vertex *, Vertex *> get_position() { return position; };
	std::pair<int, int> get_pos() { return pos; };
	int get_value() { return value; };

	void set_pos(int pos1, int pos2) { pos.first = pos1; pos.second = pos2; };
	void set_position(Vertex * pos1, Vertex * pos2) { position.first = pos1; position.second = pos2; };
	void set_value(int value_) { value = value_; };

	void synchronization(std::vector<Vertex *> vertices)
	{
		Vertex *a, *b;
		for (int i = 0; i < vertices.size(); ++i)
		{
			if (vertices[i]->get_num() == pos.first)
			{
				a = vertices[i];
			}
			if (vertices[i]->get_num() == pos.second)
			{
				b = vertices[i];
			}
		}
		a->set_adjacent(b);
		b->set_adjacent(a);
		set_position(a, b);

	}
	
	//подумала мб прописать синхронизатор между номером вершин и их указателями...тип как только заносим что-то одно из них
	//автоматически ищется записывается в другое
	//я подумала что будет удобно вбивать ребра по номерам вершин, а в программе лучше пользоваться указателями
};

class Graph
{
public:
	std::vector<Vertex *> vertices;
	std::vector<Edge *> edges;
	int size;
	std::vector<Vertex *> dfs_vertices;

	Graph(int size_)
	{
		//генератор графов))
		size = size_;
		for (int i = 0; i < size; i++)
		{
			vertices.push_back(new Vertex(i));
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = i+1; j < size; ++j)
			{
				if (rand() % 2 == 1)
				{
					edges.push_back(new Edge(vertices[i], vertices[j]));
				}
			}
		}
	};

	void print()
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			std::cout << vertices[i]->get_num() << std::endl;
		}
		for (int i = 0; i < edges.size(); ++i)
		{
			std::cout << edges[i]->get_pos().first << "---" << edges[i]->get_pos().second << std::endl;
		}
	}
	std::vector<Vertex *> dfs(int v)
	{
		//тут у меня отключился мозг(( пока не сообразила...но я думаю все тип топ
	};
	//прописать функцию генерации разных графов заданного размера
	//мб прописать функцию dfs от заданной вершины которая возвращает вектор посещений 
};


int main()
{
	setlocale(LC_ALL, "Russian");
	//решила все таки использовать вектор, так лист не поддерживает произвольный доступ к элементу
	//вектор будет подходить так как мы в процессе работы нам не нужно удалять вершины или ребра
	//нам нужно только извенять состояния и значения вершин и ребер
	//так что я думаю все будет ок))

	Graph g(10);
	g.print();

	/*
	int V_size = 4, E_size = 4;
	std::vector<Vertex *> vertices;
	std::vector<Edge *> edges;

	for (int i = 0; i < V_size; i++)
	{
		vertices.push_back(new Vertex(i));
	}

	for (int i = 0; i < E_size; i++)
	{
		int num1, num2;
		std::cout << "Enter vertecies  ";
		std::cin >> num1 >> num2;
		edges.push_back(new Edge(num1, num2));
	}

	for (int i = 0; i < edges.size(); ++i)
	{
		std::cout << edges[i]->get_pos().first << " " << edges[i]->get_pos().second << std::endl;
	}

	*/

	std::cin.get();
	std::cin.get();


	return 0;
}