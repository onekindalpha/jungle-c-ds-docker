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
	Queue temp;					 // [1] Queue 타입의 지역변수 선언. 아직 안의 쓰레기값 상태
	temp.ll.head = NULL; //[2] "이 큐는 비어있다"고 명시적으로 표시 (초기화 필수)
	temp.ll.size = 0;		 //[3] 개수도 0으로 명시적 초기화

	ListNode *cur = ll->head; // [4] 원본 리스트 순회용 포인터. ll이 포인터라 ->사용
	ListNode *tail = NULL;		// [5] temp의 현재 마지막 노드를 기억할 포인터. 아직 temp가 비어있으니 NULL로 시작.

	while (cur != NULL) // [6] cur가 리스트 끝(NULL)에 도달할 때까지 반복.
	{
		// ListNode타입을 가리키는 포인터 변수 newNode를 선언
		// 타입 캐스팅 문법 (형변환)
		// 함수호출 문법 (그 타입의 바이트 수를 반환)
		// 큐는 함수가 끝난 뒤에도 계속
		ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
		// [7] Sizeof(ListNode): ListNode 구조체 하나의 바이트 크기르 ㄹ계산
		// [8] malloc(...): 힙에서 그 크기만큼 새 메모리 공간을 요청. 시작 주솔르 반환.
		// [9] (ListNode *) 반환된 (void *)주소를 ListNode*로 캐스팅(타입 명시)
		// [10] newNode: 그 주소를 저장하는 포인터 변수. 이제 "빈 상자" 하나 확보됨.
		// [11] newNode가 가리키는 상자의 item 칸에 cur가 가리키는 원본 노드의 값을 복사
		newNode->item = cur->item;
		// [12] malloc 직후 next칸은 쓰레기 값이므로, 안전하게 "아직 연결 안 됨" 표시
		newNode->next = NULL;
		/// 여기 세줄이 까다로웠고

		if (temp.ll.head == NULL)
			// [13] temp가 지금 비어있는지 검사 (첫번째 노드를 넣는 경우인지 확인)
			temp.ll.head = newNode;
		// [14] 비어있다면 newNode를 temp의 첫 번째 노드(head)로 지정
		else
			// 큐는 뒤에 와야 하니까
			tail->next = newNode;
		// [15] 비어있지 않다면, 기존 마지막 노드(tail)의 next에 newNode를 연결함.
		// tail은 포인터이므로 사용

		tail = newNode;
		//[16] 방금 추가한 newNode가 이제 새로운 마지막 노드이므로 tail을 갱신
		temp.ll.size++;
		// [17] temp의 원소 개수를 1 증가 (size = size +1과 동일)

		cur = cur->next;
		// [18] 원본 리스트에서 다음 노드로 이동. 이게 없으면 무한 루프에 바짐.
	}
	*q = temp; // 완성된 임시 큐를 실제 q에 통째로 대입
						 //[19] while문이 다 끝난 뒤, 완성된 temp 구조체 전체를
						 // q가 가리키는 실제 위치에 통째로 복사(대입)
						 // *q는 q가 가리키는 실제 Queue이므로, 이 대입으로
						 // q->ll.head와 q->ll.size가 한번에 갱신됨.
}
void removeOddValues(Queue *q)
{
	if (q == NULL)
		return;
	// [20] 만약 q자체가 잘못된 포인터(NULL)라면, 아무 작업도 하지 않고 즉시 함수 종료
	// 방어적 코딩: 잘못된 입력으로 인한 크래시 방지
	// [21] 짝수만 담을 임시 큐 선언
	Queue temp;
	// [22] 초기화 (비어있음 표시)
	temp.ll.head = NULL;
	// [23] 초기화
	temp.ll.size = 0;
	// [24] 원본 큐(q)를 순회할 포인터
	ListNode *cur = q->ll.head;
	// [25] temp의 마지막 노드 추적용
	ListNode *tail = NULL;

	//[26] 원본 큐 끝까지 반복
	while (cur != NULL)
	{
		// [27] 지금 처리할 노드를 removed라는 이름으로 별도 저장
		// 이렇게 해두는 이유: 바로 다음 줄에서 cur을 이동시켜버리면
		// "지금 검사하려던 노드"를 가리킬 방법이 없어지기 때문
		// ListNode를 가리키는 포인터 변수 하나임 -어쨋든 지금 처리할 노드
		ListNode *removed = cur;
		// [28] cur을 미리 다음 노드로 이동시켜 둠.
		// 이 줄이 free보다 반드시 먼저 와야 함.
		// 만약 removed를 free한 후에 cur->next를 읽으면
		// 이미 해제된 메모리를 읽는 것이라 위험함.
		cur = cur->next;
		if (removed->item % 2 == 0)
		// [29] removed가 가리키는 노드의 item이 짝수인지 검사 (% : 나머지 연산자)
		{
			// 노드를 새로 만들지 않고, 기존 노드를 재사용해서 옮김
			removed->next = NULL;
			// [30] 이 노드를 temp에 새로 연결할 것이므로
			// 기존에 원본 리스트에서 갖고 있던 next값 (다음원본 노드 주소)를 끊어냄
			// 안 끊으면 temp에 연결한 뒤에도 엉뚱한 원본 노드를 계속 가리키게 됨
			if (temp.ll.head == NULL)
				temp.ll.head = removed;
			// [31] temp가 비어있으면 removed를 head로
			else
				tail->next = removed;
			// [32] 아니면 tail 뒤에 연결
			tail = removed;
			// [33] removed가 이제 temp의 새로운 마지막 노드이므로 tail갱신
			temp.ll.size++;
			// [34] temp의 개수 1 증가
		}
		else
		{
			free(removed);
			// [35] 홀수라면 이 노드는 더 이상 필요없으므로 메모리 해제
			// removed는 이미 [27]에서 안전하게 따로 저장해뒀기 때문에
			// cur은 이미 다음으로 이동한 상태라 안전함.
		}
	}
	*q = temp;
	// [36] 원본 큐(q)의 내용을 완성된 temp로 통째로 교체
	// 이 시점 이전의 q->ll.head는 이미 free되었거나(홀수)
	// temp로 옮겨졌으므로(짝수), 원본 노드들은 잃어버리지 않고 전부 처리된 상태
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
