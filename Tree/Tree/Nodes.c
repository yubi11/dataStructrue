#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left, * right;
}TreeNode;


int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

int get_node_count_leaves(TreeNode* node)
{
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_node_count_leaves(node->left) + get_node_count_leaves(node->right);
	}
	return count;
}

int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

/*
int main()
{
	TreeNode a1 = { 1,NULL,NULL};
	TreeNode a2 = { 1,NULL,NULL};
	TreeNode a3 = { 1,NULL,NULL};
	TreeNode a4 = { 1,&a1,NULL};
	TreeNode a5 = { 1,&a3,&a2};
	TreeNode a6 = { 1,&a5,&a4};

	printf("노드개수 %d\n",get_node_count(&a6));
	printf("단말노드개수 %d\n", get_node_count_leaves(&a6));
	printf("노드 높이%d\n", get_height(&a6));
	return 0;
}
*/