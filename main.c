#include <stdio.h>
#include "Graph.h"

void printGraph(struct Graph* graph) {
    if (graph->vertexCount == 0) {
        puts("graph is empty");
        return;
    }

    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        struct Vertex* vertex = graph->vertices[i];
        printf("vertex %u, computer name: %s, port: %u\n", i, vertex->computerName, vertex->port);
        struct AdjacencyList* list = graph->adjacencyLists[i];
        for (unsigned int j = 0; j < list->size; j++) {
            struct Edge* edge = list->edges[j];
            printf("\t edge number %u to %u, ports: ", j, edge->toVertexNumber);
            for (unsigned int k = 0; k < edge->portsAmount; k++) {
                printf("%u ", edge->ports[k]);
            }
            puts("");
        }
    }

    puts("graph end");
}

void addVertexDialog(struct Graph* graph) {
    puts("enter computer name (<= 200 characters):");
    char nameBuffer[200];
    scanf("%s", nameBuffer);
    puts("enter port:");
    unsigned int port;
    scanf("%u", &port);

    struct Vertex* vertex = createVertex(nameBuffer, port);
    if (vertex == NULL) {
        puts("error while creating a vertex, returning to main menu");
        return;
    }

    if (addVertex(graph, vertex)) {
        puts("vertex added, returning to main menu");
    }
    else {
        deleteVertex(vertex);
        puts("error while adding the vertex, returning to main menu");
    }
}

void addEdgeDialog(struct Graph* graph) {
    if (graph->vertexCount < 2) {
        puts("graph should contain at least 2 vertices to add an edge");
        return;
    }

    puts("enter 'to' and 'from' vertices numbers:");
    unsigned int to, from;
    scanf("%u %u", &to, &from);

    if (to == from || to >= graph->vertexCount || from >= graph->vertexCount) {
        puts("incorrect input, returning to main menu");
        return;
    }

    puts("enter ports amount:");
    unsigned int amount;
    scanf("%u", &amount);

    unsigned int* ports = (unsigned int* )malloc(sizeof(unsigned int) * amount);
    if (ports == NULL) {
        puts("allocation failure, returning to main menu");
        return;
    }

    puts("enter ports:");
    for (unsigned int i = 0; i < amount; i++) {
        scanf("%u", &ports[i]);
    }

    struct Edge* edge = createEdge(amount, ports, to);
    if (edge == NULL) {
        free(ports);
        puts("error while creating an edge, returning to main menu");
        return;
    }

    if (addEdge(graph, from, edge)) {
        puts("edge added, returning to main menu");
    }
    else {
        deleteEdge(edge);
        puts("error while adding an edge, returning to main menu");
    }
}

void deleteVertexDialog(struct Graph* graph) {
    if (graph->vertexCount == 0) {
        puts("graph is empty, returning to main menu");
        return;
    }

    unsigned int number;
    puts("enter vertex number:");
    scanf("%u", &number);
    if (number >= graph->vertexCount){
        puts("no such vertex, returning to main menu");
        return;
    }

    if (deleteVertexFromGraph(graph, number)) {
        puts("vertex deleted successfully, returning to main menu");
    }
    else {
        puts("error while deleting a vertex, returning to main menu");
    }
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
    puts("10. Exit");

    done = false;
    while (!done) {
        unsigned int input;
        scanf("%u", &input);

        switch (input) {
            case 0:
                printGraph(graph);
                break;
            case 1:
                addVertexDialog(graph);
                break;
            case 2:
                addEdgeDialog(graph);
                break;
            case 3:
                deleteVertexDialog(graph);
                break;
            case 10:
                done = true;
                break;
            default:
                puts("incorrect value, try again:");
        }
    }

    deleteGraph(graph);
    return 0;
}