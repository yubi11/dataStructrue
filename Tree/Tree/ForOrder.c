#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left, * right;
}TreeNode;

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];

void pushf(TreeNode* p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}

TreeNode* popf()
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

void inorder_iter(TreeNode* root)
{
	while (1)
	{
		for (; root; root = root->left)
			pushf(root);
		root = popf();
		if (!root)
			break;
		printf("[%d]", root->data);
		root = root->right;
	}
}

TreeNode fn1 = { 1,NULL,NULL };
TreeNode fn2 = { 4, &fn1,NULL };
TreeNode fn3 = { 16,NULL,NULL };
TreeNode fn4 = { 25,NULL,NULL };
TreeNode fn5 = { 20,&fn3,&fn4 };
TreeNode fn6 = { 15,&fn2,&fn5 };
TreeNode* froot = &fn6;

/*
int main()
{
	printf("중위 순회=");
	inorder_iter(froot);
	printf("\n");
	return 0;
}
*/