#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct lista
{
	int vrijednost;
	struct lista* next;
} lista;


void dodajSort(lista* head, int broj) {
	lista* radni = head->next;
	lista* pred = head;
	lista* temp = malloc(sizeof(lista));
	temp->vrijednost = broj;
	while (radni != NULL) {
		if ((radni->vrijednost) >= broj) {
			temp->next = radni;
			pred->next = temp;
			return;
		}
		radni = radni->next;
		pred = pred->next;
	}

	pred->next = temp;
	temp->next = NULL;
	return;
}

void readF(lista* head, const char* filename) {
	int eksp;
	FILE* p;
	p = fopen(filename, "r+");
	if (p == NULL)
		printf("NIJE OTVORIJA P FILE");
	while (fscanf(p, "%d ", &eksp) == 1) {
		dodajSort(head, eksp);
	}
	fclose(p);


	return;
}


void ispisLIste(lista* head) {
	printf("Lista \n");
	while (head->next != NULL) {
		head = head->next;
		printf("\t%d\n", head->vrijednost);
	}
	printf("\n");
	return;
}

void unosUnije(lista* glavni, lista* slabiji) {
	while (slabiji->next != NULL) {
		slabiji = slabiji->next;
		dodajSort(glavni, slabiji->vrijednost);
	}
	return;
}

void unija(lista*glavni,lista*prvi,lista*drugi) {
	unosUnije(glavni, prvi);
	unosUnije(glavni, drugi);
	return;
}


void presjek(lista* glavni, lista* prvi, lista* drugi) {
	prvi = prvi->next;
	drugi = drugi->next;
	while (prvi->next!=NULL && drugi->next!=NULL) {
		if (prvi->vrijednost == drugi->vrijednost) {
			dodajSort(glavni, prvi->vrijednost);
			prvi = prvi->next;
			drugi = drugi->next;
		}
		else if ((prvi->vrijednost) > (drugi->vrijednost)) {
			drugi = drugi->next;
		}
		else if ((prvi->vrijednost) < (drugi->vrijednost)) {
			prvi = prvi->next;
		}
	}

	return;
}

void main(void) {
	lista* p_head = malloc(sizeof(lista));
	p_head->next = NULL;
	lista* n_head = malloc(sizeof(lista));
	n_head->next = NULL;
	lista* Q_head = malloc(sizeof(lista));
	Q_head->next = NULL;
	lista* Z_head = malloc(sizeof(lista));
	Z_head->next = NULL;
	readF(p_head, "p.txt");
	readF(n_head, "n.txt");
	unija(Q_head,p_head,n_head);
	presjek(Z_head, n_head, p_head);


	ispisLIste(p_head);
	ispisLIste(n_head);
	ispisLIste(Q_head);
	ispisLIste(Z_head);

	return 0;
}