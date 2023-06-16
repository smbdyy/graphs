cmake_minimum_required(VERSION 3.25)
project(graphs C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(graphs
        Edge.c
        Graph.c
        Vertex.c AdjacencyList.c)
