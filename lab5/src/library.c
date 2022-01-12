#include "../hdrs/library.h"

#include <stdio.h>
#include <stdlib.h>

graph createGraph(int size) {
    graph newGraph = (graph) malloc(sizeof(*newGraph));
    newGraph->size = size;
    newGraph->list = (vertex *) (vertex) malloc(size * sizeof(vertex *));
    for (int i = 0; i < size; i++) {
        vertex newVertex = (vertex) malloc(sizeof(*newVertex));
        newVertex->number = i + 1;
        newVertex->connections = 0;
        newVertex->neighbours = (int*) malloc(size * sizeof(int));
        newGraph->list[i] = newVertex;
    }
    return newGraph;
}

void addVertex(graph currentGraph) {
    int size = currentGraph->size + 1;
    currentGraph->size = size;
    currentGraph->list = (vertex *) (vertex) realloc(currentGraph->list, size * sizeof(vertex *));
    for (int i = 0; i < (size - 1); i++) {
        currentGraph->list[i]->neighbours =
                (int *) realloc(currentGraph->list[i]->neighbours, size * sizeof(int *));
    }
    vertex newVertex = (vertex) malloc(sizeof(*newVertex));
    newVertex->number = size;
    newVertex->connections = 0;
    newVertex->neighbours = (int *) malloc(currentGraph->size * sizeof(int *));
    currentGraph->list[size - 1] = newVertex;
}

void connect(graph currentGraph, int first, int second) {
    int size = currentGraph->size;
    vertex firstVertex = NULL;
    vertex secondVertex = NULL;
    for (int i = 0; i < size; i++) {
        if (currentGraph->list[i]->number == first) { firstVertex = currentGraph->list[i]; }
        else if (currentGraph->list[i]->number == second) { secondVertex = currentGraph->list[i]; }
    }
    //учесть уже связанность этих узлов
    if (firstVertex == NULL || secondVertex == NULL) {
        printf("You've chosen illegal arguments");
        return;
    }
    else {
        firstVertex->connections++;
        secondVertex->connections++;
        firstVertex->neighbours += secondVertex->number;
        secondVertex->neighbours += firstVertex->number;
    }
}

void deleteVertex(graph currentGraph, int item) {
    if (item == 0) return;
    for (int i = 0; i < currentGraph->size; i++) {
        if (currentGraph->list[i]->number == item) {
            currentGraph->list[i] = NULL;
            continue;
        }
        vertex currentVertex = currentGraph->list[i];
        for (int j = 0; j < currentVertex->connections; j++) {
            if (currentVertex->neighbours[j] == item) {
                currentVertex->neighbours[j] = 0;
                currentVertex->connections--;
                break;
            }
        }
    }
}

//для проверки и отладки
void checkGraph(graph currentGraph) {
    for (int i = 0; i < currentGraph->size; i++) {
        if (currentGraph->list[i] != NULL) {
            vertex currentVertex = currentGraph->list[i];
            printf("%d ", currentVertex->number);
            printf("%d", currentVertex->connections);
            printf("\n");
            for (int j = 0; j < currentVertex->connections; j++) {
                printf("%d ", currentVertex->neighbours[j]);
            }
            printf("\n");
            printf("\n");
        }
    }
}

void clearMemory(graph currentGraph) {
    for (int i = 0; i < currentGraph->size; i++) {
        free(currentGraph->list[i]->neighbours);
        free(currentGraph->list[i]);
    }
    free(currentGraph->list);
    free(currentGraph);
}