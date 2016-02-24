/*
Adel Danandeh 

GraphTest.c is for testing the graph.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main() {

	int size = 6;
	int s = 1;
	int u;
	Graph newG = newGraph(size);
	List newL = newList();
	int k;

	addEdge(newG, 1, 2);
    addEdge(newG, 1, 3);
	addEdge(newG, 2, 4);
	addEdge(newG, 2, 5);
	addEdge(newG, 2, 6);
	addEdge(newG, 3, 4);
	addEdge(newG, 4, 5);
	addEdge(newG, 5, 6);

	if(s >= 1 && s <= getOrder(newG)){ //Making sure that the source vertex, which gets passed into BFS is out of range.
		BFS(newG, s);
		printf("***** Testing getPath ******\n");
		for(u = 1; u <= getOrder(newG); u++){
			printf("Path from %d to %d is: ", getSource(newG), u);
			getPath(newL, newG, u);
			printList(stdout, newL);
			clear(newL);
			printf("\n");
		}

		printf("\n");
		printf("Number of vetrices in the graph: %d\n", getOrder(newG));
		printf("\n");
		printf("Distance from 1 to 4: %d\n", getDist(newG, 4));
		printf("Distance from 1 to 6: %d\n", getDist(newG, 6));
		printf("Distance from 1 to 3: %d\n", getDist(newG, 3));
		printf("Distance from 1 to 5: %d\n", getDist(newG, 5));
		printf("Distance from 1 to 1: %d\n", getDist(newG, 1));
		printf("\n");
		printf("Number of vertices in a graph: %d \n", getOrder(newG));

		//----------------------------------------------------------------------------------
		printf((k = getParent(newG, 4)) == -3 ? "Out of bound!\n" : "Parent of 4: %d\n",  k);
		printf((k = getParent(newG, 6)) == -3 ? "Out of bound!\n" : "Parent of 6: %d\n",  k);
		printf((k = getParent(newG, 10)) == -3 ? "Out of bound!\n" : "Parent of 10: %d\n",  k);
		printf((k = getParent(newG, 1)) == -3 ? "Out of bound!\n" : "Parent of 1: %d\n",  k);
		printf("\n");

		printf("**********************************************************************\n\n");
		printf("Adjacency list representation: \n");
		printGraph(stdout, newG);
		printf("Number of edges in the graph: %d\n", getSize(newG));
		printf("\n");

		printf("**********************************************************************\n\n");
		printf("Adjacency list representation after adding edges between 3 to 6, and 1 to 4: \n");
		addEdge(newG, 3, 6);
		addEdge(newG, 1, 4);
		printGraph(stdout, newG);
		printf("Number of edges in the graph: %d\n", getSize(newG));
		printf("\n");

		printf("**********************************************************************\n\n");
		printf("Making the graph null:\n");
		makeNull(newG);
		printGraph(stdout, newG);
		printf("Number of edges in the graph: %d\n", getSize(newG));
		printf("\n");
		
		// Please note that getParent will be printed as -2 (NIL is defined to be -2) 
		// getDist will be prrinted as -1 (INF is defined to be -1)
		// We expect to see -2 for getParent and -1 for getDist, since Graph is null.
		printf((k = getParent(newG, 4)) == -3 ? "Out of bound!\n" : "Parent of 4: %d\n",  k);
		printf((k = getParent(newG, 6)) == -3 ? "Out of bound!\n" : "Parent of 6: %d\n",  k);
		printf((k = getParent(newG, 10)) == -3 ? "Out of bound!\n" : "Parent of 10: %d\n",  k);
		printf((k = getParent(newG, 1)) == -3 ? "Out of bound!\n" : "Parent of 1: %d\n",  k);

		printf("Distance from 1 to 4: %d\n", getDist(newG, 4));
		printf("Distance from 1 to 6: %d\n", getDist(newG, 6));
		printf("Distance from 1 to 3: %d\n", getDist(newG, 3));
		printf("Distance from 1 to 5: %d\n", getDist(newG, 5));
		printf("Distance from 1 to 1: %d\n", getDist(newG, 1));
		printf("\n");
	}

	freeGraph(&newG);
	freeList(&newL);
	
	return 0;
}
