#include<iostream>
using namespace std;
bool checkSumOftwoNumber(int* a, int n,int target)
{
	int first = 0;
	int last = n - 1;
	while (first < last)
	{
		if ((a[first] + a[last]) == target)
		{
			return true;
		}
		else if ((a[first] + a[last]) < target)
		{
			first++;
		}
		else
		{
			last--;
		}
	}
	return false;
}//Hàm kiểm tra tổng giá trị 2 phần tử bất kì trong mảng dùng 2 biến ở đầu và cuối mảng
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
	if (checkSumOftwoNumber(nums, n, target))
	{
		cout <<"YES";
	}
	else
	{
		cout <<"NO";
	}
	delete[] nums;
	return 0;
}