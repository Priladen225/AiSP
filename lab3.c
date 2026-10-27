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


int trazi(Osoba* head, char* prezime) {
	int counter = 1;
	head = head->next;
	while (strcmp(prezime, head->prezime) != 0) {
		head = head->next;
		counter += 1;
	}
	//printf("\n osoba %s je na %d mjestu u listi", prezime, counter);
	return counter;
}

int brisanje(Osoba* head, char* prezime) {
	Osoba* temp;
	temp = head->next;
	while (strcmp(prezime, head->next->prezime) != 0) {
		head = head->next;
	}
	temp = head->next;
	head->next = temp->next;
	free(temp);
	return 0;
}

int IspisListe(Osoba* head) {
	head = head->next;
	while (head != NULL) {
		printf("\nime:%s  \nPrezime:%s \nDatum rodenja:%d", head->ime, head->prezime, head->godinaRod);
		head = head->next;
	}
	return 0;
}


int DodajPocetak(Osoba* head, char* ime, char* prezime, int gRodjs) {
	Osoba* p = malloc(sizeof(Osoba));
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

int dodajIza(Osoba* head,char* anchor, char* ime, char* prezime, int gRodjs) {
	int redniBR;
	Osoba* p = malloc(sizeof(Osoba));
	redniBR=trazi(head, anchor);
	for (int i=0;i < redniBR; i++) {
		head = head->next;
	}
	p->next=head->next;
	head->next = p;
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godinaRod = gRodjs;
	return 0;
}

int dodajIspred(Osoba* head, char* anchor, char* ime, char* prezime, int gRodjs) {
	int redniBR;
	Osoba* p = malloc(sizeof(Osoba));
	redniBR = trazi(head, anchor);
	for (int i = 0;i < redniBR-1; i++) {
		head = head->next;
	}
	p->next = head->next;
	head->next = p;
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godinaRod = gRodjs;
	return 0;
}

void SortPrez(Osoba *P){
	Osoba *j, *prev_j, *temp,*end;

	end = NULL;
	while (P->next != end) {
		prev_j = P;
		j = P->next;

		while (j->next != end) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}

			prev_j = j;
			j = j->next;
		}
		end = j;
	}
}

int IspisDat(Osoba* head) {
	FILE *p;
	p = fopen("test.txt", "w+");
	while (head->next != NULL) {
		head = head->next;
		fprintf(p, "%s %s %d \n", head->ime, head->prezime, head->godinaRod);
	}
	fclose(p);
	return 0;
}

int UpisDat(Osoba* head) {
	FILE* p;
	char ime[50], prezime[50];
	int godinaRod;
	p = fopen("test.txt", "r");
	while (!feof(p)) {
		fscanf(p, "%s %s %d", ime, prezime, &godinaRod);
		printf("%s %s %d\n", ime, prezime, godinaRod);
		DodajKraj(head, ime, prezime, godinaRod);
	}
	fclose(p);
	return 0;
}




void main() {
	Osoba* head = malloc(sizeof(Osoba));
	head->next = NULL;
	DodajPocetak(head, "ante", "juric", 2005);
	DodajPocetak(head, "jure", "antic", 2006);
	DodajKraj(head, "stipe", "klaric", 2004);
	dodajIza(head, "juric", "klara", "ivic", 2003);
	dodajIspred(head, "klaric", "bruno", "karlic", 2003);
	SortPrez(head);
	IspisListe(head);
	/*IspisListe(head);
	IspisDat(head);
	UpisDat(head);
	IspisListe(head);*/
}
