#include "../hdrs/library.h"

#include <stdio.h>
#include <stdlib.h>

graph createGraph(int size) {
    graph newGraph = (graph) malloc(sizeof(*newGraph));
    newGraph->size = size;
    newGraph->list = (vertex *) malloc(size * sizeof(vertex *));
    for (int i = 0; i < size; i++) {
        vertex newVertex = (vertex) malloc(sizeof(*newVertex));
        newVertex->number = i + 1;
        newVertex->connections = 0;
        newVertex->neighbours = (int *) malloc(1 * sizeof(int));
        newGraph->list[i] = newVertex;
    }
    return newGraph;
}

void addVertex(graph currentGraph) {
    currentGraph->size++;
    int size = currentGraph->size;
    currentGraph->list = (vertex *) realloc(currentGraph->list, size * sizeof(vertex *));
    vertex newVertex = (vertex) malloc(sizeof(*newVertex));
    newVertex->number = size;
    newVertex->connections = 0;
    newVertex->neighbours = (int *) malloc(1 * sizeof(int));
    currentGraph->list[size - 1] = newVertex;
}

void connect(graph currentGraph, int first, int second) {
    int size = currentGraph->size;
    vertex firstVertex = NULL;
    vertex secondVertex = NULL;
    for (int i = 0; i < size; i++) {
        if (currentGraph->list[i]->number == first) firstVertex = currentGraph->list[i];
        else if (currentGraph->list[i]->number == second) secondVertex = currentGraph->list[i];
    }
    if (firstVertex == NULL || secondVertex == NULL) {
        printf("You've chosen illegal arguments \n");
        return;
    }
    for (int i = 0; i < firstVertex->connections; i++) {
        if (firstVertex->neighbours[i] == secondVertex->number) {
            printf("These vertices are already connected \n");
            return;
        }
    }
    firstVertex->connections++;
    secondVertex->connections++;
    firstVertex->neighbours =
            (int *) realloc(firstVertex->neighbours, firstVertex->connections * sizeof(int));
    secondVertex->neighbours =
            (int *) realloc(secondVertex->neighbours, secondVertex->connections * sizeof(int));
    firstVertex->neighbours[firstVertex->connections - 1] = secondVertex->number;
    secondVertex->neighbours[secondVertex->connections - 1] = firstVertex->number;
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
                sortNilsInArray(currentVertex->neighbours, currentVertex->connections);
                currentVertex->connections--;
                currentVertex->neighbours = (int *)
                        realloc(currentVertex->neighbours, currentVertex->connections * sizeof(int));
                break;
            }
        }
    }
    for (int i = 0; i < currentGraph->size; i++) {
        if (currentGraph->list[i] == NULL) {
            sortVertices(currentGraph, currentGraph->size);
            currentGraph->size--;
            currentGraph->list =
                    (vertex *) realloc(currentGraph->list, currentGraph->size * sizeof(vertex *));
            break;
        }
    }
}

//void search(graph currentGraph, int knownVertex, int unknownVertex) { }

//для проверки и отладки
void checkGraph(graph currentGraph) {
    for (int i = 0; i < currentGraph->size; i++) {
        vertex currentVertex = currentGraph->list[i];
        printf("Graph %d with %d connections \n", currentVertex->number, currentVertex->connections);
        printf("Its neighbour(s) is(are) ");
        for (int j = 0; j < currentVertex->connections; j++) {
            printf("%d ", currentVertex->neighbours[j]);
        }
        printf("\n \n");
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

void sortNilsInArray(int* array, int size) {
    for (int i = 0; i < (size - 1); i++) {
        if (array[i] == 0) {
            int zero = array[i];
            array[i] = array[i + 1];
            array[i + 1] = zero;
        }
    }
}

void sortVertices(graph currentGraph, int size) {
    for (int i = 0; i < (size - 1); i++) {
        if (currentGraph->list[i] == NULL) {
            vertex nullable = currentGraph->list[i];
            currentGraph->list[i] = currentGraph->list[i + 1];
            currentGraph->list[i + 1] = nullable;
        }
    }
}