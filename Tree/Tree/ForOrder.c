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

void preorder_iter(TreeNode* root)
{
	while (1)
	{
		for (; root; root = root->left)
		{
			printf("[%d]", root->data);
			if(root->right)
				pushf(root->right);
		}
		root = popf();
		if (!root)
			break;
	}
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

void postorder_iter(TreeNode* root)
{
	TreeNode* prev = root;
	while (1)
	{
		for (; root; root = root->left)
		{
			pushf(root);
		}
		root = popf();

		if (!root)
			break;

		if (!root->right || prev == root->right)
		{
			printf("[%d]", root->data);
			if (prev == root->right)
			{
				prev = root;
				root = NULL;
				continue;
			}
			prev = root;
		}
		else 
			pushf(root);
		
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
	printf("\n전위 순회=");
	preorder_iter(froot);

	printf("\n중위 순회=");
	inorder_iter(froot);

	printf("\n후위 순회=");
	postorder_iter(froot);
	printf("\n");
	return 0;
}

*/