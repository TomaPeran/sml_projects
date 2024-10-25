#pragma once
#ifndef DFS_HEADER_H
#define DFS_HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int wolf;
    int sheep;
    int cabbage;
    int farmer;
    int state;
    struct Node* next;
} Node;


typedef struct {
    int graphCapacity;
    Node* graphArray;
} Graph;


Graph* graph_Head();

void show_state(Node* state);

int compare_state(Node* state);

void set_main_part(Graph* graph);

void connect_Nodes(Node* mainNode, const int wolf, const int sheep, const int cabbage, const int farmer);

void set_Graph(Graph* graph);

void display_Graph(Graph* graph);

Node* generate_legal_moves(Graph* head, Node* state);

int deep_search_first(Graph* head, Node* start, int depth);

void free_Graph(Graph* head);

#endif // !DFS_HEADER_H

