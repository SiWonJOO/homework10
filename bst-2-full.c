/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node { //노드 구조체 선언 트리이기때문에 왼쪽 오른쪽 자식노드가 필요함.
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */ // 스택 초기값 선언및 초기화
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE]; 
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */ // 원형큐 초기값 선언및 초기화
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1; 
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;
 printf("[----- [SIWON JOO] [2018038045] -----]");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { // 노드를 초기화하는 함수 , 노드의 값을 바꾸기 위해 더블포인터로 받음

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // 노드가 비어있지않다면
		freeBST(*h); // 메모리 할당을 해제한다.

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));// 헤드노드를 만들어 메모리를 할당한다.
	(*h)->left = NULL;	/* root */ 
	(*h)->right = *h; 
	(*h)->key = -9999; // 키 값 초기화

	top = -1; // 스택탑의 초기값을 위해 초기화

	front = rear = -1; // 원형큐의 초기값을 위해 초기화

	return 1;
}



void recursiveInorder(Node* ptr) // 재귀방식의 중위 순환 함수.
{
	if(ptr) {
		recursiveInorder(ptr->left); //재귀를 통해 ptr의 왼쪽자식을 가르킨다.
		printf(" [%d] ", ptr->key); // ptr의 key값 출력
		recursiveInorder(ptr->right);  //재귀를 통해 ptr의 오른쪽 자식을 가르킨다.
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) // 반복적 중위 순회 함수.
{
	for(;;)
	{
		for(; node; node = node->left) //왼쪽 자식 노드로 계속 내려감
			push(node); // 내려가면서 스택에 push 해준다.
		node = pop(); // 팝해서 최상단 스택에 값을 노드에 넣어준다.

		if(!node) break; // 노드가 비었다면 반복문 탈출
		printf(" [%d] ", node->key); //키 값 출력

		node = node->right; // 노드를 오른쪽 자식노드로 이동시킨다.
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨순서 순회
{
   // int front = rear = -1;

   if(!ptr) return; /* empty tree */ //공백트리라면 함수 빠져나옴

   enQueue(ptr); //큐에 ptr을 넣는다

   for(;;) // 무한 반복
   {
      ptr = deQueue();//선출 선입 ptr 의 선입력된값을 대입해준다. 
      if(ptr) {
         printf(" [%d] ", ptr->key); // ptr 이 있다면 ptr의 키 값을 출력한다.

         if(ptr->left) // 왼쪽 노드라면
            enQueue(ptr->left); //큐에 왼쪽 노드 삽입
         if(ptr->right)//오른쪽 노드라면
            enQueue(ptr->right);//큐에 오른쪽 노드 삽입
      }
      else
         break;

   }

}



int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // newnode 를 동적메모리 할당해준다.
	newNode->key = key; // newnode의 입력받은 키값을 넣어준다.
	newNode->left = NULL; // 왼쪽 오른쪽 자식을 초기화 해준다.
	newNode->right = NULL;

	if (head->left == NULL) { // 만약 왼쪽 노드가 NULL 이라면
		head->left = newNode; // 입력받은 키값을 대입해준다.
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {// ptr이 빌어있지않다면 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //입력받은 key 값과 ptr의 key 값이 같으면 함수 빠져나옴 중복허용 x

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; // 부모노드에 ptr 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
      if(ptr->key < key) //입력받은 key값이 루트노드 보다 크다면
         ptr = ptr->right; // 오른쪽노드로 이동
      else //작다면 왼쪽 노드로 이동
         ptr = ptr->left;
   }

   /* linking the new node to the parent */
   if(parentNode->key > key)  // 부모노드의 key값이 입력받은 key 보다 더 크다면
      parentNode->left = newNode; // 왼쪽에 입력받은 노드 삽입
   else
      parentNode->right = newNode; // 오른쪽에 입력받은 노드 삽입
   return 1;
}


int deleteNode(Node* head, int key) // 입력한 KEY 값이 있다면 그 값을 가진 노드를 삭제하는 함수
{
	if (head == NULL) { // 헤드가 초기화 되어있지않다면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // 노드가 비었다면 오류메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; // ROOT 에 루트노드 삽입



	Node* parent = NULL; // 부모노드 초기화
	Node* ptr = root; // 루트노드 초기화

   while((ptr != NULL)&&(ptr->key != key)) { //ptr노드가 NULL이면서 입력받은 key값이랑 다를 때까지반복
      if(ptr->key != key) {// 입력받은 key값이랑 다른 경우

			parent = ptr;	/* save the parent */

      if(ptr->key > key) //입력받은 key값보다 큰 경우
            ptr = ptr->left;// 왼쪽으로 이동
         else //작은 경우
            ptr = ptr->right; //오른쪽으로 이동 
		}
	}

	/* there is no node for the key */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key); // 오류메세지 출력
		return -1;
	}

   /*
    * case 1: the node which has to be removed is a leaf node
    */
   if(ptr->left == NULL && ptr->right == NULL) // 리프노드인 경우
   {
      if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
         if(parent->left == ptr) //ptr이 부모노드의 왼쪽 노드인 경우
            parent->left = NULL; //왼쪽 노드 NULL 값 대입
         else
            parent->right = NULL; //오른쪽 노드 NULL 값 대입
      } else {
         /* parent is null, which means the node to be deleted is the root */
         head->left = NULL; // 루트노드의 NULL값을 넣어준다.
      }

      free(ptr); //ptr의 메모리 해제
      return 1;
   }

	 /**
    * case 2: if the node to be deleted has one child
    */
   if ((ptr->left == NULL || ptr->right == NULL)) //자식노드가 한개라면
   {
      Node* child; //구조체 포인터 변수 child 선언
      if (ptr->left != NULL) // 왼쪽 노드가 있다면
         child = ptr->left; // 자식노드를 왼쪽 노드로 설정
      else
         child = ptr->right; // 자식노드를 오른쪽 노드로 설정

      if(parent != NULL) //부모노드가 있는 경우
      {
         if(parent->left == ptr) // 부모노드의 왼쪽 노드가 ptr이라면
            parent->left = child; // 부모노드의 왼쪽 노드에 child 삽입
         else
            parent->right = child; //부모노드의 오른쪽 노드에 child 삽입
      } else {
         /* parent is null, which means the node to be deleted is the root
          * and the root has one child. Therefore, the child should be the root
          */
         root = child; //루트노드에 child 노드 삽입
      }

      free(ptr);//메모리 해제
      return 1;
   }

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate;
	parent = ptr; // ptr을 부모노드로 만든다.


	candidate = ptr->right; // ptr의 오른쪽 노드를 candidate 로 만든다.

	/* the smallest node is left deepest node in the right subtree of the ptr */
 while(candidate->left != NULL) // 리프노드까지 반복
   {
      parent = candidate;  //부모노드에 candidate를 넣어준다.
      candidate = candidate->left; //candidate 노드 상단 트리에서 맨 왼쪽 리프 노드까지 이동
   }

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	  if (parent->right == candidate) //부모노드의 오른쪽 자식 노드인 경우
      parent->right = candidate->right; //부모노드의 오른쪽 자식노드에 candidate->right 노드 삽입
   else
      parent->left = candidate->right; //부모노드의 왼쪽 자식 노드에 candidate->right 노드 삽입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //ptr에 key값에 candidiate key값 대입

	free(candidate); // candidate 메모리 할당 해제
	return 1;
}


void freeNode(Node* ptr) // 재귀적 방식으로 노드의 메모리를 해제하는 함수
{
	if(ptr) {
		freeNode(ptr->left); 
		freeNode(ptr->right);
		free(ptr); // 자식노드들을 전부 메모리 해제후 ptr 메모리 할당 해제
	}
}

int freeBST(Node* head) // 이진트리 메모리 할당 해제하는 함수
{

	if(head->left == head) //헤드노드만 있다면
	{
		free(head); // 헤드노드 메모리 할당해제
		return 1;
	}

	Node* p = head->left; // 노드 p를 루트 노드로 만들어주고

	freeNode(p); // 노드들의 메모리를 해제

	free(head); // 헤드노드 메모리 할당을 헤제한다.
	return 1;
}



Node* pop() // 스택을 pop 하는 함수
{
	if (top < 0) return NULL;
	return stack[top--]; // pop 했기때문에 현재 스택에 최상위의 값을 return 하고 top 이 하나 줄어든다.
}

void push(Node* aNode) // 스택에 push 하는 함수
{
	stack[++top] = aNode; // 스택을 하나 증가시켜 값을 push 한다.
}


void printStack() // 스택을 출력하는 함수
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) 
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); // 스택에 있는 키 값을 출력한다.
	}
}


Node* deQueue() // 디큐 함수 구현
{
	if (front == rear) { // front == rear 랑 같으면 인큐가 안되었기때문에 오류메세지 출력
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; // 원형큐이기떄문에 FRONT를 하나 증가시켜 max size의 나머지값을 front 에 넣는다.
	return queue[front]; // 선입선출 이므로 처음에 들어오값이 return 된다.

}

void enQueue(Node* aNode) // 큐 함수 구현
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear 를 증가시킴 // 원형큐라 나머지값방식을 사용함.
	if (front == rear) {
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; // rear에 입력받은 노드를 저장한다.
}





