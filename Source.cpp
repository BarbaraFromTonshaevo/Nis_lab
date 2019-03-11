#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <algorithm>








enum Colors{White, Gray, Black};
class Vertex
{
private:
	int num;
	int value = White;//можно задавать цвета(состояния)
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
	void set_adjacent(Vertex * ver)//прописать функцию, которая возвращает вектор смежных вершин
	{
		adjacent_vertices.push_back(ver);
		//будет постоянно увеличиваться при добавлении ребра
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

	std::pair<Vertex *, Vertex *> position;//можно через указатели
	std::pair<int, int> pos;//либо прописывать номер вершины
	//int64_t value64;
	int value;
	bool tree = 0;
	int num; //какой по счету в векторе
	int64_t posibility = 0;

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
	bool get_tree() { return tree; };
	int64_t get_posibility() { return posibility; };
	//int64_t get_value64() { return value64; };


	void set_pos(int pos1, int pos2) { pos.first = pos1; pos.second = pos2; };
	//void set_position(Vertex * pos1, Vertex * pos2) { position.first = pos1; position.second = pos2; };
	void set_value(int value_) { value = value_; };
	void set_tree(bool tree_) { tree = tree_; };
	void set_posibility()
	{
		posibility = posibility << 1;
		posibility = posibility + value;
	};
	void set_posibility(int64_t value_) { posibility = value_; };


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

	//подумала мб прописать синхронизатор между номером вершин и их указателями...тип как только заносим что-то одно из них
	//автоматически ищется записывается в другое
	//я подумала что будет удобно вбивать ребра по номерам вершин, а в программе лучше пользоваться указателями
};


void countingSort(std::vector<int> &A)
{
	int n = A.size();
	int C = *(std::max_element(A.begin(), A.end())) + 1;
	std::vector<int> R(A.size());
	std::vector<int> B(C);

	for (int i = 0; i < n; i++)
		++B[A[i]];

	for (int i = 1; i < C; i++)
		B[i] += B[i - 1];

	for (int i = n - 1; i >= 0; --i)
		R[--B[A[i]]] = A[i];
	A = R;
}


void radixSortEdges(std::vector<Edge *> &A)
{
	int n = A.size();
	int C = 2;
	std::vector<int64_t> R(n);
	std::vector<std::pair<int64_t, Edge*>>FR(n);
	std::vector<int64_t> B(C);
	for (int s = 0; s < 64; s++)
	{

		for (int i = 0; i < n; i++)
		{
			R[i] = (A[i]->get_posibility() >> s) % 2;
			FR[i].first = 0;
		}

		for (int i = 0; i < C; i++)
		{
			B[i] = 0;
		}

		for (int i = 0; i < n; i++)
			++B[R[i]];

		for (int i = 1; i < C; i++)
			B[i] += B[i - 1];

		for (int i = n - 1; i >= 0; --i)
		{
			FR[B[R[i]] - 1].first = A[i]->get_posibility();
			FR[--B[R[i]]].second = A[i];
		}

		for (int i = 0; i < n; i++)
		{
			A[i] = FR[i].second;
			A[i]->set_posibility(FR[i].first);
		}


	}
}


class Graph
{
public:
	std::vector<Vertex *> vertices;
	std::vector<Edge *> edges;
	int size;
	int n;
	int m;
	std::vector<Vertex *> dfs_vertices;
	std::vector<Edge *> dfs_edges;
	std::vector<Edge *> bridge;
	std::vector<Edge *> sort_edges;
	std::vector<std::pair<Edge *, Edge *>> bridge_2;	

