/*
Adel Danandeh 
CMPS 101 - Project #2

*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include<string.h>

char* allocateChar(char str[]);
void insertion(List L, int size, char *str[]);


int main(int argc, char* argv[]){

	FILE* in;
	FILE* out;
	int i = 0;
	int j = 0;
	int k = 0;
	int lineNum = 0;
	char bufferString[60];
	char **arr;
	List newL = newList();

	in = fopen(argv[1], "r");
	while(fgets(bufferString, 60, in)){

		lineNum++;
	}

	fclose(in);
	arr = (char**) malloc (lineNum * sizeof(char*));

	in = fopen(argv[1], "r");
	while(fgets(bufferString, 58, in)){

		arr[i] = allocateChar(bufferString);
		i++;
	}

	fclose(in);
	insertion(newL, lineNum, arr);

	out = fopen(argv[2], "w");
	for( k = 0; k < lineNum; k++){
		moveTo(newL, k);
		fprintf(out, "%s", arr[getElement(newL)]); 	
	}
	fclose(out);
	freeList(&newL);

	for(j = 0; j < lineNum; j++){

		free(arr[j]);	
	}
	free(arr);

	return 0;
}

char* allocateChar(char str[]){

	char* arr;
	arr = (char*) malloc ((strlen(str) + 1) * sizeof(char));
	strcpy(arr, str);

	return arr; 
}

void insertion(List L, int size, char *str[]) {

	int index = 0;
	int i;
	Node temp = L->front;
	append(L, 0);

	for(i = 1; i < size; i++){

		moveTo(L, i-1);

		while((strcmp(str[i] , str[getElement(L)]) < 0) && getIndex(L) > 0){

			movePrev(L);
		}

		if(getIndex(L) == 0 && (strcmp(str[i] , str[getElement(L)]) < 0))
			prepend(L, i);
		else
			insertAfter(L, i);	
	}
}