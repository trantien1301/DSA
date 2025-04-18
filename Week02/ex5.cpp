#include<iostream>
using namespace std;
bool checkSubArraybyLenght(int* a, int n, int target, int lenght)
{
	int currentsum = 0;
	for (int i = 0; i < lenght; i++)
	{
		currentsum += a[i];
	}
	if (currentsum >= target)
	{
		return true;
	}
	for (int i = lenght; i < n; i++)
	{
		currentsum += a[i] - a[i - lenght];
		if(currentsum>=target)
			{
				return true;
			}
	}
	return false;
}//Hàm kiểm tra xem mảng nhỏ với độ lớn lenght có tổng lớn hơn hoặc bằng target không
int minimalLenght(int* a, int n, int target)
{
	int maxsum=0;
	for (int i = 0; i < n; i++)
	{
		maxsum += a[i];
	}
	if (maxsum < target)
	{
		return 0;
	}//Trả về 0 nếu không có mảng con thoả
	int left = 1;//Kích thước mảng con nhỏ nhất có khả năng thoả điều kiện là 1
	int right = n; // Kích thước mảng con lớn nhất có khả năng thoả điều kiện là n
	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (checkSubArraybyLenght(a, n, target, mid))
		{
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}
	return left;
}//Hàm trả về kích thước mảng con nhỏ nhất thoả điều kiện
int main()
{
	int n, target;
	cin >> n;
	int* nums = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> nums[i];
	}
	cin >> target;
	cout << minimalLenght(nums, n, target) << endl;
	delete[] nums;
	return 0;
}