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

void Dodaj_sort(polinom* head, int eksp,int koef) {
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
	return;
}

void readpolyP(polinom *head) {
	int eksp,koef;
	FILE* p;
	p = fopen("p.txt", "r+");
	if (p == NULL)
		printf("NIJE OTVORIJA P FILE");
	while (fscanf(p, "%d %d", &eksp, &koef) == 2) {
		Dodaj_sort(head, eksp, koef);
	}
	fclose(p);
	return ;
}
void readpolyN(polinom* head) {
	int eksp, koef;
	FILE* p;
	p = fopen("n.txt", "r+");
	if (p == NULL)
		printf("NIJE OTVORIA N FILE");
	while (fscanf(p, "%d %d", &eksp, &koef) == 2) {
		Dodaj_sort(head, eksp, koef);
	}
	fclose(p);
	return;
}

void ispisListe(polinom* head) {
	static int counter = 0;
	counter++;
	switch (counter) {
	case 1:
		printf("Prvi polinom ");
		break;
	case 2:
		printf("Drugi polinom ");
		break;
	case 3:
		printf("Zbroj polinoma ");
		break;
	case 4:
		printf("Umnozak Polinoma ");
		break;
	}
	head = head->next;
	if (head->koef == 1)
		printf("je: x^%d", head->eksp);
	else if(head->koef==-1)
		printf("je: -x^%d", head->eksp);
	else
	printf("je:\n%dx^%d", head->koef, head->eksp);
	while (head->next != NULL) {
		head = head->next;
		
		if (head->eksp == 0) {
			printf("+%d", head->koef);
			continue;
		}
		if (head->koef > 0) {
			if (head->koef == 1)
				printf("+x^%d", head->eksp);
			else
				printf("+%dx^%d", head->koef, head->eksp);
		}
		else if (head->koef == -1)
			printf("-x^%d", head->eksp);
		else
			printf("%dx^%d", head->koef, head->eksp);;
	}
	printf("\n");
	return 0;
}

void ZbrojPolinoma(polinom*Z,polinom*p) {
	while (p->next != NULL) {
		p = p->next;
		Dodaj_sort(Z, p->eksp, p->koef);
	}
	return;
}

void MnozenjePolinoma(polinom* M,polinom*p,polinom*n) {
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
	return;
}

void main(void) {
	polinom* P_head = malloc(sizeof(polinom));
	P_head->next = NULL;
	polinom* N_head = malloc(sizeof(polinom));
	N_head->next = NULL;
	polinom* Z_head = malloc(sizeof(polinom));
	Z_head->next = NULL;
	polinom* Q_head = malloc(sizeof(polinom));
	Q_head->next = NULL;
	readpolyP(P_head);
	readpolyN(N_head);
	ispisListe(P_head);
	ispisListe(N_head);
	ZbrojPolinoma(Z_head, P_head);
	ZbrojPolinoma(Z_head, N_head);
	ispisListe(Z_head);
	MnozenjePolinoma(Q_head, P_head, N_head);
	ispisListe(Q_head);
	return 0;
}
