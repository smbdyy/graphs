#include <stdio.h>
#include "Graph.h"

void printGraph(struct Graph* graph) {
    if (graph == NULL || graph->vertexCount == 0) {
        puts("graph is empty");
        return;
    }

    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        struct Vertex* vertex = graph->vertices[i];
        printf("vertex %u, computer name: %s, port: %u\n", i, vertex->computerName, vertex->port);
        struct AdjacencyList* list = graph->adjacencyLists[i];
        for (unsigned int j = 0; j < list->size; j++) {
            struct Edge* edge = list->edges[j];
            printf("\t edge to %u, ports: ", edge->toVertexNumber);
            for (unsigned int k = 0; k < edge->portsAmount; k++) {
                printf("%u ", edge->ports[k]);
            }
            puts("");
        }
    }

    puts("graph end");
}

int main(int argv, char** args) {
    struct Graph* graph;
    puts("pick an option:\n 0. Create empty graph\n 1. Create random graph\n 2. Exit");

    bool done = false;
    while (!done) {
        unsigned int input;
        scanf("%u", &input);
        switch (input) {
            case 0:
                graph = createEmptyGraph();
                if (graph == NULL) {
                    puts("error while creating a graph");
                    return 0;
                }
                done = true;
                break;
            case 1:
                graph = createRandomGraph();
                if (graph == NULL) {
                    puts("error while creating a graph");
                    return 0;
                }
                done = true;
                break;
            case 2:
                deleteGraph(graph);
                return 0;
            default:
                puts("incorrect value, try again:");
        }
    }

    puts("graph created, available commands:");
    puts("0. Print graph");
    puts("1. Add vertex");
    puts("2. Add edge");
    puts("3. Delete vertex");
    puts("4. Delete edge");
    puts("5. Change vertex computer name");
    puts("6. Edit edge ports");
    puts("7. Find computers with port");
    puts("8. Find distance");
    puts("9. Split to components");

    printGraph(graph);
    deleteGraph(graph);
    return 0;
}