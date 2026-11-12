#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct polinom;
typedef struct polinom * pozicija;
struct polinom
{
	int koef, eksp;
	pozicija next;
};
typedef struct polinom polinom;

int Dodaj_sort(polinom* head, int eksp,int koef) {
	polinom *radni=head->next;
	polinom* pred = head;
	polinom* temp=malloc(sizeof(polinom));
	temp->eksp = eksp;
	temp->koef = koef;
	while (radni != NULL) {
		if ((radni->eksp) < eksp) {
			temp->next = radni;
			pred->next = temp;
			return;
		}
		else if ((radni->eksp) == eksp) {
			radni->koef = (radni->koef) + koef;
			if (radni->koef == 0) {
				pred->next = radni->next;
				free(radni);
			}
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

int readpolyP(polinom *head) {
	int eksp,koef;
	FILE* p;
	p = fopen("p.txt", "r+");
	if (p == NULL) {
		printf("NIJE OTVORIJA P FILE");
		return 1;
	}
	while (fscanf(p, "%d %d", &eksp, &koef) == 2) {
		Dodaj_sort(head, eksp, koef);
	}
	fclose(p);
	return 0;
}
int readpolyN(polinom* head) {
	int eksp, koef;
	FILE* p;
	p = fopen("n.txt", "r+");
	if (p == NULL){
		printf("NIJE OTVORIA N FILE");
		return 1;
}
	while (fscanf(p, "%d %d", &eksp, &koef) == 2) {
		Dodaj_sort(head, eksp, koef);
	}
	fclose(p);
	return 0;
}

void ispisListe(polinom* head) {
	static int counter = 0;
	int prvi = 1;
	counter++;
	switch (counter) {
	case 1:
		printf("Prvi polinom je: ");
		break;
	case 2:
		printf("Drugi polinom je: ");
		break;
	case 3:
		printf("Zbroj polinoma je: ");
		break;
	case 4:
		printf("Umnozak polinoma je: ");
		break;
	}
	head = head->next;
	if (head == NULL) {
		printf("0\n");
		return;
	}
	while (head != NULL) {
		int k = head->koef;
		int e = head->eksp;
		int a = (k < 0) ? -k : k;

		if (k < 0)
			printf("-");
		else if (!prvi)
			printf("+");

		if (e == 0) {
			printf("%d", a);
		}
		else {
			if (a != 1)
				printf("%d", a);
			if (e == 1)
				printf("x");
			else
				printf("x^%d", e);
		}
		prvi = 0;
		head = head->next;
	}
	printf("\n");
}

int ZbrojPolinoma(polinom*Z,polinom*p) {
	while (p->next != NULL) {
		p = p->next;
		Dodaj_sort(Z, p->eksp, p->koef);
	}
	return 0;
}

int MnozenjePolinoma(polinom* M,polinom*p,polinom*n) {
	int eksp=0;
	int koef=0;
	p = p->next;
	n = n->next;
	polinom* temp = n;
	while (p != NULL) {
		while (n != NULL) {
			eksp = p->eksp + n->eksp;
			koef = p->koef * n->koef;
			Dodaj_sort(M, eksp, koef);
			n = n->next;
		}
		n=temp;
		p = p->next;
	}
	return 0;
}

int oslobodiListu(polinom* head) {
	polinom* trenutni = head;
	polinom* sljedeci;
	while (trenutni != NULL) {
		sljedeci = trenutni->next;
		free(trenutni);
		trenutni = sljedeci;
	}

	return 0;
}

int provjera(polinom*head) {
	if (!head) {
		printf("prostor nije alociran");
		return 1;
	}
	return 0;
}


int main(void) {
	polinom* P_head = malloc(sizeof(polinom));
	if (provjera(P_head)) {
		return 1;
	}
	P_head->next = NULL;
	polinom* N_head = malloc(sizeof(polinom));
	if (provjera(P_head)) {
		return 1;
	}
	N_head->next = NULL;
	polinom* Z_head = malloc(sizeof(polinom));
	if (provjera(P_head)) {
		return 1;
	}
	Z_head->next = NULL;
	polinom* Q_head = malloc(sizeof(polinom));
	if (provjera(P_head)) {
		return 1;
	}
	Q_head->next = NULL;
	readpolyP(P_head);
	readpolyN(N_head);
	ZbrojPolinoma(Z_head, P_head);
	ZbrojPolinoma(Z_head, N_head);
	MnozenjePolinoma(Q_head, P_head, N_head);


	ispisListe(P_head);
	ispisListe(N_head);
	ispisListe(Z_head);
	ispisListe(Q_head);

	oslobodiListu(P_head);
	oslobodiListu(N_head);
	oslobodiListu(Z_head);
	oslobodiListu(Q_head);

	return 0;
}
