#include "BFS_Function.h"


int Map[length][breadth] = {
	{start,block,barrier,block},
	{block,block,block,block},
	{block,block,barrier,block},
	{ block, barrier, end, barrier },
	{ block, block, barrier, barrier }
};

int main()
{
	BfsNode b;
	b.x = 0;
	b.y = 0;
	BFS(Map,b);
	int a;
	std::cin >> a;
	return 0;
}