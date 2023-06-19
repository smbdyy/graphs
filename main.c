#include <stdio.h>
#include <memory.h>
#include "Graph.h"

void printGraph(struct Graph* graph) {
    if (graph->vertexCount == 0) {
        puts("graph is empty, returning to main menu");
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

    puts("graph end, returning to main menu");
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

bool hasEdges(struct Graph* graph) {
    for (unsigned int i = 0; i < graph->vertexCount; i++) {
        if (graph->adjacencyLists[i]->size > 0) return true;
    }

    return false;
}

void deleteEdgeDialog(struct Graph* graph) {
    if (!hasEdges(graph)) {
        puts("no edges in graph, returning to main menu");
        return;
    }

    puts("enter 'from' vertex number and edge number:");
    unsigned int vertex, edge;
    scanf("%u %u", &vertex, &edge);
    if (vertex >= graph->vertexCount || graph->adjacencyLists[vertex]->size <= edge) {
        puts("no such vertex or edge, returning to main menu");
        return;
    }

    if (deleteEdgeFromGraph(graph, vertex, edge)) {
        puts("edge successfully deleted, returning to main menu");
    }
    else {
        puts("error while deleting an edge, returning to main menu");
    }
}

void changeVertexComputerNameDialog(struct Graph* graph) {
    if (graph->vertexCount == 0) {
        puts("graph is empty, returning to main menu");
        return;
    }

    unsigned int number;
    puts("enter vertex number:");
    scanf("%u", &number);
    if (number >= graph->vertexCount) {
        puts("no such vertex, returning to main menu");
        return;
    }

    char nameBuffer[200];
    puts("enter new name (<= 200 characters)");
    scanf("%s", nameBuffer);

    memcpy(graph->vertices[number]->computerName, nameBuffer, 200);
    puts("vertex computer renamed successfully");
}

void changeVertexPortDialog(struct Graph* graph) {
    if (graph->vertexCount == 0) {
        puts("graph is empty, returning to main menu");
        return;
    }

    unsigned int number;
    puts("enter vertex number:");
    scanf("%u", &number);
    if (number >= graph->vertexCount) {
        puts("no such vertex, returning to main menu");
        return;
    }

    puts("enter new port:");
    unsigned int newPort;
    scanf("%u", &newPort);
    graph->vertices[number]->port = newPort;
    puts("vertex port changed successfully, , returning to main menu");
}

void addPortDialog(struct Edge* edge) {
    unsigned int port;
    puts("enter port:");
    scanf("%u", &port);

    if (containsPort(edge, port)) {
        puts("port already exists");
        return;
    }

    if (addPort(edge, port)) {
        puts("port added successfully");
    }
    else {
        puts("error while adding the port");
    }
}

void deletePortDialog(struct Edge* edge) {
    unsigned int portNumber;
    puts("enter port number:");
    scanf("%u", &portNumber);

    if (edge->portsAmount <= portNumber) {
        puts("no such port");
        return;
    }

    if (deletePort(edge, portNumber)) {
        puts("port deleted successfully");
    }
    else {
        puts("error while deleting the port");
    }
}

void editEdgePortsDialog(struct Graph* graph) {
    if (!hasEdges(graph)) {
        puts("graph has no edges, returning to main menu");
        return;
    }

    puts("enter 'from' vertex number and edgeNumber number:");
    unsigned int vertex, edgeNumber;
    scanf("%u %u", &vertex, &edgeNumber);
    if (vertex >= graph->vertexCount || graph->adjacencyLists[vertex]->size <= edgeNumber) {
        puts("no such vertex or edgeNumber, returning to main menu");
        return;
    }

    struct Edge* edge = graph->adjacencyLists[vertex]->edges[edgeNumber];
    bool hasPorts = edge->portsAmount > 0;
    printf("enter 0 to add port");
    if (hasPorts) {
        printf(", enter 1 to remove port");
    }
    puts("");

    unsigned int input;
    scanf("%u", &input);
    switch (input) {
        case 0:
            addPortDialog(edge);
            break;
        case 1:
            if (hasPorts) {
                deletePortDialog(edge);
                break;
            }
        default:
            puts("incorrect input");
    }

    puts("returning to main menu");
}

void findComputersWithPortDialog(struct Graph* graph) {
    if (graph->vertexCount == 0) {
        puts("graph is empty, returning to main menu");
        return;
    }

    puts("enter port:");
    unsigned int port;
    scanf("%u", &port);

    struct VertexList* list = findComputers(graph, port);
    if (list == NULL) {
        puts("error while finding computers, returning to main menu");
        return;
    }

    if (list->size == 0) {
        puts("no computers with specified port");
        return;
    }

    printf("computers with port %u and reachable:\n", port);
    for (unsigned int i = 0; i < list->size; i++) {
        printf("%s\n", list->vertices[i]->computerName);
    }

    puts("returning to main menu");
}

void findDistanceDialog(struct Graph* graph) {
    if (graph->vertexCount < 2) {
        puts("graph should contain at least 2 vertices, returning to main menu");
        return;
    }

    puts("enter source and destination vertices numbers:");
    unsigned int to, from;
    scanf("%u %u", &from, &to);

    if (to >= graph->vertexCount || from >= graph->vertexCount) {
        puts("no such vertex, returning to main menu");
        return;
    }

    int distance = findDistance(graph, from, to);
    if (distance == -1) {
        puts("cannot find distance");
    }
    else {
        printf("distance: %d\n", distance);
    }

    puts("returning to main menu");
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
    puts("6. Change vertex port");
    puts("7. Edit edge ports");
    puts("8. Find computers with port");
    puts("9. Find distance");
    puts("10. Split to components");
    puts("11. Exit");

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
            case 4:
                deleteEdgeDialog(graph);
                break;
            case 5:
                changeVertexComputerNameDialog(graph);
                break;
            case 6:
                changeVertexPortDialog(graph);
                break;
            case 7:
                editEdgePortsDialog(graph);
                break;
            case 8:
                findComputersWithPortDialog(graph);
                break;
            case 9:
                findDistanceDialog(graph);
                break;
            case 11:
                done = true;
                break;
            default:
                puts("incorrect value, try again:");
        }
    }

    deleteGraph(graph);
    return 0;
}