/*
Adel Danandeh 

FindComponents.c implements the top level client and main program for this project. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char *argv[]){

	FILE *in, *out;
	int i, j;
	int vertex;
	int edge;
	int edge1;
	int connectedC;

	Graph newG;
	Graph newGT;
	List newL = newList();

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL){
		fprintf(stderr, "Can't open input file in.list!\n");
		exit(1);
	}

	fscanf(in, "%d", &vertex);
	fscanf(in, "%d %d", &edge, &edge1);
	newG = newGraph(vertex);
	while(edge != 0 && edge1 != 0){
		addArc(newG, edge, edge1);
		fscanf(in, "%d %d", &edge, &edge1);
	}
	fprintf(out, "Adjacency list representation of G: \n");
	printGraph(out, newG);
	fscanf(in, "%d %d", &edge, &edge1);

	moveTo(newL, 0);
	for(j = 1; j <= getOrder(newG); j++){
		append(newL, j);
		moveNext(newL);
	}
	DFS(newG, newL);

	newGT = transpose(newG);
	DFS(newGT, newL);
	connectedC = 0;
	for(j = 1; j <= getOrder(newGT); j++){

		if(getParent(newGT, j) == NULL){
			connectedC++;
		}
	}
	fprintf(out, "\nG contains %d strongly connected components:\n", connectedC);

	List Comp = newList();

	for (i = 1; i<= connectedC; i++){
		fprintf(out, "Component %d: ", i);
		while(getParent(newGT, back(newL)) != NIL){
			prepend(Comp , back(newL));
			deleteBack(newL);
		}
		prepend(Comp, back(newL));
		deleteBack(newL);
		printList(out, Comp);
		fprintf(out, "\n");
		clear(Comp);
	}

	if (out == NULL){
		fprintf(stderr, "Can't open output file %s!\n", argv[2]);
		exit(1);
	}

	freeList(&Comp);
	freeGraph(&newG);
	freeGraph(&newGT);
	freeList(&newL);
	fclose(in);
	fclose(out);
	return 0;
}