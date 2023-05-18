#include<iostream>
#include<vector>
#include<algorithm>
#define MaxEdge (MaxVertex*MaxVertex)
using namespace std;
const int MaxVertex = 10;

struct Edge{
	int from, to;
	int weight;
};

bool cmp(Edge e1, Edge e2)
{
	return e1.weight < e2.weight;
}

class EdgeGraph			
{
public:
	int parent[MaxVertex];
	Edge edge[MaxEdge];
	int vertexNum, edgeNum;
};//定义边集数组


int findRoot(int parent[],int v)
{
	while (parent[v] != -1)//parent[i]如果为-1，则代表i已经是这棵子树的根节点了
	{
		v = parent[v];	   //如果不是根节点，则一直找当前节点的parent节点，直到找到根节点
	}
	return v;
}

vector<Edge> Kruskal(EdgeGraph &graph)
{
	vector<Edge> ret;
	sort(graph.edge, graph.edge + graph.edgeNum, cmp);
	for (int i = 0; i < graph.vertexNum; ++i)
	{
		graph.parent[i] = -1;
	}
	int num = 0;
	for (int i = 0; i < graph.edgeNum; ++i)
	{
		if (num == graph.vertexNum - 1){
			return ret;
		}
		int vex1 = findRoot(graph.parent, graph.edge[i].from);
		int vex2 = findRoot(graph.parent, graph.edge[i].to);
		if (vex1 != vex2){
			graph.parent[vex2] = vex1;
			ret.push_back(graph.edge[i]);
			num++;
		}
	}
}


int main()
{
	EdgeGraph graph;
	graph.edgeNum = 9;
	graph.vertexNum = 6;
	graph.edge[0].from = 1;
	graph.edge[0].to = 4;
	graph.edge[0].weight = 12;
	graph.edge[1].from = 2;
	graph.edge[1].to = 3;
	graph.edge[1].weight = 17;
	graph.edge[2].from = 0;
	graph.edge[2].to = 5;
	graph.edge[2].weight = 19;
	graph.edge[3].from = 2;
	graph.edge[3].to = 5;
	graph.edge[3].weight = 25;
	graph.edge[4].from = 3;
	graph.edge[4].to = 5;
	graph.edge[4].weight = 25;
	graph.edge[5].from = 4;
	graph.edge[5].to = 5;
	graph.edge[5].weight = 26;
	graph.edge[6].from = 0;
	graph.edge[6].to = 1;
	graph.edge[6].weight = 34;
	graph.edge[7].from = 3;
	graph.edge[7].to = 4;
	graph.edge[7].weight = 38;
	graph.edge[8].from = 0;
	graph.edge[8].to = 2;
	graph.edge[8].weight = 46;
	vector<Edge> v = Kruskal(graph);
	return 0;
}
