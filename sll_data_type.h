#pragma once


//Opcija 1: Guma na skladistu

typedef struct sllist {
	int number; //ID
	int width; //sirina
	int height; //visina
	short diameter; //promjer
	char dot[5]; //godina proizvodnje
	char name[30]; //marka
	char rezerviranost[3]; //rezervirano (da,ne)
	char starost[10]; //nove ili rabljene
	char tip[15]; //zimske,ljetne,4 sezonske

	struct sllist* nextNode;
}SLLNODE;

//Opcija 2: Svi dosadasnje usluge

typedef struct sllist2 {
	int number;
	short day;
	short month;
	int year;
	short hour;
	short minute;
	char usluga[20];
	int cijena;


	struct sllist2* nextNode;
}SLLNODE2;

//Opcija 3: Troskovi

typedef struct sllist3 {
	int number;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	char trosak[20];
	int cijena;

	struct sllist3* nextNode;
}SLLNODE3;

//Opcija 4: Prihodi

typedef struct sllist4 {
	int number;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	char prihod[20];
	int cijena;

	struct sllist4* nextNode;
}SLLNODE4;



//Opcija 5: Termin

typedef struct sllist5 {
	int number;
	int day;
	int month;
	int year;
	int hour;
	int minute;
	char opis[20];

	struct sllist5* nextNode;
}SLLNODE5;