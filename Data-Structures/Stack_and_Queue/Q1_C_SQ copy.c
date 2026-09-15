//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode; // You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList; // You should not change the definition of LinkedList

//
typedef struct _queue
{
	LinkedList ll;
} Queue; // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;

	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
// ll은 LinkedList를 가리키는 포인터이고
// q는 Queue를 가리키는 포인터임
// *q는 Queue를 가리킴
// Queue q;라는 변수가 있을때 q 자체는 Queue이고, Queue *p = &q; 하면 p는 Queue의 주소를 가지고 있음
// p->ll 이라고 하면 p가 가리키는 Queue안의 ll임
// LinkedList 하나를 받고, 결과를 Queue에 만들어야 하기 때문임.

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
// 직접 구현 버전으로 해보기
{
	// 연결리스트를 큐로 복사하는 함수
	ListNode *cur = ll->head; // 노드첫번째부터 지정
	while (cur != NULL)
	{
		enqueue(q, cur->item);
		cur = cur->next;
	}
}
void removeOddValues(Queue *q)
{
	if (q == NULL) // q 가 NULL이면 그냥 리턴
		return;
	int count = q->ll.size; // 큐에 들어간 길이만큼받아오기 위함
	for (int i = 0; i < count; i++)
	{
		int item = dequeue(q); // 큐의 모든 item을 순회하면서 각 큐에서 제거
		if (item % 2 == 0)		 // 그 아이템이 짝수인 경우 다시 큐에 추가
			enqueue(q, item);		 // 다시 큐에 넣음
	}
}

/////////////////////////////////////////////////////////////////////////////////

// Queue q의 내부 Linked List 맨 뒤에 item을 추가한다.
// enqueue는 뒤에 추가하고
void enqueue(Queue *q, int item)
{
	// q->ll.size는 현재 노드 개수임.
	insertNode(&(q->ll), q->ll.size, item);
}
// Queue는 맨 앞 데이터를 꺼내서 반환한다.
// dequeue 앞에서 제거한다.
// dequeue는 반환값이 int이다.
// 이 함수는 무조건 제거되는 것이 맞음.
int dequeue(Queue *q)
{
	int item;
	// 큐가 비어있지 않으면
	if (!isEmptyQueue(q))
	{
		// (어떤 노드의 주소) -> item 을 붙인다.
		// 큐에서는 맨 앞의 값을 저장한다.
		item = ((q->ll).head)->item;
		// 맨 앞 노드인 0번 위치의 노드를 삭제한다.
		removeNode(&(q->ll), 0);
		// 삭제한 값을 반환한다.
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q)
{
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
}

void printList(LinkedList *ll)
{

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL)
	{
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode *findNode(LinkedList *ll, int index)
{

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0)
	{
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0)
	{
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0)
	{
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL)
	{

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
