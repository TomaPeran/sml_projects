#pragma once
#ifndef BFS_FUNCTIONS_H
#define BFS_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int wolf;
	int sheep;
	int cabbage;
	int farmer;
	int state;
	int parentIndex;
	struct _Node* next;
}Node;

typedef struct {
	int graphCapacity;
	Node* graphArray;
}Graph;

typedef struct {
	int head;
	int tail;
	int capacity;
	Node* array;
}Queue;


Graph* dummy_Graph();

Queue* dummy_Queue();

void set_Main_Part(Graph* graph);

void connect_Nodes(Node* mainNode, const int wolf, const int sheep, const int cabbage, const int farmer);

void set_Graph(Graph* graph);

void displayGraph(Graph* graph);

void show_State(Node* state);

void enque(Queue* queue, Node* gameState);

int state_Value(Node* gameState);

int dequeue(Queue* queue);

void print_Queue(Queue* queue, int flag);

void BreadthFirstGraph(Graph* graph, Queue* queue);

void free_Graph(Graph* graph);

void free_Queue(Queue* queue);


#endif // !BFS_FUNCTIONS_H
