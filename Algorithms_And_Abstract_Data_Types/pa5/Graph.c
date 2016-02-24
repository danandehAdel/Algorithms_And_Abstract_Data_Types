/*
Adel Danandeh 

Graph.c contains all the defenition of the functions listed in the header file. 
Functions manage the implamentaion of the Graph.
*/

#include <stdio.h>
#include <stdlib.h>
#include"Graph.h"

typedef struct GraphObj  {
	int order;
	int size;
	int* color;
	int* discover;
	int* parent;
	int* finish;
	List* adj;
} GraphObj;

/*	Function newGraph takes ant integer argument.
*	Returns Graph pointing to new Graph Struct which represents a Graph
*	having n vertices and no edges.  It initializes variables inside the
*   Struct.
*/
Graph newGraph(int n){
	Graph G = (Graph) malloc(sizeof(GraphObj));
	int i;
	G->order = n;
	G->size = 0;
	
	G->adj = (List*) calloc(n+1 ,sizeof(List));
	G->parent = (int*) calloc(n+1 ,sizeof(int));
	G->discover = (int*) calloc(n+1 ,sizeof(int));
	G->color = (int*) calloc(n+1, sizeof(int));
	G->finish = (int*) calloc(n+1, sizeof(int));

	for(i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
	return G;
}

/* Function getOrder takes a Graph as an argument.
*  It returns number of vertices in a graph.
*/
int getOrder(Graph G) {
	return G->order;
}

/* Function getSize takes a Graph as an argument.
*  It returs number of vetices in a graph.
*/
int getSize(Graph G) {
	return G->size;
}

// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){

	if(u >= 1 && u <= getOrder(G)){
		return G->parent[u];
	}

	else{

		return -3;
	}
}

// Pre: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u){

	if( u >= 1 && u <= getOrder(G)){
		return G->discover[u];
	}
	else
		printf("Out of bound!");
	
}

// Pre: 1 <= u <= getOrder(G)
int getFinish(Graph G, int u){

	if( u >= 1 && u <= getOrder(G)){
		return G->finish[u];
	}
	else
		printf("Out of bound!");
	
}

/* Function addEdge takes two integers, and a Graph as arguments. 
*  This function inserts a new edge joining u to v, i.e. u is added
*  to the adjacency List of v, and v to the adjacency List of u. 
*  Pre: Two int arguments must lie in the range 1 to getOrder(G).
*/
void addEdge(Graph G, int u, int v){

	if ((u > 0) && (v > 0) && (u <= getOrder(G)) && (v <= getOrder(G))) { // check to see if u and v are in the range

		addArc(G , u, v);
		addArc(G , v, u);
		G->size--; // size of edges will be incremented twice , since addArc it's been called twice). 
				   // Therefore, decrement size of edges to only add one edge.
	}
}

/* Function addArc takes two integers, and a Graph as arguments.
*  inserts a new directed edge from u to v, i.e. v is added to the 
*  adjacency List of u (but not u to the adjacency List of v).
*  Pre: Two int arguments must lie in the range 1 to getOrder(G).
*/
void addArc(Graph G, int u, int v){

	if ((u > 0) && (v > 0) && (u <= getOrder(G)) && (v <= getOrder(G))) {

		if(length(G->adj[u]) == 0){
			append(G->adj[u], v);
		}
		else{

			moveTo(G->adj[u] , 0);
			int getVal = getElement(G->adj[u]);
			while(getVal < v && getVal != -1){

				moveNext(G->adj[u]);
				getVal = getElement(G->adj[u]);
			}

			if(getVal == -1){
				append(G->adj[u], v);
			}

			if(getVal > v){
				insertBefore(G->adj[u] , v);
			}
		}
	}
	G->size++;
}

/*	Function Visit gets four arguments.
*	Recursive function paired with DFS().  Visits a vertex and all of its
*	descendants.
*/
void visit(Graph G, List L, int x, int* time){
	G->color[x] = GRAY;
	G->discover[x] = (++(*time));

	moveTo(G->adj[x], 0); 
	int y;
	while (getIndex(G->adj[x]) != -1 ) { // Traverse the list
		y = getElement(G->adj[x]);
		if ( G->color[y] == WHITE ) {    // if the color of element in adjacency list is WHITE visit it.
			G->parent[y] = x;
			visit(G, L, y, time);
		}
		moveNext(G->adj[x]);
	}
	G->color[x] = BLACK;
	G->finish[x] = (++(*time));
	prepend(L, x);

}

/* Function DFS runs the deph first search algorithm. 
* This function takes a Graph and a List argument.
* This function does not return anything.
*/

void DFS(Graph G, List S){

	int x;
	int time;
	int i;

	if(length(S) == getOrder(G))
	{
		for(x = 1; x <= G->order; x++)	// Initializing color and parent 
		{
			G->color[x] = WHITE;
			G->parent[x] = NIL;
		}
		time = 0;
		moveTo(S, 0);			    // Setting the cursor's position to the beginning of list
		while(getIndex(S) != -1){   // Travers the entire list

			if(G->color[getElement(S)] == WHITE)
			{
				visit(G, S, getElement(S), &time);  // if the color of the element in list is white  visit it.
			}
			moveNext(S);
			getElement(S);	
		}
	}
	
	for(i = 1; i <= getOrder(G); i++){ // Deletes the previous order
		deleteBack(S);
	}
}

/*	Function transpose() takes a Graph as an argument.
 *	This function returns transpose of graph G. 
 */
Graph transpose(Graph G) {
	Graph newG;
	if (G != NULL) {
		newG = newGraph(getOrder(G));    // New graph is created to hold the values of tranposed graph
		int i, x;
		for (i = 1; i <= getOrder(G); i++) {
			moveTo(G->adj[i], 0);
			while (getElement(G->adj[i]) != -1) { // Travesing the adjacency list
				x = getElement(G->adj[i]);
				addArc(newG, x, i);
				moveNext(G->adj[i]);
			}
		}
	}
	return (newG);
}

/*	Function copyGraph() takes a Graph as an argument.
 *	This function returns a copy of graph G.
 */
Graph copyGraph(Graph G) {
	Graph newG = newGraph(getOrder(G));
	int i;
	
	if(G != NULL){
		for(i = 1; i <= getOrder(G); i++){
			moveTo(G->adj[i], 0);
			while(getElement(G->adj[i]) != -1){  // Traverse through adjacency list
				append(newG->adj[i], getElement(G->adj[i]));
				moveNext(G->adj[i]);
			}
			// Copying color, discover, finish, and parent to newG
			newG->color[i] = G->color[i];
			newG->discover[i] = G->discover[i];
			newG->finish[i] = G->finish[i];
			newG->parent[i] = G->parent[i];
		}
		newG->size = G->size;
	}

	return (newG);
}

/* Function freeGraph takes a Graph pointer.
* This function frees all dynamic memory associated with the
* Graph *pG, then sets the handle *pG to NULL
*/
void freeGraph(Graph* pG){
	int i;
	for(i = 1; i <= getOrder(*pG); i++){
		freeList(&(*pG)->adj[i]);
	}

	free((*pG)->adj);
	free((*pG)->color);
	free((*pG)->discover);
	free((*pG)->parent);
	free((*pG)->finish);
	free(*pG);
	*pG = NULL;
}

void printGraph(FILE* out, Graph G) {
    int i;
    for (i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}