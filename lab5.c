#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct lista
{
	int vrijednost;
	struct lista* next;
} lista;


int dodajSort(lista* head, int broj) {
	lista* radni = head->next;
	lista* pred = head;
	lista* temp = malloc(sizeof(lista));
	if (!temp) {
		printf("Prostor nije alociran");
		return 1;
	}
	temp->vrijednost = broj;
	while (radni != NULL) {
		if ((radni->vrijednost) > broj) {
			temp->next = radni;
			pred->next = temp;
			return;
		}
		else if (radni->vrijednost == broj) {
			free(temp);
			return;
		}
		radni = radni->next;
		pred = pred->next;
	}

	pred->next = temp;
	temp->next = NULL;
	return 0;
}

int readF(lista* head, const char* filename) {
	int eksp;
	FILE* p;
	p = fopen(filename, "r+");
	if (p == NULL) {
		printf("NIJE OTVORIJA P FILE");
		return 1;
	}
	while (fscanf(p, "%d ", &eksp) == 1) {
		dodajSort(head, eksp);
	}
	fclose(p);


	return 0;
}


int ispisLIste(lista* head) {
	printf("Lista \n");
	while (head->next != NULL) {
		head = head->next;
		printf("\t%d\n", head->vrijednost);
	}
	printf("\n");
	return 0;
}

int unosUnije(lista* glavni, lista* slabiji) {
	while (slabiji->next != NULL) {
		slabiji = slabiji->next;
		dodajSort(glavni, slabiji->vrijednost);
	}
	return 0;
}

int unija(lista* glavni, lista* prvi, lista* drugi) {
	unosUnije(glavni, prvi);
	unosUnije(glavni, drugi);
	return 0;
}


int presjek(lista* glavni, lista* prvi, lista* drugi) {
	prvi = prvi->next;
	drugi = drugi->next;
	while (prvi != NULL && drugi != NULL) {
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

	return 0;
}

int main() {
	lista* p_head = malloc(sizeof(lista));
	if (!p_head) {
		printf("Prostor nije alociran");
		return 1;
	}
	p_head->next = NULL;
	lista* n_head = malloc(sizeof(lista));
	if (!n_head) {
		printf("Prostor nije alociran");
		return 1;
	}
	n_head->next = NULL;
	lista* Q_head = malloc(sizeof(lista));
	if (!Q_head) {
		printf("Prostor nije alociran");
		return 1;
	}
	Q_head->next = NULL;
	lista* Z_head = malloc(sizeof(lista));
	if (!Z_head) {
		printf("Prostor nije alociran");
		return 1;
	}
	Z_head->next = NULL;
	if ((readF(p_head, "p.txt")) == -1) {
		return 1;
	}
	if ((readF(n_head, "n.txt")) == -1) {
		return 1;
	}
	unija(Q_head, p_head, n_head);
	presjek(Z_head, n_head, p_head);


	ispisLIste(p_head);
	ispisLIste(n_head);
	ispisLIste(Q_head);
	ispisLIste(Z_head);

	return 0;
}
