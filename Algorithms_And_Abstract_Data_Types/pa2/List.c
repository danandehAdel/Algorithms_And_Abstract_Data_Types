/*
Adel Danandeh 
CMPS 101 - Project #2

*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

List newList(void){
	List newList = (List) malloc (sizeof(ListObject));

	newList->front = NULL;
	newList->back = NULL;
	newList->cursor = NULL;
	newList->length = 0;

	return newList;
}

int length(List L){

	return L->length;

}

int getIndex(List L) {

	int index = -1;
	Node temp = L->cursor;

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

	if(length(L) > 0, getIndex(L) >= 0){
		return L->cursor->data;
	}

	return -1;
}

int equals(List A, List B){

	Node tempNode1 = A->front;
	Node tempNode2 = B->front;

	while (tempNode1 != NULL && tempNode2 != NULL) {

		if (tempNode1->data != tempNode2->data) {

			return 0;
		}

		tempNode1 = tempNode1->forward;
		tempNode2 = tempNode2->forward;
	}

	return 1;
}

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

void movePrev(List L){

	if (getIndex(L) <= length(L) - 1) {
		L->cursor = L->cursor->backward;
	}

	else if (getIndex(L) == 0) {

		L->cursor = NULL;
	}
	return;
}
void moveNext(List L){

	if (getIndex(L) < length(L) - 1) {

		L->cursor = L->cursor->forward;
	}

	else if (getIndex(L) == length(L) - 1) {
		L->cursor = NULL;
	}
	return;
}

void prepend(List L, int data){

	Node newNode = (Node) malloc (sizeof(NodeObject));

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

void append(List L, int data){

	Node newNode = (Node) malloc (sizeof(NodeObject));

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

void insertBefore(List L, int data){

	if (getIndex(L) >= 0 && length(L) > 0) {

		Node newNode = (Node) malloc (sizeof(NodeObject));
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

void insertAfter(List L, int data){

	if (getIndex(L) >= 0 && length(L) > 0) {

		Node newNode = (Node) malloc (sizeof(NodeObject));
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

void deleteFront(List L){

	if (length(L) > 0) {

		if (L->front->forward == NULL) {

			free(front);
			L->front = NULL;
			L->back = NULL;	
		}

		else {

			L->front = L->front->forward;
			free(L->front->backward);
			L->front->backward = NULL;
		}

	}

	L->length--;

	return;
}

void deleteBack(List L){

	if (length(L) > 0) {

		if (L->back->backward == NULL) {

			free(free);
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

void delete(List L){

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

List copyList(List L) {

	Node temp = L->front;
	List newL;
	int i;
	newL = newList();

	for (i = 0; i < L->length-1; i++) {

		append(newL, temp->data);
		temp = temp->forward;
	}

	return newL;
}

void printList(FILE* out, List L){
	
	Node temp = L->front;

	while(temp != NULL){

		fprintf(out, "%d " , temp->data);
		temp = temp->forward;
	}
}

void clear(List L){

	Node temp = L->front;
	Node temp1;

	while(temp != NULL){

		temp1 = temp;
		temp = temp->forward;
		free(temp1);
	}


	L->front = NULL;
	L->back = NULL;
	L->length = 0;
}

void freeList(List* L){

	clear(*L);
	free(*L);
}
