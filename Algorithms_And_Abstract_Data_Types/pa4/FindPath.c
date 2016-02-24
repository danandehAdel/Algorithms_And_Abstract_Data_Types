///*
//Adel Danandeh 
//
//FindPath.c opens an input file and parse the data properly into the Graph,
//and then it prints the path between vertices. 
//*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	FILE *in, *out;
	int size;
	int vertex1;
	int vertex2;

	Graph newG;
	List newL = newList();

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL) {
		fprintf(stderr, "Can't open input file in.list!\n");
		exit(1);
	}
	fscanf(in, "%d", &size);
	fscanf(in, "%d %d", &vertex1, &vertex2);
	newG = newGraph(size);
	while(vertex1 != 0)
	{
		while(vertex1 != 0 && vertex2 != 0)
		{
			addEdge(newG, vertex1, vertex2);
			fscanf(in, "%d %d", &vertex1, &vertex2);
		}
		printGraph(out, newG);
		fscanf(in, "%d %d", &vertex1, &vertex2);
		while(vertex1 != 0 && vertex2 != 0){
			BFS(newG, vertex1);
			getPath(newL, newG, vertex2);
			fprintf(out, "\n");
			if (front(newL) == -2) {
				fprintf(out, "The distance from %d to %d is infinity\n", vertex1, vertex2);
				fprintf(out, "No %d-%d path exists\n", vertex1, vertex2);
				fprintf(out, "\n\n");
			}
			else {
				fprintf(out, "The distance from %d to %d is %d\n", vertex1, vertex2, getDist(newG, vertex2));
				fprintf(out, "A shortest %d-%d path is: ", vertex1, vertex2);
				printList(out, newL);
				fprintf(out, "\n");
				clear(newL);
			}
			fscanf(in, "%d %d", &vertex1, &vertex2);
		}
	}

	if (out == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", argv[2]);
		exit(1);
	}

	freeGraph(&newG);
	freeList(&newL);
	fclose(in);
	fclose(out);
	return 0;
}