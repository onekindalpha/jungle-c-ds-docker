
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode
{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode; // You should not change the definition of BSTNode

typedef struct _QueueNode
{
	BSTNode *data;
	// QueueNode가 연결리스트 방식으로 만들어져있음
	struct _QueueNode *nextPtr;
} QueueNode; // You should not change the definition of QueueNode

typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
} Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode *dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	// Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the level-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void levelOrderTraversal(BSTNode *root)
{
	// 0. 큐를 먼저 초기화한다.
	QueueNode *head = NULL;
	QueueNode *tail = NULL;
	/* add your code here */
	// 1. root에 넣기.
	enqueue(&head, &tail, root);

	// 2. Queue노드의 data에서 BSTNode의 주소를 꺼냄.
	// 2. 큐에 있는 것을 빼기 (dequeue) - 바로 아래 문장이 조금 어려웠음.
	// 반복문 쓰는 것도 조금 어려웠음. - 그냥 헤드만 넣으면 되는건가.
	// 현재 head 하나만 보고 큐가 비었는지만 확인해도 충분함.
	while (!isEmpty(head))
	{
		BSTNode *cur = dequeue(&head, &tail);
		printf("%d ", cur->item);

		// 비어있지 않으면, 인큐하기.
		if (cur->left != NULL)
			// 3. 팝한 것에 대한 자식 노드들을 큐에 넣기 (enqueue)
			enqueue(&head, &tail, cur->left);

		// 4. 팝한 것에 대한 자식들을 큐에 넣기 (enqueue)
		if (cur->right != NULL)
			enqueue(&head, &tail, cur->right);
	}
}

///////////////////////////////////////////////////////////////////////////////
// 여기서 node는 BSTNode *변수의 주소를 받음
// BSTNode **는 노드를 가리키는 포인터 변수 자체를 바꾸기 위해 사용함.
void insertBSTNode(BSTNode **node, int value)
{
	// *node는 실제 BSTNode를 가리키는 포인터임.
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL)
		{
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value > (*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

// enqueue node

// 각 변수의 의미: headPtr 은 Queue head 포인터의 주소  Queue **
// tailPtr은 Queue의 tail 포인터의 주소
// node는 Queue에 넣을 BSTNode의 주소

void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	// 새로운 포인터 변수를 하나 만들고, 동시에 QueueNode가 들어갈 메모리 공간도 하나 만듦
	// 다음 QueueNode를 가리키는 포인터임.
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	//
	if (newPtr != NULL)
	{
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// if queue is empty, insert at head
		// isEmpty에 head를 전달함.
		//
		if (isEmpty(*headPtr))
		{
			*headPtr = newPtr;
		}
		else
		{ // insert at tail
			// (* ) 포인터를 한번 꺼내는 것
			// 현재 tail이 가리키는 QueueNode의 nextPtr에 새 QueueNode의 주소를 넣는다.

			(*tailPtr)->nextPtr = newPtr;
		}

		*tailPtr = newPtr;
	}
	else
	{
		printf("Node not inserted");
	}
}

BSTNode *dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{
	BSTNode *node = (*headPtr)->data;
	QueueNode *tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL)
	{
		*tailPtr = NULL;
	}

	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
}

void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
