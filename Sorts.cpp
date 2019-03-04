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

int main()
{
	std::vector<int64_t> matr = { int64_t(45321), int64_t(13440), int64_t(68632) };
	radixSort(matr);
	std::cin.get();
	std::cin.get();
}
