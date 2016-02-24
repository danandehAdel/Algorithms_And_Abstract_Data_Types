/*
Adel Danandeh

Graph.h is the header file for Graph implementation. All the function protypes
which will do certain operations are listed in this file.
*/

#include <stdio.h>
#include <stdlib.h>
#include"List.h"

#define UNDEF -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

typedef struct GraphObj* Graph;

/* Constructors-Destructors */
Graph newGraph(int n);
void freeGraph(Graph* pG);
/* Access functions */
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

/* Manipulation procedures */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: getLength(S)==getOrder(G) */

/* Other Functions */
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);
