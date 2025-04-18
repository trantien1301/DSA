#include<iostream>
using namespace std;
int linearsearchwithsentinel(int* a, int n, int K)
{
	int last = a[n - 1];
	a[n - 1] = K;
	int i = 0;
	while (a[i] != K)
	{
		i++;
	}
	a[n - 1] = last;
	if (i < n-1 || a[n - 1] == K)
	{
		return i;
	}
	return -1;
}
int main()
{
	int n, K;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cin >> K;
	cout << linearsearchwithsentinel(a, n, K) << endl;
	delete[] a;
	return 0;
}