#include "../hdrs/tests.h"
#include "../hdrs/library.h"
#include "../src/library.c"
#include "assert.h"

void runTests() {
    testCreationOfGraph();
    testAdditionOfVertex();
}

void testCreationOfGraph() {
    graph newGraph = createGraph(5);
    assert(newGraph->size == 5);
    for (int i = 0; i < newGraph->size; i++) {
        assert(newGraph->list[i]->number == i + 1);
    }
}

void testAdditionOfVertex() {
    graph newGraph = createGraph(5);
    int oldSize = newGraph->size;
    addVertex(newGraph);
    int newSize = newGraph->size;
    assert(oldSize + 1 == newSize);
    assert(newGraph->list[newSize - 1]->number == newSize);
}