#include "BFS_Header.h"

#define MAX_CAPACITY 100

Graph* dummy_Graph() {
	Graph* head = (Graph*)malloc(sizeof(Graph));
	head->graphCapacity = 16;
	head->graphArray = (Node*)malloc(sizeof(Node) * head->graphCapacity);

	return head;
}

void set_Main_Part(Graph* graph) {
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
		graph->graphArray[i].parentIndex = 0;
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
	set_Main_Part(graph);

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

void displayGraph(Graph* graph) {
	for (int i = 0; i < graph->graphCapacity; ++i) {
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

void show_State(Node* state) {
	printf("Wolf: %s, Sheep: %s, Cabbage: %s, Farmer: %s\n",
		state->wolf ? "Finish" : "Start",
		state->sheep ? "Finish" : "Start",
		state->cabbage ? "Finish" : "Start",
		state->farmer ? "Finish" : "Start");
}

Queue* dummy_Queue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));

	queue->capacity = 0;
	queue->head = 0;
	queue->tail = 0;
	queue->array = NULL;

	return queue;
}

void enque(Queue* queue, Node* gameState) {

	queue->capacity++;

	queue->array[queue->tail].wolf = gameState->wolf;
	queue->array[queue->tail].sheep = gameState->sheep;
	queue->array[queue->tail].cabbage = gameState->cabbage;
	queue->array[queue->tail].farmer = gameState->farmer;

	queue->array[queue->tail].state = gameState->state;
	queue->array[queue->tail].parentIndex = gameState->parentIndex;
	queue->array[queue->tail].next = gameState->next;


	if ((queue->tail + 1) == MAX_CAPACITY)
		queue->tail = 0;
	else
		queue->tail++;
}

int state_Value(Node* gameState) {
	return (gameState->wolf * 8 + gameState->sheep * 4 + gameState->cabbage * 2 + gameState->farmer);
}

int dequeue(Queue* queue) {
	queue->capacity--;

	int index = queue->head;
	if ((queue->head + 1) == MAX_CAPACITY)
		queue->head = 0;
	else
		queue->head++;

	return queue->array[index].wolf * 8 + queue->array[index].sheep * 4 + queue->array[index].cabbage * 2 + queue->array[index].farmer;
}

void print_Queue(Queue* queue, int flag) {
	int currentIndex = queue->head - 1;

	while (currentIndex >= 0) {
		show_State(&queue->array[currentIndex]);
		currentIndex = queue->array[currentIndex].parentIndex;
	}
}

void BreadthFirstGraph(Graph* graph, Queue* queue) {

	queue->array = (Node*)malloc(sizeof(Node) * MAX_CAPACITY);

	graph->graphArray[0].state = 1;
	graph->graphArray[0].parentIndex = -123;

	enque(queue, &graph->graphArray[0]);

	for (int i = 0; queue->capacity; i++) {

		int currentIndex = dequeue(queue);
		Node* newNode = graph->graphArray[currentIndex].next;

		while (newNode != NULL) {
			if (newNode->state == 0) {
				newNode->state = 1;
				newNode->parentIndex = i;
				enque(queue, newNode);

			}
			newNode = newNode->next;
		}


	}

	print_Queue(queue, 0);
}

void free_Graph(Graph* graph) {

	for (int i = 0; i < graph->graphCapacity; i++) {
		Node* tmp = graph->graphArray[i].next;
		while (tmp != NULL) {
			Node* delete = tmp;
			tmp = tmp->next;
			free(delete);
		}
	}

	free(graph->graphArray);
	free(graph);
}

void free_Queue(Queue* queue) {
	free(queue->array);
	free(queue);
}