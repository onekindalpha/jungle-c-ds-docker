//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 실제로 정의한 구조체 타입과
// 그 구조체 타입에 붙인 별칭(alias)
typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode
// 실제로 정의한 구조체 타입과
// 그 구조체 타입에 붙인 별칭(alias)
typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);
void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			// 여기서 삽입할 값을 받고 있음. 
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 해당 함수는 정렬된 리스트에서 몇 번째 위치에 넣어야 하는지만 찾는다. 
// 그리고 실제 삽입은 기존 함수한테 맡긴다. 
int insertSortedLL(LinkedList *ll, int item) {
	// LinkedList *ll -> ll의 타입 자체가 LinkedList *임. 
	// 함수 안에서 ll->head를 사용하는 것이고, 
	// 그리고 만약 다른 함수가 똑같이 int insertNode(LinkedList *ll, int index, int value)를 받는 다면 그냥 insertNode(ll, index, item);이라고 넘기는 것임. 

	/* add your code here */
	ListNode *cur = ll->head;
	// 현재 노드는 연결리스트의 헤드를 가리키고. 
	// 인덱스는 0을 가리키고. 
	// 현재 보고 있는 노드의 위치는 index이다. 
	int index = 0;
	// 현재 노드가 NULL이 아닌 이상
	while (cur!= NULL) {
		// 현재 item이 현재 받고 있는 정수값이랑 같으면
		if (cur -> item == item) {
			// 이미 중복값이 들어있는 것이므로 -1을 반환한다. 
			return -1;
		}
		// 현재 아이템이 내가 받고 있는 정수값보다 크게 되면
		// 그 순간 바로 종료를 한다. 
		if (cur-> item > item) {
			break;
		}
		// 그리고 while문이 끝나지 않을때까지
		// 현재 노드를 현재의 다음 노드로 갱신을 한다. 
		cur = cur->next;
		// 인덱스는 계속 증가시킨다. 
		// 현재 보고 있는 인덱스의 위치를 증가시킨다. 
		index ++;
		}
	// 여기서 insertNode()라는 다른 함수를 호출함. 
	// 어느 연결 리스트에, 몇 번 째 위치에, 어떤 정수값을 전달할지를 정함. 
	// 실제로 삽입할 인덱스를 전달을 하고
	insertNode(ll, index, item);
	// 문제에서 삽입된 위치의 index를 반환하라고 했기 때문에 반환함. 
	return index;
}
///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

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

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

// 찾아낸 index에 실제 노드를 삽입함.
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;
	// 이 부분은 if문 + 논리 연산자 || + 비교 연산자가 합쳐진 문법이다. 
	// ||은 or을 사용하는 연산자임. 
	// 조건1 || 조건2 || 조건3 중 하나라도 참이면 전체가 참임. 
	// 이 부분은 아예 잘못된 요청인지 검사함. 
	// (1) 리스트가 NULL이거나, 인덱스가 음수이거나, 허용된 범위를 벗어나면 -1을 반환한다. (셋중 하나라도 이상하면)
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;
	// (2) 유효한 요청 중에서 맨 앞 삽입인지 검사.하는 부분임. 
	// 정상적인 요청인데, 삽입 위치가 맨 앞인가?
	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

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
