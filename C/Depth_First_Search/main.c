#include "DFS_Header.h"


int main() {
    Graph* graph = graph_Head();

    set_Graph(graph);
    display_Graph(graph);

    deepSearchFirst(graph, graph->graphArray, 10);
    //printf("Wolf: start, Sheep: start, Cabbage: start, Farmer: start");
    
    free_Graph(graph);

	return 0;
}