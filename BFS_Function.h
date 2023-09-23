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
};//������һ���ṹ�壬������Žڵ��λ�ú͵�ǰ�Ĳ���


bool ifCanMove(int Map[length][breadth], BfsNode curNode, int mov, BfsNode BfsMap[length][breadth])	//�ж��Ƿ����ߵ���һ��
{
	//mov ������ȡֵ0��1��2��3,�ֱ�������ϡ��¡�������
	//curNode ����ǰ�ڵ�
	//Map��Ҫ�ߵĵ�ͼ
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
	std::queue<BfsNode> que;	//BFS����
	BfsMap[begin.x][begin.y].notfound = false;
	que.push(BfsMap[begin.x][begin.y]);
	while (que.empty()!=true)	//�����в�Ϊ��
	{
		if (Map[que.front().x][que.front().y] == end){
			std::cout << "�ҵ����յ㣬����Ϊ(" << que.front().x + 1 << "," << que.front().y + 1 << ")!" << std::endl;
		}
		BfsNode temp = que.front();
		que.pop();
		for (int i = 0; i < 4; ++i)		//�����ĸ����򣬽���һ�������ߵ���λ����ӵ�������
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
	std::cout << "û��ͨ���յ��·��";
}