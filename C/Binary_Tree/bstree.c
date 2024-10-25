#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	BSTree newTree = (BSTree)malloc(sizeof(Node));
	newTree->word = NULL;
	newTree->left = NULL;
	newTree->right = NULL;

	return newTree;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se traži mjesto za novi èvor u stablu. Ako rijeè postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivaè. -> Pre-order?
	
	
	if (*bst == NULL || (*bst)->word == NULL) { 
		(*bst) = NewBSTree();
		(*bst)->word = strdup(word);
	}

	// strcmp(str1, str2); (< 0) -> str1 manji od str2; (> 0) -> str1 veci od str2;
	else if (strcmp((*bst)->word, word) > 0) {
		AddNode(&(*bst)->left, word);
	
	}
	else if (strcmp((*bst)->word, word) < 0) {
		AddNode(&(*bst)->right, word);
	
	}

	return;
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se pronašla najduža grana (visina stabla).
	if (bst == NULL)
		return 0;

	int m = BSTHeight(bst->left) + 1;
	int n = BSTHeight(bst->right) + 1;

	return (m < n) ? n : m;
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rijeèi u stablu na ekran po abecednom redu.
	// In-order šetnja po stablu (lijevo dijete, èvor, desno dijete)
	
	if (bst != NULL) {
		PrintBSTree(bst->left);
		printf("%s\n", bst->word);
		PrintBSTree(bst->right);
	}

}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rijeè po rijeè iz stabla u tekstualnu datoteku. Rijeèi su odvojene razmakom.
	// Pre-order šetnja po stablu (trenutni èvor pa djeca)
	// 	
	if (bst == NULL)
		return;

	SaveBSTree(bst->left, fd);
	fprintf(fd, "%s\n", bst->word);
	SaveBSTree(bst->right, fd);


	/*
	while (bst == NULL) {
		SaveBSTree(bst->left, fd);
		fprintf(fd, "%s \n", bst->word);
		SaveBSTree(bst->right, fd);
	}
	*/
}

void DeleteBSTree(BSTree bst)
{
	// Briše stablo (string word i sam èvor) iz memorije.
	// Post-order šetnja po stablu (prvo djeca pa trenutni èvor)
	if (bst == NULL)
		return;
	
	if (bst->left == NULL && bst->right == NULL) {
		free(bst->word);
		free(bst);
		return NULL;
	}
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	return;
	
	/*
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	free(bst->word);
	free(bst);
	*/

	//PrintBSTree(bst);

}

BSTree LoadBSTree(FILE *fd)
{
	// Uèitava rijeè po rijeè iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijeè duplicirati sa strdup().
	char buffer[1024];
	BSTree bst;

	bst = NewBSTree(); // nadodano

	while (1) {
		if (fscanf(fd, "%s", buffer) == EOF) {
			return bst;
		}

		buffer[strlen(buffer)] = '\0';
		AddNode(&bst, strdup(buffer));
	}
}
