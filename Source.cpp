#include <iostream>
#include <list>
#include <vector>

enum Colors{White, Gray, Black};
class Vertex
{
private:
	int num;
	int value = White;//����� �������� �����(���������)
	std::vector<Vertex *> adjacent_vertices;
	std::vector<int> adjacent_edges;

	int power;
public:
	Vertex() {};
	Vertex(int num_) { num = num_; };
	Vertex(int num_, int value_) { num = num_; value = value_; };

	int get_num() { return num; };
	int get_value() { return value; };
	std::vector<Vertex *> get_adjacent_vertices() { return adjacent_vertices; };
	std::vector<int> get_adjacent_edges() { return adjacent_edges; };



	void set_value(int value_) { value = value_; };
	void set_adjacent(Vertex * ver)//��������� �������, ������� ���������� ������ ������� ������
	{
		adjacent_vertices.push_back(ver);
		//����� ��������� ������������� ��� ���������� �����
	};
	void set_adj_edges(int e)
	{
		adjacent_edges.push_back(e);
	}


	void print_adjacent()
	{
		for (int i = 0; i < adjacent_vertices.size(); ++i)
		{
			std::cout << adjacent_vertices[i]->get_num() << " ";
		}
		std::cout << std::endl;
	}

	void print_adjacent_edges()
	{
		for (int i = 0; i < adjacent_edges.size(); ++i)
		{
			std::cout << adjacent_edges[i] << " ";
		}
		std::cout << std::endl;
	}

};


class Edge
{
private:

	std::pair<Vertex *, Vertex *> position;//����� ����� ���������
	std::pair<int, int> pos;//���� ����������� ����� �������
	int value;
	int num; //����� �� ����� � �������

public:

	Edge(int num1, int num2, int num_) { pos.first = num1; pos.second = num2; num = num_; };
	Edge(Vertex * num1, Vertex * num2, int num_)
	{
		num = num_;
		position.first = num1;
		position.second = num2;
		position.first->set_adjacent(position.second);
		position.second->set_adjacent(position.first);
		pos.first = position.first->get_num();
		pos.second = position.second->get_num();
		position.first->set_adj_edges(num);
		position.second->set_adj_edges(num);


	};
	Edge(int num1, int num2, std::vector<Vertex *> vertices, int num_)
	{
		num = num_;
		pos.first = num1;
		pos.second = num2;
		synchronization(vertices);
	};

	std::pair<Vertex *, Vertex *> get_position() { return position; };
	std::pair<int, int> get_pos() { return pos; };
	int get_value() { return value; };

	void set_pos(int pos1, int pos2) { pos.first = pos1; pos.second = pos2; };
	//void set_position(Vertex * pos1, Vertex * pos2) { position.first = pos1; position.second = pos2; };
	void set_value(int value_) { value = value_; };

	void synchronization(std::vector<Vertex *> vertices)
	{
		Vertex *a = nullptr, *b = nullptr;
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
		position.first = a;
		position.second = b;
		position.first->set_adj_edges(num);
		position.second->set_adj_edges(num);

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
	int size;
	std::vector<Vertex *> dfs_vertices;
	std::vector<Edge *> dfs_edges;

	Graph(int size_)
	{
		//��������� ������))
		size = size_;
		for (int i = 0; i < size; i++)
		{
			vertices.push_back(new Vertex(i));
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				if (rand() % 2 == 1)
				{
					edges.push_back(new Edge(vertices[i], vertices[j],edges.size()+1));
				}
			}
		}
	};
	Graph(std::vector<Vertex *> vertices_, std::vector<Edge *> edges_)
	{
		vertices = vertices_;
		edges = edges_;
	};

	void print()
	{
		for (int i = 0; i < vertices.size(); ++i)
		{
			std::cout << vertices[i]->get_num() << std::endl;
			vertices[i]->print_adjacent();
			vertices[i]->print_adjacent_edges();

		}
		for (int i = 0; i < edges.size(); ++i)
		{
			std::cout << edges[i]->get_pos().first << "---" << edges[i]->get_pos().second << std::endl;
		}
	}
	void print_dfs()
	{
		for (int i = 0; i < dfs_vertices.size(); ++i)
		{
			std::cout << dfs_vertices[i]->get_num() << std::endl;
		}
		for (int i = 0; i < dfs_edges.size(); ++i)
		{
			std::cout << dfs_edges[i]->get_pos().first<<"---"<< dfs_edges[i]->get_pos().second << std::endl;
		}
	};
	void dfs_ptr(Vertex* v)
	{
		//��� � ���� ���������� ����(( ���� �� ����������...�� � ����� ��� ��� ���
		v->set_value(Gray);
		for (int i = 0; i < v->get_adjacent_vertices().size(); ++i)
		{
			if (v->get_adjacent_vertices()[i]->get_value() == 0)//�� ��������
			{
				//����� ������ �����
				dfs_edges.push_back(edges[v->get_adjacent_edges()[i]]);
				dfs_ptr(v->get_adjacent_vertices()[i]);
			}
			
		}
		v->set_value(Black);//������ � ������
		dfs_vertices.push_back(v);
	};
	void dfs_int(int v)
	{
		vertices[v]->set_value(Gray);

		for (int i = 0; i < vertices[v]->get_adjacent_vertices().size(); ++i)
		{
			if (vertices[v]->get_adjacent_vertices()[i]->get_value() == 0)//�� ��������
			{
				dfs_edges.push_back(edges[vertices[v]->get_adjacent_edges()[i]]);
				dfs_int(vertices[v]->get_adjacent_vertices()[i]->get_num());
			}

		}
		vertices[v]->set_value(Black);//������ � ������
		dfs_vertices.push_back(vertices[v]);
	};

	//��������� ������� ��������� ������ ������ ��������� �������
	//�� ��������� ������� dfs �� �������� ������� ������� ���������� ������ ��������� 
};


int main()
{
	setlocale(LC_ALL, "Russian");
	//������ ��� ���� ������������ ������, ��� ���� �� ������������ ������������ ������ � ��������
	//������ ����� ��������� ��� ��� �� � �������� ������ ��� �� ����� ������� ������� ��� �����
	//��� ����� ������ �������� ��������� � �������� ������ � �����
	//��� ��� � ����� ��� ����� ��))

	//Graph g(10);
	//g.print();

	
	int V_size = 6, E_size = 7;
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
		edges.push_back(new Edge(num1, num2,vertices,edges.size()));

	}
	Graph g(vertices, edges);
	//g.print();
	std::cout << "DFS: " << std::endl;
	g.dfs_int(0);
	g.print_dfs();

	std::cin.get();
	std::cin.get();


	return 0;
}