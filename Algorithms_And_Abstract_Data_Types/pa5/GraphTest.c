/*
Adel Danandeh 

GraphTest.c is for testing the Graph purposes. 
*/

#include <stdio.h>
#include <stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
	
	int SIZE = 10;
	Graph G = newGraph(SIZE);
	Graph T;
	List S = newList();
	int i;
	for( i = 1; i<= 9; i++){
		addArc(G, i, i+1);
	}

	addArc(G, 1, 3);
	addArc(G, 1, 4);
	
	for(i = 1; i<= getOrder(G); i++){append(S, i);}

	printf("\nThe adjacency list of G is:\n");

	printGraph(stdout, G);

	DFS(G, S); 

	T = transpose(G);		// Store the transpose of Graph in T (T is a graph)
	printf("\nTranspose of G is:\n");
	printGraph(stdout, T);	// Print the transpose of Graph
	printf("\n");

	printf("Number of vertices of G is %d.\n", getOrder(G));
	printf("Number of edges of G is %d.\n", getSize(G));
	printf("Parent of 10 is %d.\n", getParent(G, 10));
	printf("Parent of 3 is %d.\n", getParent(G, 3));
	printf("Discover time of 1 is %d.\n",getDiscover(G, 1));
	printf("Finish time of 1 is %d.\n", getFinish(G, 1));
	printf("Discover time of 9 is %d.\n",getDiscover(G, 9));
	printf("Finish time of 9 is %d.\n", getFinish(G, 9));

	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);
	return(0);
}