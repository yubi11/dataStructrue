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
		  1
		/	\
	  2		 3
	/	\	   \
   4	 5		8
		  \	     \
		   6	   9
		  /
		7

전위순회		
1	(2,4,5,6,7)			(3,8,9)				최상위층			
	2	 4 (5,6,7)		3	x (8,9)			괄호 압축을 풀어가는 식임
			5 6 7				8,9			좌측 괄호 없는 부분 읽고 오른쪽 읽으면 됨
124567389

중위순회
(2,4,5,6,7)					1			(3,8,9)
	4	2	(5,6,7)						x	3	8
			x	5	6								9
						7

후위순회
(좌측노드)		(우측노드)	루트노드
=> (2,4,5,6,7)	(3,8,9)		1


*/


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