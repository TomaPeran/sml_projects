#include "DFS_Header.h"

Graph* graph_Head() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->graphCapacity = 16;
    graph->graphArray = (Node*)malloc(sizeof(Node) * graph->graphCapacity);

    return graph;
}

void set_main_part(Graph* graph) {
    for (int i = 0; i < graph->graphCapacity; i++) {
        int tmp = i;
        graph->graphArray[i].farmer = tmp % 2;
        tmp = tmp / 2;
        graph->graphArray[i].cabbage = tmp % 2;
        tmp = tmp / 2;
        graph->graphArray[i].sheep = tmp % 2;
        tmp = tmp / 2;
        graph->graphArray[i].wolf = tmp % 2;


        graph->graphArray[i].state = 0;
        graph->graphArray[i].next = NULL;
    }
}

void connect_Nodes(Node* mainNode, const int wolf, const int sheep, const int cabbage, const int farmer) {
    Node* addNode = (Node*)malloc(sizeof(Node));
    addNode->wolf = wolf;
    addNode->sheep = sheep;
    addNode->cabbage = cabbage;
    addNode->farmer = farmer;
    addNode->state = 0;

    addNode->next = mainNode->next;
    mainNode->next = addNode;
}

void set_Graph(Graph* graph) {
    set_main_part(graph);

    // 0
    connect_Nodes(&graph->graphArray[0], 0, 0, 0, 1); // 1
    connect_Nodes(&graph->graphArray[0], 0, 0, 1, 1);  // 3
    connect_Nodes(&graph->graphArray[0], 0, 1, 0, 1);  // 5
    connect_Nodes(&graph->graphArray[0], 1, 0, 0, 1);  // 9
    // 2
    connect_Nodes(&graph->graphArray[2], 0, 0, 1, 1);  // 3
    connect_Nodes(&graph->graphArray[2], 1, 1, 1, 0);  // 11
    // 4
    connect_Nodes(&graph->graphArray[4], 0, 1, 1, 1);  // 7
    connect_Nodes(&graph->graphArray[4], 1, 1, 0, 1);  // 13
    // 5
    connect_Nodes(&graph->graphArray[5], 0, 1, 0, 0);  // 4
    // 7
    connect_Nodes(&graph->graphArray[7], 0, 1, 1, 0);  // 6
    connect_Nodes(&graph->graphArray[7], 0, 0, 1, 0); // 2
    // 8
    connect_Nodes(&graph->graphArray[8], 1, 0, 0, 1);  // 9
    connect_Nodes(&graph->graphArray[8], 1, 0, 1, 1);  // 11
    // 10
    connect_Nodes(&graph->graphArray[10], 1, 1, 1, 1); // 15
    // 11
    connect_Nodes(&graph->graphArray[11], 1, 0, 1, 0);  // 10
    // 13
    connect_Nodes(&graph->graphArray[13], 1, 1, 0, 0); // 12
    connect_Nodes(&graph->graphArray[13], 1, 0, 0, 0);  // 8

}

void display_Graph(Graph* graph) {
    for (int i = 0; i < graph->graphCapacity; i++) {
        printf("Stanje %d:", i);
        Node* tmp = graph->graphArray[i].next;
        if (tmp == NULL)
            printf(" -> NULL");
        while (tmp != NULL) {
            printf(" -> (%d, %d, %d, %d)", tmp->wolf, tmp->sheep, tmp->cabbage, tmp->farmer);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void show_state(Node* state) {
    printf("Wolf: %s, Sheep: %s, Cabbage: %s, Farmer: %s\n",
        state->wolf ? "finish" : "start",
        state->sheep ? "finish" : "start",
        state->cabbage ? "finish" : "start",
        state->farmer ? "finish" : "start");
}

int compare_state(Node* state) {

    int value = state->wolf * 8 + state->sheep * 4 + state->cabbage * 2 + state->farmer;

    switch (value) {
    case 15: return 1;
    case 14:
    case 1:
    case 6:
    case 9:
    case 3:
    case 12: return 0;
    default: return -1;
    }
}



Node* generate_legal_moves(Graph* head, Node* state) {
    int index = state->wolf * 8 + state->sheep * 4 + state->cabbage * 2 + state->farmer;


    if (head->graphArray[index].state != 1) {
        head->graphArray[index].state = 1;
        show_state(&head->graphArray[index]);
        return &head->graphArray[index];
    }

    return state->next;
}

int deep_search_first(Graph* head, Node* start, int depth) {
    if (compare_state(start) > 0) {
        return 1;
    }
    if (!compare_state(start) && depth != 10) {
        return 0;
    }
    if (!depth) {
        return 0;
    }

    while (start != NULL) {


        start = generate_legal_moves(head, start);
        if (deep_search_first(head, start, depth - 1)) {
            return 1;
        }

        start = start->next;
    }


    return 0;
}


void free_Graph(Graph* head) {
    for (int i = 0; i < head->graphCapacity; i++) {
        Node* tmp = head->graphArray[i].next;
        while (tmp != NULL) {
            Node* delete = tmp;
            tmp = tmp->next;
            free(delete);
        }
    }

    free(head->graphArray);
    free(head);
}