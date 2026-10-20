#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba* pozicija;

typedef struct osoba {
	char ime[50];
	char prezime[50];
	int godinaRod;
	pozicija next;
}Osoba;

int IspisListe(Osoba* head) {
	head = head->next;
	while (head != NULL) {
		printf("\nime:%s  \nPrezime:%s \nDatum rodenja:%d",head->ime,head->prezime,head->godinaRod);
		head = head->next;
	}
	return 0;
}


int DodajPocetak(Osoba* head, char * ime, char * prezime, int gRodjs) {
	Osoba *p = malloc(sizeof(Osoba));
	p->next = head->next;
	head->next = p;
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godinaRod = gRodjs;

	return 0;
}


int DodajKraj(Osoba* head, char* ime, char* prezime, int gRodjs) {

	while (head->next != NULL) {
		head = head->next;
	}
	Osoba* p = malloc(sizeof(Osoba));
	p->next = NULL;
	head->next = p;
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godinaRod = gRodjs;

	return 0;
}



void main() {
	Osoba* head = malloc(sizeof(Osoba));
	head->next = NULL;
	DodajPocetak(head, "ante", "juric",2005 );
	DodajPocetak(head, "jure", "antic", 2006);
	IspisListe(head);
	DodajKraj(head, "stipe", "klaric", 2004);
	IspisListe(head);
}