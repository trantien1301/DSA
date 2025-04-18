#include<iostream>
using namespace std;
void sortArray(int* a, int n)
{
	for (int i = 1; i < n; i++)
	{
		int key = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > key)
		{
			 a[j + 1] = a[j];
			 j = j- 1;
		}
		a[j + 1] = key;
	}
}//Hàm sắp xếp lại mảng theo chiều tăng dần
void SumofThreeEqualZero(int* a, int n)
{
	sortArray(a, n);
	for (int i = 0; i < n-2; i++)//Cho chạy phần tử đầu tiên của mảng con
	{
		if (i > 0 && a[i] == a[i - 1])//Tránh lặp lại phần tử đầu
		{
			continue;
		}
		int left = i + 1;//Phần tử 2 của mảng con
		int right = n - 1;//Phần tử 3 của mảng con
		
		while (left < right) 
		{
			int sum = a[i] + a[left] + a[right];
			if (sum == 0)
			{
				cout << "[" << a[i] << "," << a[left] << "," << a[right] << "]" << ", " ;
				while (left < right && a[left] == a[left + 1]) left++;//Tránh lặp phần tử 2
				while (left < right && a[right] == a[right - 1]) right--;//Tránh lặp phần tử 3
				left++;
				right--;
			}
			else if (sum < 0)//Tổng bé hơn 0 thì tăng phần tử 2,lớn hơn 0 thì giảm phần tử 3
			{
				left++;
			}
			else
			{
				right--;
			}
		}
	}
}int main()
{
	int n;
	cin >> n;
	int* nums = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> nums[i];
	}
	SumofThreeEqualZero(nums, n);
	delete[] nums;
	return 0;
}