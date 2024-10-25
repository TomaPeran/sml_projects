#include "hash.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define HCONST 3567892

HashTable *NewTable(int size)
{
	// kreira novu hash tablicu (alocira samu strukturu i niz pokazivaèa)
	
	// prkaticki stvara se pointer na listu pokazivaca, sveukupno *** 
	HashTable* dict = (HashTable*)malloc(sizeof(HashTable)); // nista drugo nego dummy head
	dict->size = size;
	dict->load = 0;
	dict->table = (Bin**)malloc(size * sizeof(Bin*)); // // dict->table => dinamicki alociran niz pokazivaca
	
	for (int i = 0; i < size; i++) { // za svaki skafetin triba alocirat memoriju
		dict->table[i] = (Bin*)malloc(sizeof(Bin)); // svaki pointer unutar niza je alociran
		dict->table[i]->word = NULL;
		dict->table[i]->next = NULL;
	}

	return dict;
}

unsigned int hash(char *word)
{
	// od kljuca generira hash kod
	unsigned int key = 0;
	while(*word != '\0')
	{
		key = key*HCONST + *word;
		word++;
	}
	return key;
}

void Insert(HashTable *ht, char *word)
{
	// dodaje novu rijec u listu na odgovarajucem pretincu


	/* ovaj dio je potreban kod linearnog rjesenja kolizije
	if (ht->load == ht->size) {
		printf("Tablica puna\n");
		return;
	}
	*/

	unsigned int key = hash(word);
	unsigned int b = key % ht->size;
	ht->load++;
	

	// dodaje u glavu odgovarajuceg skafetina
	Bin* new_element = (Bin*)malloc(sizeof(Bin));
	new_element->word = strdup(word);
	new_element->next = NULL;
	ht->table[b]->next = new_element;

}

int Get(HashTable *ht, char *word)
{

	// pogledat lako moguce da san falia
	// vraca 0 ili 1 ovisno o tome da li rijec postoji u tablici

	unsigned int key = hash(word); // vadi kljuc za pojedinu rijec, id u tablici
	unsigned int b = key % ht->size;
	
	//printf("key: %u\n", b);
	Bin* tmp = ht->table[b];
	//printf("tmp: %p\n", tmp);
	//return 0;
	while (tmp ->next != NULL) { // usli unutar skafetina, trazi se struktura
		if (!strcmp(tmp->next->word, word)) {
			return 1;
		}
		tmp = tmp->next;
	}
	

	return 0;
}

void DeleteTable(HashTable *ht)
{
	// brise cijelu hash tablicu (liste na svim pretincima (rijec i element liste), pretince ...)

	for (int i = 0; i < ht->size; i++) {
		Bin *tmp = ht->table[i];
		while (tmp != NULL) {
			Bin* obrisi = tmp;
			tmp = tmp->next;
			free(obrisi->word);
			free(obrisi);
		}
		free(tmp);
	}
	free(ht->table);
	free(ht);
}