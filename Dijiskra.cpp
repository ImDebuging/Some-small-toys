#include<iostream>
using namespace std;
int a = INT_MAX;
int map[6][6] = { { 0, 50, INT_MAX, 40, 25, 10 },
{ 50, 0, 15, 20, INT_MAX, 25 },
{ INT_MAX, 15, 0, 10, 20, INT_MAX },
{ 40, 20, 10, 0, 10, 25 },
{ 25, INT_MAX, 20, 10, 0, 55 },
{ 10, 25, INT_MAX, 25, 55, 0 } };


int findMinIndex(int start,bool used[6])
{
	int ret=0;
	while (used[ret] && ret < 6)
	{
		ret++;
	}
	for (int i = ret; i < 6; ++i)
	{
		if (!used[i] && map[start][i] < map[start][ret]){
			ret = i;
		}
	}
	return ret;
}

void Dijiskra(int start)
{
	bool used[6] = { false, false, false, false, false, false};
	used[start] = true;
	int min_index;
	int s_num = 1;
	while (s_num<6)
	{
		min_index = findMinIndex(start, used);
		used[min_index] = true;
		for (int i = 0; i < 6; ++i)
		{
			if (!used[i] && map[start][i]>map[start][min_index] + map[min_index][i] && map[min_index][i]!=INT_MAX){
				map[start][i]=map[start][min_index] + map[min_index][i];
			}
		}
		s_num++;
	}
}

int main()
{
	Dijiskra(0);
	int c;
	cin >> c;
	return 0;
}
