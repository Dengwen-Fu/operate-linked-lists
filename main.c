#include "stdio.h"
#include "stdlib.h"

typedef struct LinkedList
{
	int data;
	struct LinkedList* next;
}defnode;

int removeDuplicates(defnode* head);
defnode* findIntersection(defnode* head1, defnode* head2);
int reverseTwoElements(int position1, int position2, defnode* head);
defnode* mergeSortedLists(defnode* list1, defnode* list2);
defnode* makeLinkedList_int(int firstData, int gap, int quantity, defnode* nextnode);//the beginning data, the gap, quanitity of the list, inserted in which node
defnode* reverseLinkedList(defnode* head);
int insert(char direction, int inputNumber, defnode* head);/*����(a/+)ascending order; ����(d/-)descending order */

int main()
{
	defnode* headNode = (defnode*)malloc(sizeof(defnode));
	defnode* headNode2 = (defnode*)malloc(sizeof(defnode));
	defnode* headNode3 = (defnode*)malloc(sizeof(defnode));
	defnode* headNode4 = (defnode*)malloc(sizeof(defnode));
	defnode* headNode5 = (defnode*)malloc(sizeof(defnode));
	if (headNode == NULL || headNode2 == NULL || headNode3 == NULL || headNode4 == NULL || headNode5 == NULL) return 1;
	headNode->next = makeLinkedList_int(1, 2, 8, NULL);//������1��ʼ������Ϊ2������Ϊ8���������ӵ�NULLǰ��
	headNode2->next = makeLinkedList_int(2, 2, 8, NULL);//������1��ʼ������Ϊ2������Ϊ8���������ӵ�NULLǰ��
	headNode3->next = makeLinkedList_int(1, 2, 8, NULL);

	headNode4->next = makeLinkedList_int(0, 2, 8, NULL);
	headNode5->next = makeLinkedList_int(2, 4, 6, NULL);
	printf("������1��ʼ������Ϊ2������Ϊ8������: \n"); printLinkedList(headNode);

	insert('+', 6, headNode); //�����б��в���6
	printf("�����б��в���6: \n"); printLinkedList(headNode);

	headNode->next = reverseLinkedList(headNode->next); //��ת�б�
	printf("��ת�б�: \n"); printLinkedList(headNode);

	insert('-', 7, headNode); //�����б��в���8
	printf("�����б��в���7: \n"); printLinkedList(headNode);

	reverseTwoElements(5, 2, headNode); //������Բ���˳�����룬���Ը�����Ԫ������
	printf("���õ�5��2��Ԫ��: \n"); printLinkedList(headNode);

	printf("�ϲ������б��ֱ���ʾΪ�б�1���б�2���ϲ�����б�: \n"); 
	printLinkedList(headNode2); 	printLinkedList(headNode3);
	mergeSortedLists(headNode3->next, headNode2->next);
	printLinkedList(headNode3);

	printf("�󲢼������ϲ��������ϲ�ɾ���ظ�Ԫ�أ�ʹ�õ�ǰ��ϲ���ģ�: \n");
	//add some values which are duplicated
	insert('+', 2, headNode3); insert('+', 2, headNode3); insert('+', 5, headNode3); insert('+', 5, headNode3); 	insert('+', 7, headNode3);
	printLinkedList(headNode3);
	removeDuplicates(headNode3->next);
	printLinkedList(headNode3);

	printf("�󽻼���ǰ����Ϊ�������ϣ�������Ϊ������\n������������ԭ�����Ǽ��ϵ�������Ԫ�����ظ�������: \n");
	defnode* intersectionHead;
	insert('+', 6, headNode4);	insert('+', 6, headNode5);
	printLinkedList(headNode4);	printLinkedList(headNode5);
	intersectionHead = findIntersection(headNode4, headNode5);
	removeDuplicates(intersectionHead->next);
	printLinkedList(intersectionHead);

	return 0;
}

defnode* findIntersection(defnode* head1, defnode* head2) {
	defnode* resultHead = (defnode*)malloc(sizeof(defnode));
	resultHead->next = NULL;
	defnode* tail = resultHead;

	defnode* current1 = head1->next;
	while (current1 != NULL) {
		defnode* current2 = head2->next;
		while (current2 != NULL) {
			if (current1->data == current2->data) {
				tail->next = makeLinkedList_int(current1->data, 0, 1, NULL);
				tail = tail->next;
				break;
			}
			current2 = current2->next;
		}
		current1 = current1->next;
	}

	return resultHead;
}

