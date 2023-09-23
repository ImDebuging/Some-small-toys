#include<iostream>
#include<queue>

#define length	5
#define breadth 4
#define block	0
#define start	1
#define end		2
#define barrier 3


struct BfsNode
{
	int x;
	int y;
	/*int step;
	int element;*/
	bool notfound;
};//定义了一个结构体，用来存放节点的位置和当前的步数


bool ifCanMove(int Map[length][breadth], BfsNode curNode, int mov, BfsNode BfsMap[length][breadth])	//判断是否能走到下一步
{
	//mov 有四种取值0，1，2，3,分别代表往上、下、左、右走
	//curNode 代表当前节点
	//Map是要走的地图
	switch (mov)
	{
	case 0:
		if (curNode.x <= 0){
			return false;
		}
		else if (Map[curNode.x - 1][curNode.y] == barrier || BfsMap[curNode.x - 1][curNode.y].notfound==false){
			return false;
		}
		break;
	case 1:
		if (curNode.x >= (length - 1)){
			return false;
		}
		else if (Map[curNode.x + 1][curNode.y] == barrier || BfsMap[curNode.x + 1][curNode.y].notfound == false){
			return false;
		}
		break;
	case 2:
		if (curNode.y <= 0){
			return false;
		}
		else if (Map[curNode.x][curNode.y - 1] == barrier || BfsMap[curNode.x][curNode.y - 1].notfound == false){
			return false;
		}
		break;
	case 3:
		if (curNode.y >= (breadth - 1)){
			return false;
		}
		else if (Map[curNode.x][curNode.y + 1] == barrier || BfsMap[curNode.x][curNode.y + 1].notfound == false){
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}


void BFS(int Map[length][breadth],BfsNode begin)
{
	BfsNode BfsMap[length][breadth];
	for (int i = 0; i < length;++i)
	{
		for (int j = 0; j < breadth; ++j)
		{
			BfsMap[i][j].x = i;
			BfsMap[i][j].y = j;
			BfsMap[i][j].notfound = true;
		}
	}
	std::queue<BfsNode> que;	//BFS队列
	BfsMap[begin.x][begin.y].notfound = false;
	que.push(BfsMap[begin.x][begin.y]);
	while (que.empty()!=true)	//当队列不为空
	{
		if (Map[que.front().x][que.front().y] == end){
			std::cout << "找到了终点，坐标为(" << que.front().x + 1 << "," << que.front().y + 1 << ")!" << std::endl;
		}
		BfsNode temp = que.front();
		que.pop();
		for (int i = 0; i < 4; ++i)		//遍历四个方向，将下一步可能走到的位置添加到队列里
		{
			if (ifCanMove(Map, temp, i,BfsMap) == true){
				switch (i)
				{
				case 0:
					que.push(BfsMap[temp.x-1][temp.y]);
					BfsMap[temp.x - 1][temp.y].notfound = false;
					break;
				case 1:
					que.push(BfsMap[temp.x + 1][temp.y]);
					BfsMap[temp.x + 1][temp.y].notfound = false;
					break;
				case 2:
					que.push(BfsMap[temp.x ][temp.y-1]);
					BfsMap[temp.x][temp.y - 1].notfound = false;
					break;
				case 3:
					que.push(BfsMap[temp.x][temp.y + 1]);
					BfsMap[temp.x][temp.y + 1].notfound = false;
					break;
				default:
					break;
				}
			}
		}
	}
	std::cout << "没有通往终点的路径";
}