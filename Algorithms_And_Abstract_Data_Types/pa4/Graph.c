/*
Adel Danandeh 

Graph.c contains all the defenition of the functions listed in the header file. 
Functions manage the implamentaion of the Graph.
*/

#include <stdio.h>
#include <stdlib.h>
#include"Graph.h"

#define INF -1
#define NIL -2
#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct GraphObj  {
	int order;
	int size;
	int source;
	int* color;
	int* distance;
	int* parent;
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
	G->source = NIL;
	G->adj = (List*) calloc(n+1 ,sizeof(List));
	G->parent = (int*) calloc(n+1 ,sizeof(int));
	G->distance = (int*) calloc(n+1 ,sizeof(int));
	G->color = (int*) calloc(n+1, sizeof(int));

	for(i = 1; i <= n; i++){
		G->adj[i] = newList();
	}
	return G;
}

/*	Function getOrder takes a Graph as an argument.
*	It returns number of vertices in a graph.
*/
int getOrder(Graph G) {
	return G->order;
}

/* Function getSize takes a Graph as an argument.
* It returs number of vetices in a graph.
*/
int getSize(Graph G) {
	return G->size;
}

/* Function getSource takes a Graph as an argument.
* It returns the label of the vertex that was most 
* recently used as source.
*/
int getSource(Graph G) {
	return G->source;
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
int getDist(Graph G, int u){

	if( u >= 1 && u <= getOrder(G)){
		return G->distance[u];
	}
	else
		printf("Out of bound!");
	
}

// Pre: getSource(G)!=NIL
void getPath(List L, Graph G, int u){

	int x;
	if( u >= 1 && u <= getOrder(G)){

		if (getDist(G, u) != INF) {
			x = u;
			append(L, x);
			while (getParent(G, x) != NIL) {
				x = getParent(G, x);			
				prepend(L, x);
			}
		}
		else{
			prepend(L, NIL);
		}
	}

	else{
		printf("Error.");
	}

	return;
}

/* Function makeNull takes a Graph as an argument.
* This function deletes all edges of G, restoring 
* it to its original (no edge) state
*/
void makeNull(Graph G) {
	int i;
	for (i = 1; i <= getOrder(G); i++) {
		clear(G->adj[i]);
		G->distance[i] = INF;
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->size = 0;
	}
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
	free((*pG)->distance);
	free((*pG)->parent);
	free(*pG);
	*pG = NULL;
}

/* Function BFS takes a Graph, and integer as arguments.
* This funtion runs the BFS algorithm on the Graph G with 
* source s, setting the color, distance, parent, and source 
* fields of G accordingly
*/
void BFS(Graph G, int s){

	int x, y;
	G->source = s;
	List newL;
	newL = newList();

	for(x = 1; x <= getOrder(G); x++){
		G->color[x] = WHITE;
		G->parent[x] = NIL;
		G->distance[x] = INF;
	}

	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL; 

	append(newL, s);

	while(length(newL) > 0){
		x = front(newL);
		deleteFront(newL); 
		moveTo(G->adj[x], 0);
		y = getElement(G->adj[x]);
		while(getIndex(G->adj[x]) != -1){
			if (G->color[getElement(G->adj[x])] == WHITE) {
				G->color[y] = GRAY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(newL, y);
			}
			
			moveNext(G->adj[x]);
			y = getElement(G->adj[x]);
		}
		G->color[x] = BLACK;
	}
	freeList(&newL);
}

void printGraph(FILE* out, Graph G) {
    int i;
    for (i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}
