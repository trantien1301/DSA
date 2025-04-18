#include <iostream>
using namespace std;
int sumweight(int* weight, int n)
{
	int res =0;
	for (int i = 0; i < n; i++)
	{
		res += weight[i];
	}
	return res;
}//Hàm tính tổng khối lượng cần chở
bool enoughCapacity(int* weight, int n,int days,int capacity)
{
	int currentweight = 0;
	int requiredday = 1;
	for (int i = 0; i < n; i++)
	{
		if (currentweight + weight[i] > capacity)
		{
			requiredday++;
			currentweight = 0;
		}
		currentweight += weight[i];
		if(requiredday>days)
		{
			return false;
		}
	}
	return true;
}//Hàm kiểm tra khả năng chở của tàu có đủ để vận chuyển trong days ngày không
int leastweightcapacity(int* weight, int n, int days)
{
	int left = weight[n - 1];//Tối thiểu là khối lượng lớn nhất trong mảng
	int right = sumweight(weight, n);//Tối đa là tổng các khối lượng
	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (enoughCapacity(weight, n, days, mid))
		{
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}
	return left;
}//Hàm trả về khối lượng tối thiểu cần để chở trong days ngày
int main()
{
	int n, days;
	cin >> n;
	int* weights = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> weights[i];
	}
	cin >> days;
	cout << leastweightcapacity(weights, n, days) << endl;
	delete[] weights;
	return 0;
}