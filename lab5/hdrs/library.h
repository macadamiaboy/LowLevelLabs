#include <stdio.h>
#ifndef CLIB_LIBRARY_H
#define CLIB_LIBRARY_H

typedef struct item {
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


#endif //CLIB_LIBRARY_H
