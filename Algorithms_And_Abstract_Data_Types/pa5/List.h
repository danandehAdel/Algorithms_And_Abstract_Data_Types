/*
Adel Danandeh

List.h is the header file of this program. All the function protypes
which will do certain operations are listed in this file (header file).
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct ListObject* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);      // create a new list
void freeList(List* pL); // free a list
// Access functions -----------------------------------------------------------
int length(List L);
int getIndex(List L);
int front(List L);
int back(List L);
int getElement(List L);
int equals(List A, List B);
// Manipulation procedures ----------------------------------------------------
void clear(List L);
void moveTo(List L, int i);	// Moving the cursor to target index in list
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void Delete(List L);
// Other operations -----------------------------------------------------------
void printList(FILE* out, List L);
List copyList(List L);
