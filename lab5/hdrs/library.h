#include <stdio.h>
#include <stdbool.h>
#ifndef CLIB_LIBRARY_H
#define CLIB_LIBRARY_H

typedef struct item {
    bool seen;
    int number;
    int connections;
    int *neighbours;
} *vertex;

typedef struct graphList {
    int size;
    vertex *list;
} *graph;

graph createGraph(int size);
void addVertex(graph currentGraph);
void deleteVertex(graph currentGraph, int item);
void connect(graph currentGraph, int first, int second);
void checkGraph(graph currentGraph);
void clearMemory(graph currentGraph);
void sortNilsInArray(int* array, int size);
int* search(graph currentGraph, int knownVertex, int unknownVertex);
void sortVertices(graph currentGraph, int size);
int* recursiveSearch(vertex current, int steps, int* way, graph currentGraph, int unknownVertex);


#endif //CLIB_LIBRARY_H
