#ifndef HASH_H
#define HASH_H

typedef struct Bin { // struktura unutar "ladice" (skafetina)
	char *word; // rijec
	struct Bin *next; // pointer na iduci element te liste (u skafetinu)
} Bin;

typedef struct {
	Bin **table; // niz pokazivaca
	int size, load; // fizicka i logicka velicina
} HashTable;

HashTable *NewTable(int size);

unsigned int hash(char *word);

void Insert(HashTable *ht, char *word);

int Get(HashTable *ht, char *word);

void DeleteTable(HashTable *ht);

#endif