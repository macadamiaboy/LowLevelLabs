#include "../hdrs/library.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*динамический массив neighbours у каждой вершины реализован нелогично,
  ибо функция поиска писалась позже всех, и переделывать не хотелось*/

graph createGraph(int size) {
    graph newGraph = (graph) malloc(sizeof(*newGraph));
    newGraph->size = size;
    newGraph->list = (vertex *) malloc(size * sizeof(vertex *));
    for (int i = 0; i < size; i++) {
        vertex newVertex = (vertex) malloc(sizeof(*newVertex));
        newVertex->number = i + 1;
        newVertex->seen = false;
        newVertex->connections = 0;
        newVertex->neighbours = (int *) malloc(sizeof(int));
        newGraph->list[i] = newVertex;
    }
    return newGraph;
}

void addVertex(graph currentGraph) {
    currentGraph->size++;
    int size = currentGraph->size;
    currentGraph->list = (vertex *) realloc(currentGraph->list, size * sizeof(vertex *));
    vertex newVertex = (vertex) malloc(sizeof(*newVertex));
    newVertex->number = currentGraph->list[size - 2]->number + 1;
    newVertex->seen = false;
    newVertex->connections = 0;
    newVertex->neighbours = (int *) malloc(sizeof(int));
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

int* search(graph currentGraph, int knownVertex, int unknownVertex) {
    int *exceptions = (int *) malloc(sizeof(int));
    if (knownVertex == unknownVertex) {
        exceptions[0] = knownVertex;
        return exceptions;
    }
    vertex current = NULL;
    int steps = 1;
    int *way = (int *) malloc(2 * sizeof(int));
    way[0] = 0; way[1] = 0;
    //определяем текущую вершину
    for (int i = 0; i < currentGraph->size; i++) {
        if (currentGraph->list[i]->number == knownVertex) {
            current = currentGraph->list[i];
            current->seen = true;
        }
    }
    if (current == NULL) {
        return exceptions;
    }
    way = recursiveSearch(current, steps, way, currentGraph, unknownVertex);
    if (way[steps] != 0) {
        //printf("%d ", current->number);
        way[steps - 1] = current->number;
        return way;
    } else return exceptions;
}

int* recursiveSearch(vertex current, int steps, int* way, graph currentGraph, int unknownVertex) {
    //printf("current: %d ", current->number);
    for (int i = 0; i < current->connections; i++) {
        //printf("i: %d, steps: %d ", i, steps);
        vertex newVertex = NULL;
        for (int j = 0; j < currentGraph->size; j++) {
            if (currentGraph->list[j]->number == current->neighbours[i]) {
                newVertex = currentGraph->list[j];
                //printf("chosen %d ", newVertex->number);
                break;
            }
        }
        if (newVertex->seen == false) {
            if (newVertex->number == unknownVertex) {
                //printf("%d ", newVertex->number);
                way[steps] = newVertex->number;
                return way;
            }
            newVertex->seen = true;
            steps++;
            way = (int *) realloc(way, (steps + 1) * sizeof(int));
            way[steps] = 0;
            //printf("calling, steps: %d \n", steps);
            way = recursiveSearch(newVertex, steps, way, currentGraph, unknownVertex);
            //printf("returning to %d ", current->number);
            if (way[steps] != 0) {
                //printf("%d ", newVertex->number);
                way[steps - 1] = newVertex->number;
                return way;
            } else steps--;
        }
    }
    way = (int *) realloc(way, (steps) * sizeof(int));
    //printf("step back, steps: %d ", steps);
    return way;
}

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
