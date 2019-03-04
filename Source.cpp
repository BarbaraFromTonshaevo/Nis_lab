#include <iostream>
#include <list>
#include <vector>
#include <ctime>


enum Colors { White, Grey, Black };
class Vertex
{
private:
	int num;
	int value=White;//����� �������� �����(���������) ���� �� ���������
	std::vector<Vertex *> adjacent_vertices;
	int power;
public:
	Vertex() {};
	Vertex(int num_) { num = num_; };
	Vertex(int num_, int value_) { num = num_; value = value_; };

	int get_num() { return num; };
	int get_value() { return value; };

	void set_value(int value_) { value = value_; };
	void set_adjacent(Vertex * ver)//��������� �������, ������� ���������� ������ ������� ������
	{
		adjacent_vertices.push_back(ver);
		//����� ��������� ������������� ��� ���������� �����
	};

	
};


class Edge
{
private:

	std::pair<Vertex *, Vertex *> position;//����� ����� ���������
	std::pair<int, int> pos;//���� ����������� ����� �������
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
	
	//�������� �� ��������� ������������� ����� ������� ������ � �� �����������...��� ��� ������ ������� ���-�� ���� �� ���
	//������������� ������ ������������ � ������
	//� �������� ��� ����� ������ ������� ����� �� ������� ������, � � ��������� ����� ������������ �����������
};

class Graph
{
public:
	std::vector<Vertex *> vertices;
	std::vector<Edge *> edges;
	int n;//���������� ������
	int m; //���������� �����

	Graph(int n_, int m_)
	{
		//��������� ������))
		//��� ������� �����! �� �� �� ����� �������������� ���������� �����, 
		//� ��� ��� ����� ������������, ����� ��������� ������ ������������ � ������
		//���������, ��� ��������
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
				i = (rand() % (n - 1)); //��������� ����� �� 0 �� n-2
				j = (rand() % (n - i - 1)) + i + 1;//�������� ��������� ����� �� i+1 �� n-1 - ������ ����� �����
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
		//��� � ���� ���������� ����(( ���� �� ����������...�� � ����� ��� ��� ���
	}
	//��������� ������� ��������� ������ ������ ��������� �������
	//�� ��������� ������� dfs �� �������� ������� ������� ���������� ������ ��������� 
};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	//������ ��� ���� ������������ ������, ��� ���� �� ������������ ������������ ������ � ��������
	//������ ����� ��������� ��� ��� �� � �������� ������ ��� �� ����� ������� ������� ��� �����
	//��� ����� ������ �������� ��������� � �������� ������ � �����
	//��� ��� � ����� ��� ����� ��))

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