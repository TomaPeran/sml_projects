#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Stog_HelpFunctions.h"


int main() {
	srand((unsigned int)time(NULL));
	Element* Stog = NULL;

	add_randomPriority(Stog);


	free(Stog);
	return 0;
}