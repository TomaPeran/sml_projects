#include "BFS_Header.h"

/*
	Solution of popular puzzle game
	Wolf, Sheep and Cabbage
	using Breadth First Graph to find solution
*/
int main() {
	
	Graph* graph = dummy_Graph();
	Queue* queue = dummy_Queue();

	set_Graph(graph);
	//displayGraph(graph);

	BreadthFirstGraph(graph, queue);

	free_Graph(graph);
	free_Queue(queue);

	return 0;
}