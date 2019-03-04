#include <iostream>
#include <list>
#include <vector>
#include <ctime>


enum Colors { White, Grey, Black };
class Vertex
{
private:
	int num;
	int value=White;//можно задавать цвета(состояния) цвет по умолчанию
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

	void synchronization(std::vector<Vertex *> vertieces)
	{
		Vertex *a, *b;
		for (int i = 0; i < vertieces.size(); ++i)
		{
			if (vertieces[i]->get_num() == pos.first)
			{
				a = vertieces[i];
			}
			if (vertieces[i]->get_num() == pos.second)
			{
				b = vertieces[i];
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
	int n;//количество вершин
	int m; //количество ребер

	Graph(int n_, int m_)
	{
		//генератор графов))
		//Это ооочень круто! Но мы не можем контролировать количество ребер, 
		//а нам его нужно регулировать, чтобы проводить разные эксперименты в отчете
		//поправила, все работает
		n = n_;
		m = m_;
		for (int i = 0; i < n; i++)
		{
			vertices.push_back(new Vertex(i));
		}

		for (int k = 0; k < m; ++k)
		{
			bool f = 1;
			int i, j;
			while  (f == 1)
			{
				f = 0;
				i = (rand() % (n - 1)); //рандомное число от 0 до n-2
				j = (rand() % (n - i - 1)) + i + 1;//получаем рандомное число от i+1 до n-1 - индекс конца ребра
				for (int l = 0; l < edges.size(); l++)
				{
					if ((edges[l]->get_pos().first == i) && (edges[l]->get_pos().second == j))
					{
						f = 1;
						break;
					}
				}
			}
			
			edges.push_back(new Edge(vertices[i], vertices[j]));
			
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
	}
	//прописать функцию генерации разных графов заданного размера
	//мб прописать функцию dfs от заданной вершины которая возвращает вектор посещений 
};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	//решила все таки использовать вектор, так лист не поддерживает произвольный доступ к элементу
	//вектор будет подходить так как мы в процессе работы нам не нужно удалять вершины или ребра
	//нам нужно только извенять состояния и значения вершин и ребер
	//так что я думаю все будет ок))

	Graph g(5, 5);
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