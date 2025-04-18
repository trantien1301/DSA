#include<iostream>
using namespace std;
bool isSorted(int arr[], int n)
{
	if (n == 0 || n == 1) 
	{
		return true;
    }
	if (arr[0] > arr[1])
	{
		return false;
	}
	return isSorted(arr + 1, n - 1);
}
int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	if (isSorted(a, n))
		cout << "The array is sorted.\n";
	else
		cout << "The array is NOT sorted.\n";
	delete[] a;
	return 0;

}