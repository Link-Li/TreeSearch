#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
	char key;
	char flag;  //判断是左还是右   1是左  0是头结点  -1是右
	struct TreeNode *left;
	struct TreeNode *right;
}TREE;

#define MAX_SIZE 100
#define true 1
#define false 0

TREE* createTree(char Pre[MAX_SIZE], char Mud[MAX_SIZE], int leftright);  //创建一个树
int ReadTree(TREE *tree);  //按后序遍历的方式遍历树
int DrawTree(TREE *tree);  //把树的结构画出来
int print_level(TREE *tree, int level);   //按深度遍历树
void deleteTree(TREE *tree);   //释放树所占的内存
int main()
{
	TREE *tree;
	char dataOfTreePre[MAX_SIZE];
	char dataOfTreeMud[MAX_SIZE];
	memset(dataOfTreePre, '\0', MAX_SIZE);
	memset(dataOfTreeMud, '\0', MAX_SIZE);
	printf("请输入先序遍历的表达式：\n");
	scanf("%s", dataOfTreePre);
	printf("请输入中序遍历的表达式：\n");
	scanf("%s", dataOfTreeMud);
	tree = createTree(dataOfTreePre, dataOfTreeMud, 0);
	ReadTree(tree);
	printf("\n\n");
	DrawTree(tree);

	deleteTree(tree);

	system("pause");
	return 0;
}

TREE* createTree(char Pre[MAX_SIZE], char Mud[MAX_SIZE], int leftright)
{
	//判断传入的前序遍历序列是否为空
	if (strlen(Pre) == 0)
	{
		return NULL;
	}
	char rightMud[MAX_SIZE];   //为下一次的递归储存右子树的中序遍历序列
	char leftMud[MAX_SIZE];    //为下一次的递归储存左子树的中序遍历序列
	char leftPre[MAX_SIZE];    //为下一次的递归储存左子树的前序遍历序列
	char rightPre[MAX_SIZE];   //为下一次的递归储存右子树的前序遍历序列
	memset(rightMud, '\0', MAX_SIZE);
	memset(rightPre, '\0', MAX_SIZE);
	memset(leftMud, '\0', MAX_SIZE);
	memset(leftPre, '\0', MAX_SIZE);
	int i;
	int n1, n2;
	n1 = n2 = 0;
	int flag = 0;
	for (i = 0; i<strlen(Pre); i++)
	{
		if (Mud[i] == Pre[0])   //在中序遍历中找到头结点
		{
			flag = 1;
			continue;
		}
		//在找到头结点之前把中序遍历的结果存入到为下一次递归
		//而用的leftMud中
		//同时把头结点中的数据存入到为下一次递归遍历而用的leftPre中
		if (flag == 0)   
		{
			leftMud[n1] = Mud[i];
			leftPre[n1] = Pre[i + 1];
			n1++;
		}
		//找到头结点后把中序遍历的结果存入到为下一次递归
		//而用的rightMud中
		//同时把头结点中的数据存入到为下一次递归遍历而用的rightPre中
		else if (flag == 1)
		{
			rightMud[n2] = Mud[i];
			rightPre[n2] = Pre[i];
			n2++;
		}
	}
	TREE *tree = (TREE*)malloc(sizeof(TREE));
	tree->key = Pre[0];
	tree->flag = leftright; //判断树的节点的相对位置
	//进入递归过程
	tree->left = createTree(leftPre, leftMud, 1);
	tree->right = createTree(rightPre, rightMud, -1);
	return tree;
}
int ReadTree(TREE *tree)
{
	if (tree == NULL)
		return 0;
	//进行后序遍历
	else
	{
		ReadTree(tree->left);
		ReadTree(tree->right);
		printf("%c  ", tree->key);
	}
	return 0;
}

int DrawTree(TREE *tree)
{
	int i = 0;
	for (i = 0; ; i++) {
		if (!print_level(tree, i)) {
			break;
		}
		printf("\n");
	}
	
	return 0;
}
int print_level(TREE *tree, int level)
{
	static long num = 0;
	num++;
	if (!tree || level < 0)
		return 0;
	if (0 == level)
	{
		if (tree->flag == 0)  //头结点
			printf("(%d)%c",num, tree->key);
		else if (tree->flag == 1)  //左子树
			printf("(%d)(%c  ",num, tree->key);
		else if (tree->flag == -1) //右子树
			printf("(%d)%c)  ",num, tree->key);
		return 1;
	}
	return print_level(tree->left, level - 1) + print_level(tree->right, level - 1);
}
void deleteTree(TREE *tree)
{
	if (tree != NULL)
	{
		deleteTree(tree->left);
		deleteTree(tree->right);
		free(tree);
	}
}