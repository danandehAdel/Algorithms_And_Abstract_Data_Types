/*
Adel Danandeh 

List.c contains all the defenition of the functions listed in the header file. Funtions manage the implamentaion of
the doubly link list. 
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

typedef struct Node{
	int data;
	struct Node* forward;
	struct Node* backward;

} Node;

typedef struct ListObject{
	Node* front;
	Node* back;
	Node* cursor;
	int length;

} ListObject;

// newList creates a new empty list
List newList(void){
	List newList = (List) malloc (sizeof(ListObject));

	newList->front = NULL;
	newList->back = NULL;
	newList->cursor = NULL;
	newList->length = 0;

	return newList;
}

// It returns the length of the list
int length(List L){

	return L->length;

}

int getIndex(List L) {

	int index = -1;
	Node *temp = L->cursor;

	while (temp != NULL) {

		temp = temp->backward;
		index++;
	}

	return index;

}

int front(List L){

	if(length(L) > 0){

		return L->front->data;
	}
	return -1;
}

int back(List L){

	if(length(L) > 0){
		return L->back->data;
	}

	return -1;
}

int getElement(List L){

	if(length(L) > 0 && getIndex(L) >= 0){
		return L->cursor->data;
	}

	return -1;
}

// equals function takes two list as argument. 
// It checks to see if the two passed lists are 
// equal or not.
int equals(List A, List B){

	Node *tempNode1 = A->front;
	Node *tempNode2 = B->front;

	while (tempNode1 != NULL && tempNode2 != NULL) {

		if (tempNode1->data != tempNode2->data) {

			return 0;
		}

		tempNode1 = tempNode1->forward;
		tempNode2 = tempNode2->forward;
	}

	return 1;
}

// moveTo takes a list and an integer argument. 
// cursor will be moved to a target index.
void moveTo(List L, int i){

	int j = 0;
	L->cursor = L->front;

	if (length(L) > 0) {
		while (i > j) {

			L->cursor = L->cursor->forward;
			j++;
		}
	} else

		L->cursor = NULL;

	return;
}

// moveNext takes a list argument. 
// If 0 <= getIndex() < length() - 1, moves the cursor backward 
// one step.
void movePrev(List L){

	if (getIndex(L) >= 0 && getIndex(L) <= length(L) - 1) {
		L->cursor = L->cursor->backward;
	}

	else if (getIndex(L) == 0) {

		L->cursor = NULL;
	}
	return;
}

// moveNext takes a list argument. 
// If 0 <= getIndex() < length() - 1, moves the cursor forward 
// one step.
void moveNext(List L){

	if (getIndex(L) >= 0 && getIndex(L) < length(L) - 1) {

		L->cursor = L->cursor->forward;
	}

	else if (getIndex(L) == length(L) - 1) {
		L->cursor = NULL;
	}
	return;
}

// append takes a list and an integer (data) as argument.
// This function inserts a new element before front element.
void prepend(List L, int data){

	Node *newNode = (Node*) malloc (sizeof(Node));

	if (length(L) == 0) {

		L->front = newNode;
		L->back = newNode;
		newNode->backward = NULL; 
		newNode->forward = NULL;
	}

	else {


		L->front->backward = newNode;
		newNode->forward = L->front;
		newNode->backward = NULL;
		L->front = newNode;
	}
	newNode->data = data;
	L->length++;

	return;
}

// append takes a list and an integer (data) as argument.
// This function inserts a new element after back element.
void append(List L, int data){

	Node *newNode = (Node*) malloc (sizeof(Node));

	if (length(L) == 0) {

		L->front = newNode;
		L->back = newNode;
		newNode->backward = NULL; 
		newNode->forward = NULL;

	}

	else {

		L->back->forward = newNode;
		newNode->backward = L->back;
		L->back = newNode;
		newNode->forward = NULL;

	}
	newNode->data = data;
	L->length++;

	return;
}

// insertBefore function takes a list and int (data) argumnet. 
// This function inserts a new element before cursor element. 
// Pre: getIndex(L) >= 0 && length(L) > 0
void insertBefore(List L, int data){

	if (getIndex(L) >= 0 && length(L) > 0) {

		Node *newNode = (Node*) malloc (sizeof(Node));
		newNode->data = data;

		if (L->cursor->backward == NULL) {

			L->cursor->backward = newNode;
			newNode->forward = L->cursor;
			L->front = newNode;
			newNode->backward = NULL;
		}

		else {

			newNode->forward = L->cursor;
			newNode->backward = L->cursor->backward;
			L->cursor->backward->forward = newNode;
			L->cursor->backward = newNode;
		}
	}

	L->length++;

	return;
}

// insertAfter function takes a list and int (data) argumnet. 
// This function inserts a new element after cursor element. 
// Pre: getIndex(L) >= 0 && length(L) > 0
void insertAfter(List L, int data){

	if (getIndex(L) >= 0 && length(L) > 0) {

		Node *newNode = (Node*) malloc (sizeof(Node));
		newNode->data = data;

		if (L->cursor->forward == NULL) {

			L->cursor->forward = newNode;
			newNode->backward = L->cursor;
			newNode->forward = NULL;
			L->back = newNode;
		}

		else {

			newNode->backward = L->cursor;
			newNode->forward = L->cursor->forward;
			L->cursor->forward->backward = newNode;
			L->cursor->forward = newNode;

		}

	}

	L->length++;

	return;
}

// deleteBack function deletes the back element in this list. 
// Pre: length(L) > 0
void deleteFront(List L){
	
	Node* tempNode;
	if (length(L) > 0) {

		if (L->front->forward == NULL) {

			free(L->front);
			L->front = NULL;
			L->back = NULL;	
		}

		else {

			tempNode = L->front;
			L->front = L->front->forward;
			free(tempNode);
			L->front->backward = NULL;
		}

	}

	L->length--;

	return;
}

// deleteBack function deletes the back element in this list. 
// Pre: length(L) > 0
void deleteBack(List L){

	if (length(L) > 0) {

		if (L->back->backward == NULL) {

			free(L);
			L->back = NULL;
			L->front = NULL;
		}

		else {

			L->back = L->back->backward;
			free(L->back->backward);
			L->back->backward = NULL;
		}
	}
	L->length--;

	return;
}

// delete function takes a list as an argument. 
// This function deletes cursor element in this 
// list. Cursor will be undefined after this operation. 
// Pre: getIndex(L) >= 0 && length(L) > 0
void Delete(List L){

	if (getIndex(L) >= 0 && length(L) > 0) {

		if (L->length == 1) {

			L->cursor->forward = NULL;
			L->cursor->backward = NULL;

		}

		else if(getIndex(L) == 0){

			L->cursor->forward = NULL;
			L->cursor->backward = NULL;
			L->front = NULL;
			L->back = NULL;
		}

		else if (getIndex(L) > 0) {

			L->cursor->forward->backward = L->cursor->backward;
			L->cursor->backward->forward = L->cursor->forward;
			L->cursor->forward = NULL;
			L->cursor->backward = NULL;

		}

		else if (getIndex(L) == L->length-1) {

			L->cursor->backward->forward = NULL;
			L->cursor->backward = NULL;
			L->cursor->forward = NULL;
		}
	}

	free(L->cursor);
	L->length--;
	return;
}

// Function copyList takes a list as an argument.
// It copies the list into a new list and the new 
// list gets returned.
List copyList(List L) {

	Node *temp = L->front;
	List newL;
	newL = newList();

	for (int i = 0; i < L->length-1; i++) {

		append(newL, temp->data);
		temp = temp->forward;
	}

	return newL;
}

// This functon prints the list
void printList(FILE* out, List L){
	
	Node *temp = L->front;

	while(temp != NULL){

		fprintf(out, "%d " , temp->data);
		temp = temp->forward;
	}
}

// clear function clears the list and initializes pointers properly
void clear(List L){

	Node *temp = L->front;
	Node *temp1;

	while(temp != NULL){

		temp1 = temp;
		temp = temp->forward;
		free(temp1);
	}


	L->front = NULL;
	L->back = NULL;
	L->length = 0;
}

// freeList makes the list empty
void freeList(List* L){

	clear(*L);
	free(*L);
}
