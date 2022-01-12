#include "../hdrs/library.h"
#include "../src/library.c"

int main() {
    graph newGraph = createGraph(5);
    connect(newGraph, 1, 2);
    connect(newGraph, 1, 3);
    connect(newGraph, 2, 4);
    connect(newGraph, 3, 4);
    connect(newGraph, 3, 5);
    deleteVertex(newGraph, 4);
    checkGraph(newGraph);
    clearMemory(newGraph);
    return 0;
}
