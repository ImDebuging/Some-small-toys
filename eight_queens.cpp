#include<iostream>
using namespace std;

int place[8] = { 0, 0,0,0,0,0,0 };		//第i行皇后放在第place[i]列
bool flag[8] = { true, true, true, true, true, true, true, true };	//第flag[i]列是否可用
bool d1[15] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };		//上对角线是否可用
bool d2[15] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };		//下对角线是否可用
int ans = 0;

void generate(int n)
{
	int col;
	for (col = 0; col < 8; ++col)
	{
		if (flag[col] && d1[n - col + 7] && d2[n + col]){
			place[n] = col;
			flag[col] = false;
			d1[n - col + 7] = false;
			d2[n + col] = false;			//将第n个皇后放置在flag[col]位置
			if (n < 7){
				generate(n + 1);
			}
			else{
				ans++;
			}
			flag[col] = true;
			d1[n - col + 7] = true;
			d2[n + col] = true;
		}

	}
}


int main()
{
	generate(0);
	cout << ans;
	return 0;
}
