#include <stdio.h>

typedef struct TreeNode 
{
	int data;
	struct TreeNode* left, * right;
}TreeNode;

//			n1
//	 	 /		\
//		n2		n3
// 순회 시 항상, R보다 L이먼저와야됨
// VLR 전위순회, LVR 중위순회 ,LRV 후위순회 만 가능



/*
int main()
{
	//기본 사용법
	TreeNode* n1, * n2, * n3;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	n3 = (TreeNode*)malloc(sizeof(TreeNode));

	n1->data = 10;
	n1->left = n2;
	n1->right = n3;
	n2->data = 20;
	n2->left = NULL;
	n2->right = NULL;
	n3->data = 30;
	n3->left = NULL;
	n3->right = NULL;
	free(n1);
	free(n2);
	free(n3);
	
	return 0;
}
*/