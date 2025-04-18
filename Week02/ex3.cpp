#include<iostream>
using namespace std;
int findmin(int* a, int n)
{
	int left = 0;
	int right = n - 1;
	while (left < right)
	{
		int mid =left+ (right - left) / 2;
		
		if (a[mid] > a[right])//Nếu vị trí ở giữa lớn hơn vị trí biên phải thì giá trị min phải ở bên phải nên cắt nữa bên trái và ngược lại
		{
			left = mid + 1;
		}
		else
		{
			right = mid ;
		}
	}
	return a[left];
}//Hàm tìm min dùng binary search
int main()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	cout << findmin(a,n) << endl;
	delete[] a;
	return 0;
}