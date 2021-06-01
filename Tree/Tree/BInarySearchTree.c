#include <stdio.h>
#include <stdlib.h>

// 중위순으로 트리를 만들어 놓으면 
// 즉 왼쪽 트리는 루트보다 작은값, 오른쪽은 루트보다 큰 값으로 저장해 놓는다면
// 중위 순위 탐색을 할 시 오름차순 정렬 값을 얻을 수 있음

typedef struct BTreeNode
{
	int data;
	struct BTreeNode* left, * right;
}BTreeNode;


BTreeNode* search(BTreeNode* node, int key)
{
	if (node == NULL)							// 해당 key값을 왼쪽먼저찾고 오른쪽을 찾음
		return NULL;
	if (key == node->data)
		return node;
	else if (key < node->data)
		return search(node->left, key);
	else
		return search(node->right, key);

}

BTreeNode* ForSearch(BTreeNode* node, int key)		// for문으로 구현
{
	while (node != NULL)
	{
		if (key == node->data)
			return node;
		else if (key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

//탐색 후, 삽입연산을 하여 BinaryTree를 만듬 허나 중복허용 안함
BTreeNode* Insert_node(BTreeNode* node, int key)
{
	BTreeNode* newNode;
	if (node == NULL)
	{
		newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
		newNode->data = key;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}
	if (key < node->data)
		node->left = Insert_node(node->left, key);
	else if (key > node->data)
		node->right = Insert_node(node->right, key);
	return node;
}


//탐색후 삭제, 3가지 경우 존재, 단말노드 삭제, 하나의 서브트리를 가진경우, 두개의 서브트리를 가진 경우
// 단말노드는 그냥 지우면 됨
// 한개의 서브트리를 가진 경우는 다음서브트리를 그냥 삭제할노드의 전노드에 이어줌
// 두개의 서브트리를 가진 경우는, 지울노드의 왼쪽서브트리에서 가장 큰 값, 오른쪽서브트리에서 가장 낮은 값 중 하나로 대체를 하면 된다
// 그래도 이진트리는 유지 됨, 그러나 이진탐색트리가 더 좋은 탐색트리가 되기 위해선, 그 두 노드 중 비슷한 값을 넣는게 좋음
BTreeNode* min_value_node(BTreeNode* node)
{
	BTreeNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

BTreeNode* max_value_node(BTreeNode* node)
{
	BTreeNode* current = node;
	while (current->right != NULL)
		current = current->right;
	return current;
}


BTreeNode* delete_node(BTreeNode* root, int key)
{
	if (root == NULL)
		return root;
	if (key < root->data)
		root->left = delete_node(root->left, key);				//키 값이 루트보다 낮을 시 왼쪽 순환
	else if (key > root->data)
		root->right = delete_node(root->right, key);			//키 값이 루트보다 높을 시 오른쪽 순환
	else
	{															//값이 매치되는경우
		if (root->left == NULL)									// 해당 노드의 왼쪽을 살펴봄,
		{														// 아무것도 없으면 오른쪽 저장 후 현재 루트 삭제
			BTreeNode* temp = root->right;
			free(root);
			return temp;										//반환되는 오른쪽값은 순환문을 빠져나오면서 윗 노드와 이어지게 됨
		}
		else if (root->right == NULL)							//해당 노드의 오른쪽
		{
			BTreeNode* temp = root->left;						//아무것도 없으면 왼쪽 저장 후 현재 루트 삭제
			free(root);
			return temp;										//반환되는 왼쪽값은 순환문을 빠져나오면서 윗 노드와 이어짐
		}

		BTreeNode* temp = min_value_node(root->right);			// 마지막으로, 2개의 노드 둘다 달고 있는 경우, 오른쪽 노드로 가서,서브트리의 최소값을 찾음
		BTreeNode* temp2 = max_value_node(root->left);			// 왼쪽노드는 서브트리의 최대값을 구하게 됨
		if (abs(root->data - temp->data) < abs(root->data - temp2->data))
		{															
			root->data = temp->data;								// 값 비교 후 가장 근접한 값 선택하여 루트로 바꿔줌
			delete_node(root->right, temp->data);					// 그 값을 삭제시키고 
		}
		else
		{
			root->data = temp2->data;
			delete_node(root->left, temp2->data);				// 해당 값을 루트노드에 저장 후
		}
																	// 루트가 카피한 노드를 삭제 시켜줌 마치 자리를 대체하는 것 처럼
	}
	return root;													// 이 루트 반환값은 순환문을 돌며 delete_node의 결과로 나오면서 잘 이어지게됨
}


inorderB(BTreeNode* root)
{
	if (root)
	{
		inorder(root->left);
		printf("[%d]", root->data);
		inorder(root->right);
	}
}



int main()															//이진탐색트리에서 탐색,삽입,삭제 연산의 시간 복잡도는 트리의 높이에 비레함
{

	BTreeNode* n1, * n2, * n3, *n4, *n5;							// 왼쪽서브트리와 오른쪽서브트리가 균형이 맞으면 이것을 balanced 트리라 한다.
	n1 = (BTreeNode*)malloc(sizeof(BTreeNode));						// 최선의경우는 완전이진트리인 경우이다. 이 경우에는, h는 log 2 n인데, 15개의 노드가 들어있다면, 최악의 경우에도 4번의 연산
	n2 = (BTreeNode*)malloc(sizeof(BTreeNode));						// 최악의경우는 한쪽으로 치우쳐진 경사이진트리의 경우로, h=n이 되기 때문에 순차탐색과 시간복잡도가 같다.
	n3 = (BTreeNode*)malloc(sizeof(BTreeNode));
	n4 = (BTreeNode*)malloc(sizeof(BTreeNode));						// 즉, 이진탐색트리에서 최선의경우 탐색,삽입,삭제 연산이 O(log n)이다
	n5 = (BTreeNode*)malloc(sizeof(BTreeNode));						// 최악의경우, O(n)이 된다
																	//최악의 경우를 없애기 위해선, 최대한 balanced 트리를 만들어야한다.

	n5->data = 100;
	n5->left = n4;
	n4->data = 90;
	n5->right = n3;
	n3->data = 120;
	n1->data = 80;
	n2->data = 130;
	n4->left = n1;
	n4->right = NULL;
	n3->right = n2;
	n3->left = NULL;
	n1->left = NULL;
	n1->right = NULL;
	n2->left = NULL;
	n2->right = NULL;

	BTreeNode* answer = search(n5,100);

	printf("%d\n",answer?answer->data:0);

	BTreeNode* answerFor = ForSearch(n5, 120);

	printf("%d\n", answerFor?answer->data:0);

	free(n1);
	free(n2);
	free(n3);
	free(n4);
	free(n5);
	


/*
	BTreeNode* root = NULL;
	BTreeNode* tmp = NULL;

	root = Insert_node(root, 30);
	root = Insert_node(root, 20);
	root = Insert_node(root, 10);
	root = Insert_node(root, 40);
	root = Insert_node(root, 50);
	root = Insert_node(root, 60);
	root = Insert_node(root, 70);

	printf("이진 탐색 트리 중위 순회 결과\n");
	inorderB(root);
	printf("\n\n");
	if (search(root, 30) != NULL)
		printf("이진 탐색 트리에서 30을 발견함\n");
	else
		printf("이진 탐색 트리에서 30을 발견못함\n");
*/


	
	return 0;
}

