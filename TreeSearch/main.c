#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode
{
	char key;
	char flag;  //�ж���������   1����  0��ͷ���  -1����
	struct TreeNode *left;
	struct TreeNode *right;
}TREE;

#define MAX_SIZE 100
#define true 1
#define false 0

TREE* createTree(char Pre[MAX_SIZE], char Mud[MAX_SIZE], int leftright);  //����һ����
int ReadTree(TREE *tree);  //����������ķ�ʽ������
int DrawTree(TREE *tree);  //�����Ľṹ������
int print_level(TREE *tree, int level);   //����ȱ�����
void deleteTree(TREE *tree);   //�ͷ�����ռ���ڴ�
int main()
{
	TREE *tree;
	char dataOfTreePre[MAX_SIZE];
	char dataOfTreeMud[MAX_SIZE];
	memset(dataOfTreePre, '\0', MAX_SIZE);
	memset(dataOfTreeMud, '\0', MAX_SIZE);
	printf("��������������ı��ʽ��\n");
	scanf("%s", dataOfTreePre);
	printf("��������������ı��ʽ��\n");
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
	//�жϴ����ǰ����������Ƿ�Ϊ��
	if (strlen(Pre) == 0)
	{
		return NULL;
	}
	char rightMud[MAX_SIZE];   //Ϊ��һ�εĵݹ鴢���������������������
	char leftMud[MAX_SIZE];    //Ϊ��һ�εĵݹ鴢���������������������
	char leftPre[MAX_SIZE];    //Ϊ��һ�εĵݹ鴢����������ǰ���������
	char rightPre[MAX_SIZE];   //Ϊ��һ�εĵݹ鴢����������ǰ���������
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
		if (Mud[i] == Pre[0])   //������������ҵ�ͷ���
		{
			flag = 1;
			continue;
		}
		//���ҵ�ͷ���֮ǰ����������Ľ�����뵽Ϊ��һ�εݹ�
		//���õ�leftMud��
		//ͬʱ��ͷ����е����ݴ��뵽Ϊ��һ�εݹ�������õ�leftPre��
		if (flag == 0)   
		{
			leftMud[n1] = Mud[i];
			leftPre[n1] = Pre[i + 1];
			n1++;
		}
		//�ҵ�ͷ�������������Ľ�����뵽Ϊ��һ�εݹ�
		//���õ�rightMud��
		//ͬʱ��ͷ����е����ݴ��뵽Ϊ��һ�εݹ�������õ�rightPre��
		else if (flag == 1)
		{
			rightMud[n2] = Mud[i];
			rightPre[n2] = Pre[i];
			n2++;
		}
	}
	TREE *tree = (TREE*)malloc(sizeof(TREE));
	tree->key = Pre[0];
	tree->flag = leftright; //�ж����Ľڵ�����λ��
	//����ݹ����
	tree->left = createTree(leftPre, leftMud, 1);
	tree->right = createTree(rightPre, rightMud, -1);
	return tree;
}
int ReadTree(TREE *tree)
{
	if (tree == NULL)
		return 0;
	//���к������
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
		if (tree->flag == 0)  //ͷ���
			printf("(%d)%c",num, tree->key);
		else if (tree->flag == 1)  //������
			printf("(%d)(%c  ",num, tree->key);
		else if (tree->flag == -1) //������
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