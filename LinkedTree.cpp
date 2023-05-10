#include<iostream>
#include<cmath>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int val) :val(val), left(NULL), right(NULL)
	{

	}
	TreeNode(int val, TreeNode *left, TreeNode *right) :val(val), left(left), right(right)
	{

	}
};


class Tree
{
public:
	TreeNode *root;
	Tree(int arr[], int n,TreeNode *father=NULL,int num=0) 
	{
		initialize(arr, n, father, num);
	}
	void initialize(int arr[], int n, TreeNode *&father , int num)
	{
		if (num == 0){
			root=new TreeNode(arr[0]);
			initialize(arr, n, root->left, 1);
			initialize(arr, n, root->right, 2);
		}
		if (num >= n){
			return;
		}
		else{
			father = new TreeNode(arr[num]);
			initialize(arr, n, father->left, 2 * num + 1);
			initialize(arr, n, father->right, 2 * num + 2);
		}		
	}
	void deleteTree(TreeNode *root);
	~Tree()
	{
		deleteTree(root);
	}
};

void Tree::deleteTree(TreeNode *root)
{
	if (!root){
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 ,8,9,10};
	Tree tree(arr, 10);
	int c;
	cin >> c;
	return 0;
}