	Graph(int n_, int m_)
	{
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
			while (f == 1)
			{
				f = 0;
				i = (rand() % (n - 1)); 
				j = (rand() % (n - i - 1)) + i + 1;
				for (int l = 0; l < edges.size(); l++)
				{
					if ((edges[l]->get_pos().first == i) && (edges[l]->get_pos().second == j))
					{
						f = 1;
						break;
					}
				}
			}

			edges.push_back(new Edge(vertices[i], vertices[j],edges.size()));

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
		//тут у меня отключился мозг(( пока не сообразила...но я думаю все тип топ
		v->set_value(Gray);
		for (int i = 0; i < v->get_adjacent_vertices().size(); ++i)
		{
			if (v->get_adjacent_vertices()[i]->get_value() == 0)//не посещали
			{
				//здесь кладем ребро
				dfs_edges.push_back(edges[v->get_adjacent_edges()[i]]);
				dfs_ptr(v->get_adjacent_vertices()[i]);
			}
			
		}
		v->set_value(Black);//красим в черный
		dfs_vertices.push_back(v);
	};
	void dfs_int(int v)
	{
		vertices[v]->set_value(Gray);

		for (int i = 0; i < vertices[v]->get_adjacent_vertices().size(); ++i)
		{
			if (vertices[v]->get_adjacent_vertices()[i]->get_value() == 0)//не посещали
			{
				dfs_int(vertices[v]->get_adjacent_vertices()[i]->get_num());
				dfs_edges.push_back(edges[vertices[v]->get_adjacent_edges()[i]]);
				edges[vertices[v]->get_adjacent_edges()[i]]->set_tree(1);//ребро остовное
			}

		}
		vertices[v]->set_value(Black);//красим в черный
		dfs_vertices.push_back(vertices[v]);
	};

	void clean()
	{
		for (int i = 0; i < vertices.size(); ++i)
			vertices[i]->set_value(White);
		for (int i = 0; i < edges.size(); ++i)
			edges[i]->set_value(0);
	}

	void dfs_clean()
	{
		dfs_vertices.clear();
		dfs_edges.clear();
	}

	void set_link(int start, int size)
	{
		std::pair<Edge *, Edge*> e;
		for (int i = start; i < start+size; i++)
		{
			for (int j = i + 1; j < start+size; j++)
			{
				e.first = sort_edges[i];
				e.second = sort_edges[j];
				bridge_2.push_back(e);

			}
		}
	}

	void repead_method()
	{
		for (int it = 0; it < 63; ++it)
		{
			one_bridge();
			for (int i = 0; i < edges.size(); ++i)
			{
				edges[i]->set_posibility();
			}
		}
		for (int i = 0; i < edges.size(); ++i)
		{
			if (!edges[i]->get_posibility())
			{
				bridge.push_back(edges[i]);
			}
		}
		
		sort_edges = edges;
		radixSortEdges(sort_edges);
		int count = 0;
	
		for (int i = 0; i < sort_edges.size() - 1; ++i)
		{
			if (sort_edges[i]->get_posibility() == sort_edges[i + 1]->get_posibility())
			{
				count++;
				if (i == sort_edges.size() - 2)
				{
					set_link(i - count+1, count + 1);
				}
			}
			else if (count > 0) 
			{
				set_link(i-count, count+1);
				count = 0;
			}
			
		}

		std::cout << "2-BRIGES : " << std::endl;
	
		for (int i = 0; i < bridge_2.size(); ++i)
		{
			std::cout << bridge_2[i].first->get_pos().first << "---" << bridge_2[i].first->get_pos().second << " <---> " << bridge_2[i].second->get_pos().first << "---" << bridge_2[i].second->get_pos().second << std::endl;
		}
		
	

	};

	void one_bridge()
	{
		int sum;

		clean();
		dfs_clean();
		dfs_int(0);

		for (int i = 0; i < edges.size(); ++i)
		{
			if (!edges[i]->get_tree())
			{
				edges[i]->set_value(rand() % 2);
			}
		}
		for (int i = 0; i < dfs_vertices.size() - 1; i++)
		{
			sum = 0;
			for (int j = 0; j < dfs_vertices[i]->get_adjacent_edges().size(); ++j)
			{
				if (edges[dfs_vertices[i]->get_adjacent_edges()[j]] != dfs_edges[i])
				{
					sum = sum ^ edges[dfs_vertices[i]->get_adjacent_edges()[j]]->get_value();//считаем сумму по модулю всех ребер, кроме той которой присваиваем значение
				}
			}
			dfs_edges[i]->set_value(sum);
		}
	}

};


int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(0));

	
	

	int V_size = 7, E_size = 8;
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


	g.repead_method();
	std::cout << "1-BRIGES: " << std::endl;
	for (int i = 0; i < g.bridge.size(); i++)
	{
		std::cout << g.bridge[i]->get_pos().first << "---" << g.bridge[i]->get_pos().second << std::endl;
	}
	
	std::cin.get();
	std::cin.get();


	return 0;
}