#include<iostream>
using namespace std;
int linearsearch(int *a, int n, int K)
{
	int position=-1;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == K)
		{
			position = i;
		}
	}
	return position;
}
int main()
{
	int n,K;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cin >> K;
	cout << linearsearch(a, n, K)<< endl;
	delete[] a;
	return 0;
}