#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Stog_HelpFunctions.h"

#define MAX_LENGTH 10 // 10 000
#define RANDOM (rand() * rand())


/*
	int p = (i - 1) / 2;
	int lc = (i * 2) + 1;
	int rc = (i * 2) + 2;
*/


void print_Tree(Element* stog) {
	for (int i = 0; i < MAX_LENGTH; i++) {
		printf("%d ", stog[i].priority);
	}
	printf("\n");
}

Element* delete_HelpFunction(Element* stog, int r) {
	int lc = (2 * r) + 1;
	int rc = (2 * r) + 2;

	if (lc > MAX_LENGTH) {
		lc = 0;
	}
	if (rc > MAX_LENGTH) {
		rc = 0;
	}

	if (stog[r].priority < stog[rc].priority || stog[r].priority < stog[lc].priority) {
		int m = (rc > lc) ? rc : lc;
		int temp = stog[r].priority;
		stog[r].priority = stog[m].priority;
		stog[m].priority = temp;
		delete_HelpFunction(stog, m);
	}

	return NULL;
}

void iterativeDelete_HelpFunction(Element** stog, int r) {
	do {
		int lc = (2 * r) + 1;
		int rc = (2 * r) + 2;

		if (lc > MAX_LENGTH) {
			lc = 0;
		}
		if (rc > MAX_LENGTH) {
			rc = 0;
		}

		if ((*stog + r)->priority < (*stog + lc)->priority || (*stog + r)->priority < (*stog + rc)->priority) {
			int m = (rc > lc) ? rc : lc;
			int temp = (*stog + r)->priority;
			(*stog + r)->priority = (*stog + m)->priority;
			(*stog + m)->priority = temp;
			delete_HelpFunction(stog, m);
		}
	} while (r > MAX_LENGTH);
}

void delete_Element(Element* stog) {
	for (int i = MAX_LENGTH - 1; i >= 0; i--) {
		stog[0].priority = stog[i].priority;
		iterativeDelete_HelpFunction(&stog, ((i - 1) / 2));
		//delete_HelpFunction(stog, ((i - 1) / 2));  // rekurzija
		stog[i].priority = 0;
	}

	print_Tree(stog);
}

Element* parent_childConnection(Element* stog, int c) {
	int r = (c - 1) / 2;

	if (stog[r].priority < stog[c].priority) {
		int temp = stog[r].priority;
		stog[r].priority = stog[c].priority;
		stog[c].priority = temp;
		parent_childConnection(stog, r);
	}


	return NULL;
}

//	(*stog + r)->priority
void iterativeParent_childConnection(Element** stog, int c) {
	int r = (c - 1) / 2;
	int flag = 0;

	do {
		if ((*stog + r)->priority < (*stog + c)->priority) {

			int temp = (*stog + r)->priority;
			(*stog + r)->priority = (*stog + c)->priority;
			(*stog + c)->priority = temp;
			c = r;

		}
		if (r == 0)
			flag++;

		r = (r - 1) / 2;

	} while (flag < 1);

}

void add_randomPriority(Element* stog) {
	stog = (Element*)malloc(MAX_LENGTH * sizeof(Element));

	for (int i = 0; i < MAX_LENGTH; i++) {
		stog[i].priority = RANDOM % MAX_LENGTH + 1;
		iterativeParent_childConnection(&stog, i); // iteracija
		//parent_childConnection(stog, i); // rekurzija

	}

	print_Tree(stog);

	delete_Element(stog);
}

