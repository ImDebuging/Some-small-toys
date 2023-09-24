/*
基于多线程的BFS迷宫实现
此代码由懒猫老师的学生小林同学版权所有，如需转发，请注明出处

*/

#include <thread>//多线程头文件
#include<Windows.h>//用于窗口等待Sleep
#include <iostream>
using namespace std;
#define WAIT_TIME 1000//加载时间，越小越快
string* maze = NULL;//输入的迷宫
int maze_height = 0;//迷宫高度
int flag = 0;//结束标志
int aim_x = 0, aim_y = 0;//终点坐标
int** maze_road;//迷宫数组
int road_num = 0, road_num_flag = -1;//创建寻路线程次数，寻路线程次数标记
void printMap();
void findRoad(int x, int y, int direction);
void continuePrintMap();
int main()
{
	/*输入数据*/
	cout << "迷宫高为：";
	cin >> maze_height;
	cout << "请输入迷宫（墙壁为#）：" << endl;
	maze = new string[maze_height];
	for (int i = 0; i < maze_height; i++)
	{
		cin >> maze[i];
	}
	cout << "请输入迷宫终点(x,y)：" << endl;
	cin >> aim_x >> aim_y;
	/*构造迷宫数组*/
	maze_road = new int* [maze_height];
	if (maze_road)
		memset(maze_road, 0, sizeof(int*) * maze_height);
	for (int i = 0; i < maze_height; i++)
	{
		maze_road[i] = new int[maze[i].size() + 1];
		for (unsigned int j = 0; j < maze[i].size() + 1; j++)
		{
			if (maze[i][j] != '#')
				maze_road[i][j] = 0;
			else
				maze_road[i][j] = -1;
		}
	}
	/*打开多线程*/
	system("cls");//清屏
	thread print_map(continuePrintMap);
	print_map.detach();
	thread find_road(findRoad, 1, 1, 0);
	find_road.detach();
	/*后续*/
	while (1)
	{
		/*没找到路径不继续*/
		if (flag == 1)
			break;
	}
	system("cls");
	printMap();//最终迷宫图
	/*收尾删除*/
	for (int i = 0; i < maze_height; i++)
	{
		delete[] maze_road[i];
	}
	if (maze_road)
		delete[] maze_road;
	maze_road = NULL;
	delete[] maze;
	maze = NULL;
	return 0;
}
/*多线程持续打印迷宫*/
void continuePrintMap()
{
	while (1)
	{
		/*不再找了也停止（机器人全灭）*/
		if (road_num_flag == road_num)
		{
			flag = 1;
			return;
		}
		/*找到位置就停止*/
		if (flag == 1)
			return;
		printMap();
	}

}
/*打印迷宫*/
void printMap()
{
	/*光标移动到（0，0），不用cls因为会闪*/
	road_num_flag = road_num;
	printf_s("\33[0;0H");
	for (int i = 0; i < maze_height; i++)
	{
		for (unsigned int j = 0; j < maze[i].size(); j++)
		{
			if (maze_road[i][j] == -1)
				printf_s("%3c", maze[i][j]);//打印墙
			else
				printf_s("%3d", maze_road[i][j]);//打印路
			/*else if(maze_road[i][j] == -2)
				printf_s("  X");*/
		}
		cout << endl;
	}
	Sleep(WAIT_TIME);
}
/*
多线程迷宫寻路机器人
x 当前x坐标
y 当前y坐标
direction:
0 没有前一个位置
1 前一个位置在↑
2 前一个位置在↓
3 前一个位置在←
4 前一个位置在→
*/
void findRoad(int x, int y, int direction)
{
	Sleep(WAIT_TIME);
	road_num++;
	/**/
	if (flag == 1)//寻路完成提前退出
		return;
	switch (direction)      //记录当前走到第几步
	{
	case 1: {
		maze_road[x][y] = maze_road[x - 1][y] + 1;
		break;
	}
	case 2: {
		maze_road[x][y] = maze_road[x + 1][y] + 1;
		break;
	}
	case 3: {
		maze_road[x][y] = maze_road[x][y - 1] + 1;
		break;
	}
	case 4: {
		maze_road[x][y] = maze_road[x][y + 1] + 1;
		break;
	}
	default:
		break;
	}
	/*寻路成功，标记并退出*/
	if (x == aim_x && y == aim_y)
	{
		flag = 1;
		return;
	}
	/*向四个方向，有路则释放新的机器人（创建新线程）*/
	if (maze_road[x - 1][y] == 0)
	{
		thread find_road_up(findRoad, x - 1, y, 2);
		find_road_up.detach();
	}
	if (maze_road[x + 1][y] == 0)
	{
		thread find_road_down(findRoad, x + 1, y, 1);
		find_road_down.detach();
	}
	if (maze_road[x][y - 1] == 0)
	{
		thread find_road_left(findRoad, x, y - 1, 4);
		find_road_left.detach();
	}
	if (maze_road[x][y + 1] == 0)
	{
		thread find_road_right(findRoad, x, y + 1, 3);
		find_road_right.detach();
	}
	/*分裂成新的机器人后，本机器人销毁*/
	Sleep(WAIT_TIME * 2);
	maze_road[x][y] = -2;
	return;
}

测试数据1：
##########
#00#000#0#
#00#000#0#
#0000##00#
#0###0000#
#000#0000#
#0#000#00#
#0###0##0#
##0000000#
##########

测试数据2：
####################
#0####0#0000########
#0###0000##0000000##
#0####0######0##0###
#000000######00#00##
#########00000######
##00000000###000####
##0##0##############
##0##0####0##0######
##0##000000000000###
#00#########0#######
##00000#####000#####
######0#############
######0#############
##0000000000000#####
##0####0#####0######
##0000#0#####0######
#######0############
#######000000000000#
####################