int removeDuplicates(defnode* head) 
{
	defnode* current = head;

	while (current != NULL && current->next != NULL) 
	{
		defnode* runner = current;

		// Remove all nodes with duplicate data
		while (runner->next != NULL) 
		{
			if (runner->next->data == current->data) 
			{
				defnode* temp = runner->next;
				runner->next = runner->next->next;
				free(temp);
			}
			else {
				runner = runner->next;
			}
		}
		current = current->next;
	}
	return 0;
}

defnode* mergeSortedLists(defnode* list1, defnode* list2) {
	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;

	defnode* result;
	if (list1->data <= list2->data) {
		result = list1;
		result->next = mergeSortedLists(list1->next, list2);
	}
	else {
		result = list2;
		result->next = mergeSortedLists(list1, list2->next);
	}
	return result;
}

int reverseTwoElements(int position1, int position2, defnode* head)
{
	if (position1 == position2 || head == NULL || head->next == NULL)  return 1;

	defnode* prev1 = NULL, * current1 = head;
	defnode* prev2 = NULL, * current2 = head;
	int pos = 0;

	// Find the first element
	while (current1 != NULL && pos != position1) 
	{
		prev1 = current1;
		current1 = current1->next;
		pos++;
	}

	pos = 0;

	// Find the second element
	while (current2 != NULL && pos != position2) 
	{
		prev2 = current2;
		current2 = current2->next;
		pos++;
	}

	if (current1 == NULL || current2 == NULL)
		return;

	// Swap the data of the two elements
	int temp = current1->data;
	current1->data = current2->data;
	current2->data = temp;
	return 0;
}

int insert(char direction,  int inputNumber, defnode* head)
{
	defnode* currentNode = head->next;
	defnode* beforeNode = (defnode*)malloc(sizeof(defnode));
	defnode* newNode = (defnode*)malloc(sizeof(defnode));
	if (newNode == NULL || beforeNode == NULL) return 1;
	while (currentNode != NULL)
	{
		if (direction == '+' || direction == 'a')
		{
			if (inputNumber >= currentNode->data)
			{
				beforeNode = currentNode;
				currentNode = currentNode->next;
			}
			else
			{
				break;
			}
		}
		else if (direction == '-' || direction == 'd')
		{
			if (inputNumber <= currentNode->data)
			{
				beforeNode = currentNode;
				currentNode = currentNode->next;
			}
			else
			{
				break;
			}
		}
	}
	beforeNode->next = newNode;
	newNode->data = inputNumber;
	newNode->next = currentNode;
	return 0;
}

defnode* reverseLinkedList(defnode* head)
{
	defnode* beforeOne, * currentOne, * nextOne;
	beforeOne = NULL;
	currentOne = head;
	/*   this one has some bugs, the next version is right
	while (currentOne->next != NULL)
	{
		nextOne = ......
		...... = nextOne;
	}
	return currentOne;
	*/
	while (currentOne != NULL)
	{
		nextOne = currentOne->next; //save the actual next one
		currentOne->next = beforeOne; //change the direction
		beforeOne = currentOne; //move to the next, current one changed into the former one (in the view of the next node)
		currentOne = nextOne; //the actual next one is the current one now
	}
	return beforeOne;
}

defnode* makeLinkedList_int(int firstData, int gap, int quantity, defnode* nextNode) //Insert a node before the node of "nextNode"
{
	defnode* node = (defnode*)malloc(sizeof(defnode));
	if (node == NULL)
	{
		return 1; // Return 1 to indicate failure
	}

	node->data = firstData; // Assign data value

	if (quantity > 1)
	{
		node->next = makeLinkedList_int(firstData + gap, gap, quantity - 1, nextNode); // Recursively create the rest of the list
	}
	else
	{
		node->next = nextNode; // Set the next pointer to the provided next node
	}

	return node;
}

int printLinkedList(defnode* head)
{
	defnode* currentNode = head->next;
	while (currentNode != NULL)
	{
		printf("%3d ", currentNode->data);
		currentNode = currentNode->next;
	}
	printf("\n");
}
