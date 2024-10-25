#ifndef STOG_HELPFUNCTIONS_HPP
#define STOG_HELPFUNCTIONS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int priority;
	void* data;
}Element;


void print_Tree(Element* stog);

Element* delete_HelpFunction(Element* stog, int r);

void iterativeDelete_HelpFunction(Element** stog, int r);

void delete_Element(Element* stog);

Element* parent_childConnection(Element* stog, int c);

void iterativeParent_childConnection(Element** stog, int c);

void add_randomPriority(Element* stog);



#endif