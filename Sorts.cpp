#include<iostream>
#include<vector>
#include <algorithm>

void countingSort(std::vector<int> &A)
{
	int n = A.size();
	int C = *(std::max_element(A.begin(), A.end())) +1;
	std::vector<int> R(A.size());
	std::vector<int> B(C);//создание вектора из int64 размера C

	for (int i = 0; i < n; i++)
		++B[A[i]];

	for (int i = 1; i < C; i++)
		B[i] += B[i - 1];

	for (int i = n - 1; i >= 0; --i)
		R[--B[A[i]]] = A[i];
	A = R;
}


void radixSort(std::vector<int64_t> &A) //принимает массив А инт64 и сортирует его линейно 
{
	int n = A.size();
	int C = 2;
	std::vector<int64_t> R(n), FR(n);
	std::vector<int64_t> B(C); //создание вектора из int64 размера C
	for (int s = 0; s < 64; s++)
	{
		int shift = pow(2, s);
		for (int i = 0; i < n; i++)
		{
			R[i] = (A[i] >> s) % 2;
			FR[i] = 0;
		}

		for (int i = 0; i < C; i++)
		{
			B[i] = 0;
		}
		
		for (int i = 0; i < n; i++)
			++B[ R[i] ];

		for (int i = 1; i < C; i++)
			B[i] += B[i - 1];

		for (int i = n - 1; i >= 0; --i)
			FR[--B[ R[i]] ] = A[i];

		A = FR;
		
	}
	for (int i = 0; i < A.size(); i++)
	std::cout << A[i] << ' ';
}

void radixSortEdges(std::vector<Edge *> &A) //принимает массив А ребер и сортирует его линейно 
{
	int n = A.size();
	int C = 2;
	std::vector<int64_t> R(n);
	std::vector<std::pair<int64_t, Edge*>>FR(n);
	std::vector<int64_t> B(C); //создание вектора из int64 размера C
	for (int s = 0; s < 64; s++)
	{
		for (int i = 0; i < n; i++)
		{
			R[i] = (A[i]->get_value64() >> s) % 2;
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
			FR[B[R[i]] - 1].first = A[i]->get_value64();
			FR[--B[R[i]]].second = A[i];
		}

		for (int i = 0; i < n; i++)
		{
			A[i] = FR[i].second;
			A[i]->set_value64(FR[i].first);
		}

	}
}

int main()
{
	Graph g(5, 5);
	g.print();
	std::cout << "64 VALUE: " << std::endl;
	for (int i = 0; i < g.edges.size(); i++)
	{
		int64_t val = rand() % int(pow(2, 64) - 1);
		g.edges[i]->set_value64(val);
		std::cout << g.edges[i]->get_pos().first << "-"<< g.edges[i]->get_pos().second<<" "<< g.edges[i]->get_value64() << std::endl;
	}
	radixSortEdges(g.edges);
	std::cout << "RADIX SORT: " << std::endl;
	for (int i = 0; i < g.edges.size(); i++)
	{
		std::cout << g.edges[i]->get_pos().first << "-" << g.edges[i]->get_pos().second << " " << g.edges[i]->get_value64() << std::endl;
	}
}
