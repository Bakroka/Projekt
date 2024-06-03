/*
Program omogucuje pregledavanje i ažuriranje trenutno dostupnih guma na skladištu,
bez obzira jesu li nove ili rabljene, te prikazuje njihovu dostupnost ili rezerviranost.
Omogucuje unos, ažuriranje i pregled podataka o popravcima, montaži, balansiranju i drugim uslugama te
troškovima poboljšanja rada, kao što su alati, dizalice, narudžbe guma, službeni automobil i drugo.
Program takoder omogucuje zakazivanje termina te njihovo izmjenu i brisanje.
Generira izvještaje o svim popravcima i montažama za svaki mjesec te izracunava dobit ili gubitak po mjesecu.


*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "sll_data_type.h"

//Opcija 1: Guma na skladistu
SLLNODE* head = NULL;
SLLNODE* tail = NULL;
SLLNODE* list = NULL;
SLLNODE* current = NULL;
int currentNumber = 0;

//Opcija 2: Svi dosadasnje usluge
SLLNODE2* head2 = NULL;
SLLNODE2* tail2 = NULL;
SLLNODE2* list2 = NULL;
SLLNODE2* current2 = NULL;
int currentNumber2 = 0;

//Opcija 3: Troskovi
SLLNODE3* head3 = NULL;
SLLNODE3* tail3 = NULL;
SLLNODE3* list3 = NULL;
SLLNODE3* current3 = NULL;
int currentNumber3 = 0;

//Opcija 4: Prihodi
SLLNODE4* head4 = NULL;
SLLNODE4* tail4 = NULL;
SLLNODE4* list4 = NULL;
SLLNODE4* current4 = NULL;
int currentNumber4 = 0;

//Opcija 5: Termin
SLLNODE5* head5 = NULL;
SLLNODE5* tail5 = NULL;
SLLNODE5* list5 = NULL;
SLLNODE5* current5 = NULL;
int currentNumber5 = 0;



int updateNumber;
int deleteNumber;
char choice;

int c = 0;

char odabir = '0';

char sporedni = '0';
char uvjet = '1';

int izbornik(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)
{
	printf("============================\
======  GLAVNI  =================================\n");
	printf("===================  ");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("  ==================\n");
	printf("\t\t\tOpcija 1: Dodavanje!\n");
	printf("\t\t\tOpcija 2: Izmjena!\n");
	printf("\t\t\tOpcija 3: Brisanje!\n");
	printf("\t\t\tOpcija 4: Ispisivanje!\n");
	printf("\t\t\tOpcija 5: Sortiranje!\n");
	printf("\t\t\tOpcija 6: Pretrazivanje!\n");
	printf("\t\t\tOpcija 0: Izlaz iz programa!\n");
	printf("=======================================\
======================================\n");

	scanf("%c", &uvjet);	
	while ((c = getchar()) != '\n' && c != EOF);

	switch (uvjet) 
	{
	case '1':
		//Dodavanje


		sporedni = '1';
		
		while (sporedni)
		{			
			sporedni = izbornik1(skladiste,usluge,prihodi,troskovi,termini);
			
		}

		break;

	case '2':
		//Izmjena
		
		sporedni = '1';

		while (sporedni)
		{
			sporedni = izbornik2(skladiste, usluge, troskovi, prihodi, termini);
		}
		
		break;
	case '3':
		//Brisanje
		
		sporedni = '1';

		while (sporedni)
		{
			sporedni = izbornik3(skladiste, usluge, troskovi, prihodi, termini);
		}


		break;
	case '4':

		//Ispisivanje

		sporedni = '1';

		while (sporedni)
		{
			sporedni = izbornik4(skladiste, usluge, troskovi, prihodi, termini);
		}


		break;
	case '5':
		//Sortiranje
		
		sporedni = '1';

		while (sporedni)
		{
			sporedni = izbornik5(skladiste, usluge, troskovi, prihodi, termini);
		}


		break;
	case '6':
		
		//Pretrazivanje

		sporedni = '1';

		while (sporedni)
		{
			sporedni = izbornik6(skladiste, usluge, troskovi, prihodi, termini);
		}


		break;
	case '0':
		//Izlaz

		uvjet = izlazIzPrograma(list,list2,list3,list4,list5);

		if (uvjet == '0')
		{
			return 0;
		}

		break;
	default:
		printf("Pogresan odabir\n");
		uvjet = '0';
	}

	system("cls");
	return uvjet;
}






int izbornik1(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)
{
	printf("============================\
====  DODAVANJE  ================================\n");
	printf("===================  ");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("  ==================\n");
	printf("\t\t\tOpcija 1: Guma na skladistu!\n");
	printf("\t\t\tOpcija 2: Sve dosadasnje usluge!\n"); 
	printf("\t\t\tOpcija 3: Troskovi!\n");
	printf("\t\t\tOpcija 4: Prihodi!\n");
	printf("\t\t\tOpcija 5: Termini!\n");
	printf("\t\t\tOpcija 0: Vracanje u glavni izbornik!\n");
	printf("=======================================\
======================================\n");

	sporedni = '0';
	scanf("%c", &sporedni);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (sporedni)
	{
	case '1':
		//Skladiste

		head = NULL;
		tail = NULL;
		currentNumber = 0;
		currentNumber = getLastNumberFromFile(skladiste) + 1;
		
		do {
			insertNewNodeSLList(&head, &tail, &currentNumber);

			printf("Do you want to add another node? (y/n): ");
			scanf(" %c", &choice);
			getchar(); 
		} while (choice == 'y' || choice == 'Y');

		// Write the list to a binary file
		writeListToBinaryFile(skladiste, head);
		

		break;
	case '2':
		//Usluge

		head2 = NULL;
		tail2 = NULL;
		currentNumber2 = 0;
		currentNumber2 = getLastNumberFromFile2(usluge) + 1;

		do {
			insertNewNodeSLList2(&head2, &tail2, &currentNumber2);

			printf("Do you want to add another node? (y/n): ");
			scanf(" %c", &choice);
			getchar(); 
		} while (choice == 'y' || choice == 'Y');

		// Write the list to a binary file
		writeListToBinaryFile2(usluge, head2);


		break;
	case '3':

		//Troskovi

		head3 = NULL;
		tail3 = NULL;
		currentNumber3 = 0;
		currentNumber3 = getLastNumberFromFile3(troskovi) + 1;

		do {
			insertNewNodeSLList3(&head3, &tail3, &currentNumber3);

			printf("Do you want to add another node? (y/n): ");
			scanf(" %c", &choice);
			getchar(); 
		} while (choice == 'y' || choice == 'Y');

		// Write the list to a binary file
		writeListToBinaryFile3(troskovi, head3);



		break;
	case '4':


		head4 = NULL;
		tail4 = NULL;
		currentNumber4 = 0;
		currentNumber4 = getLastNumberFromFile4(prihodi) + 1;

		do {
			insertNewNodeSLList4(&head4, &tail4, &currentNumber4);

			printf("Do you want to add another node? (y/n): ");
			scanf(" %c", &choice);
			getchar();  
		} while (choice == 'y' || choice == 'Y');

		// Write the list to a binary file
		writeListToBinaryFile4(prihodi, head4);
		

		break;
	case '5':

		head5 = NULL;
		tail5 = NULL;
		currentNumber5 = 0;
		currentNumber5 = getLastNumberFromFile5(termini) + 1;

		do {
			insertNewNodeSLList5(&head5, &tail5, &currentNumber5);

			printf("Do you want to add another node? (y/n): ");
			scanf(" %c", &choice);
			getchar();  
		} while (choice == 'y' || choice == 'Y');

		// Write the list to a binary file
		writeListToBinaryFile5(termini, head5);

		
		break;
	case '0':

		return 0;

		break;
	default:
		printf("Pogresan odabir\n");
		sporedni = '0';
	}


	return sporedni;
}

int izbornik2(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)

{
	printf("============================\
=====  IZMJENA  =================================\n");
	printf("===================  ");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("  ==================\n");
	printf("\t\t\tOpcija 1: Guma na skladistu!\n");
	printf("\t\t\tOpcija 2: Sve dosadasnje usluge!\n"); 
	printf("\t\t\tOpcija 3: Troskovi!\n");
	printf("\t\t\tOpcija 4: Prihodi!\n");
	printf("\t\t\tOpcija 5: Termini!\n");
	printf("\t\t\tOpcija 0: Vracanje u glavni izbornik!\n");
	printf("=======================================\
======================================\n");

	sporedni = '0';
	scanf("%c", &sporedni);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (sporedni)
	{
	case '1':

		//Skladiste

		list = NULL;
		// Read the list from the binary file
		list = readListFromBinaryFile(skladiste);
		if (list == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		printf("Enter the number of the node to update: ");
		updateNumber = safeIntInputAll();
		updateNodeByNumber(list, updateNumber);

		// Print the list after deletion
		printf("List after update\n");
		printList(list);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted(skladiste, list);



		break;
	case '2':

		//Usluge

		list2 = NULL;
		// Read the list from the binary file
		list2 = readListFromBinaryFile2(usluge);
		if (list2 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		printf("Enter the number of the node to update: ");
		updateNumber = safeIntInputAll();
		updateNodeByNumber2(list2, updateNumber);

		// Print the list after deletion
		printf("List after update\n");
		printList2(list2);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted2(usluge, list2);



		break;
	case '3':

		//Troskovi

		list3 = NULL;
		// Read the list from the binary file
		list3 = readListFromBinaryFile3(troskovi);
		if (list3 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		printf("Enter the number of the node to update: ");
		updateNumber = safeIntInputAll();
		updateNodeByNumber3(list3, updateNumber);

		// Print the list after deletion
		printf("List after update\n");
		printList3(list3);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted3(troskovi, list3);




		break;
	case '4':

		//Prihodi


		list4 = NULL;
		// Read the list from the binary file
		list4 = readListFromBinaryFile4(prihodi);
		if (list4 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		printf("Enter the number of the node to update: ");
		updateNumber = safeIntInputAll();
		updateNodeByNumber4(list4, updateNumber);

		// Print the list after deletion
		printf("List after update\n");
		printList4(list4);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted4(prihodi, list4);


		break;
	case '5':

		//Termini

		list5 = NULL;
		// Read the list from the binary file
		list5 = readListFromBinaryFile5(termini);
		if (list5 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		printf("Enter the number of the node to update: ");
		updateNumber = safeIntInputAll();
		updateNodeByNumber5(list5, updateNumber);

		// Print the list after deletion
		printf("List after update\n");
		printList5(list5);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted5(termini, list5);




		break;
	case '0':

		return 0;
		break;
	default:
		printf("Pogresan odabir\n");
		sporedni = '0';
	}


	return sporedni;
}



int izbornik3(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)
{
	printf("============================\
=====  BRISANJE  ================================\n");
	printf("===================  ");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("  ==================\n");
	printf("\t\t\tOpcija 1: Guma na skladistu!\n");
	printf("\t\t\tOpcija 2: Sve dosadasnje usluge!\n"); 
	printf("\t\t\tOpcija 3: Troskovi!\n");
	printf("\t\t\tOpcija 4: Prihodi!\n");
	printf("\t\t\tOpcija 5: Termini!\n");
	printf("\t\t\tOpcija 0: Vracanje u glavni izbornik!\n");
	printf("=======================================\
======================================\n");

	sporedni = 0;
	scanf("%c", &sporedni);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (sporedni)
	{
	case '1':

		//Skladiste

		list = NULL;
		// Read the list from the binary file
		list = readListFromBinaryFile(skladiste);
		if (list == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Delete a node based on number
		printf("Enter the number of the node to delete: ");
		deleteNumber = safeIntInput();
		deleteNodeByNumber(&list, deleteNumber);

		// Print the list after deletion
		printf("List after deletion:\n");
		printList(list);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted(skladiste, list);

		break;
	case '2':

		//Usluge

		list2 = NULL;
		// Read the list from the binary file
		list2 = readListFromBinaryFile2(usluge);
		if (list2 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Delete a node based on number
		printf("Enter the number of the node to delete: ");
		getchar();
		deleteNumber = safeIntInput();
		deleteNodeByNumber2(&list2, deleteNumber);

		// Print the list after deletion
		printf("List after deletion:\n");
		printList2(list2);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted2(usluge, list2);



		break;
	case '3':

		//Troskovi

		list3 = NULL;
		// Read the list from the binary file
		list3 = readListFromBinaryFile3(troskovi);
		if (list3 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Delete a node based on number
		printf("Enter the number of the node to delete: ");
		getchar();
		deleteNumber = safeIntInput();
		deleteNodeByNumber3(&list3, deleteNumber);

		// Print the list after deletion
		printf("List after deletion:\n");
		printList3(list3);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted3(troskovi, list3);



		break;
	case '4':

		//Prihodi

		list4 = NULL;
		// Read the list from the binary file
		list4 = readListFromBinaryFile4(prihodi);
		if (list4 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Delete a node based on number
		printf("Enter the number of the node to delete: ");
		getchar();
		deleteNumber = safeIntInput();
		deleteNodeByNumber4(&list4, deleteNumber);

		// Print the list after deletion
		printf("List after deletion:\n");
		printList4(list4);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted4(prihodi, list4);




		break;
	case '5':

		//Termini

		list5 = NULL;
		// Read the list from the binary file
		list5 = readListFromBinaryFile5(termini);
		if (list5 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Delete a node based on number
		printf("Enter the number of the node to delete: ");
		getchar();
		deleteNumber = safeIntInput();
		deleteNodeByNumber5(&list5, deleteNumber);

		// Print the list after deletion
		printf("List after deletion:\n");
		printList5(list5);

		//  Zapis izmjenjenog
		writeListToBinaryFileWhenDeleted5(termini, list5);


		
		break;
	case '0':

		return 0;
		break;
	default:
		printf("Pogresan odabir\n");
		sporedni = '0';
	}


	return sporedni;
}


int izbornik4(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)
{
	printf("============================\
======  ISPIS  ==================================\n");
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("=====================\n");
	printf("\t\t\tOpcija 1: Guma na skladistu!\n");
	printf("\t\t\tOpcija 2: Usluge!\n");
	printf("\t\t\tOpcija 3: Troskovi!\n");
	printf("\t\t\tOpcija 4: Prihodi!\n");
	printf("\t\t\tOpcija 5: Termini!\n");
	printf("\t\t\tOpcija 6: Izvjestaj o popravcima po mjesecu!\n");
	printf("\t\t\tOpcija 7: Izvjestaj dobita ili gubitka po mjesecu!\n");
	printf("\t\t\tOpcija 0: Vracanje u izbornik!\n");
	printf("======================================\
=======================================\n");

	sporedni = 0;
	scanf("%c", &sporedni);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (sporedni)
	{
	case '1':
		//Skladiste

		list = NULL;

		// Read the list from the binary file
		list = readListFromBinaryFile(skladiste);
		if (list == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Print the list
		printf("Original List:\n");
		printList(list);


		break;
	case '2':
		//Usluge

		list2 = NULL;

		// Read the list from the binary file
		list2 = readListFromBinaryFile2(usluge);
		if (list2 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Print the list
		printf("Original List:\n");
		printList2(list2);



		break;
	case '3':
		//Troskovi

		list3 = NULL;

		// Read the list from the binary file
		list3 = readListFromBinaryFile3(troskovi);
		if (list3 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Print the list
		printf("Original List:\n");
		printList3(list3);


		break;
	case '4':
		//Prihodi

		list4 = NULL;

		// Read the list from the binary file
		list4 = readListFromBinaryFile4(prihodi);
		if (list4 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Print the list
		printf("Original List:\n");
		printList4(list4);



		break;
	case '5':
		//Termini


		list5 = NULL;

		// Read the list from the binary file
		list5 = readListFromBinaryFile5(termini);
		if (list5 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Print the list
		printf("Original List:\n");
		printList5(list5);


		break;
	case '6':
		//Usluge po mjesecu


		list2 = NULL;

		// Read the list from the binary file
		list2 = readListFromBinaryFile2(usluge);
		if (list2 == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}


		short mjesec = 0;
		getchar();
		printf("Unesite mjesec usluge:");
		mjesec = safeShortInput();


		// Print the list
		printListUslugePoMjesecu(list2,mjesec);


		break;
	case '7':
		//dobit i gubitak

		DobitIliGubitak(usluge,troskovi,prihodi);


		break;
	case '0':

		return 0;

		break;
	default:
		printf("Pogresan odabir\n");
		sporedni = '0';
	}

	return sporedni;
}


int izbornik5(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)
{
	printf("=========================\
========  SORTIRANJE  ==============================\n");
	printf("===================  ");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("  ==================\n");
	printf("\t\t\tOpcija 1: Guma na skladistu!\n");
	printf("\t\t\tOpcija 2: Sve dosadasnje usluge!\n");
	printf("\t\t\tOpcija 3: Troskovi!\n");
	printf("\t\t\tOpcija 4: Prihodi!\n");
	printf("\t\t\tOpcija 5: Termini!\n");
	printf("\t\t\tOpcija 0: Vracanje u glavni izbornik!\n");
	printf("=======================================\
======================================\n");

	sporedni = 0;
	scanf("%c", &sporedni);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (sporedni)
	{
	case '1':

		list = NULL;
		// Read the list from the binary file
		list = readListFromBinaryFile(skladiste);
		if (list == NULL) {
			printf("Failed to read list from file\n");
			return 1;
		}

		// Sort the list by DOT
		insertSortSLListByDot(&list);

		// Print the sorted list
		printf("Sorted List by DOT (Descending):\n");
		printList(list);

		break;
	case '2':

		break;
	case '3':

		break;
	case '4':

		break;
	case '5':

		break;
	case '0':


		return 0;
		break;
	default:
		printf("Pogresan odabir\n");
		sporedni = '0';
	}


	return sporedni;
}


int izbornik6(const char* const skladiste, const char* const usluge, const char* const troskovi, const char* const prihodi, const char* const termini)
{
	printf("=========================\
========  PRETRAZIVANJE  ===========================\n");
	printf("===================  ");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("  ==================\n");
	printf("\t\t\tOpcija 1: Guma na skladistu!\n");
	printf("\t\t\tOpcija 2: Sve dosadasnje usluge!\n");
	printf("\t\t\tOpcija 3: Troskovi!\n");
	printf("\t\t\tOpcija 4: Prihodi!\n");
	printf("\t\t\tOpcija 5: Termini!\n");
	printf("\t\t\tOpcija 0: Vracanje u glavni izbornik!\n");
	printf("=======================================\
======================================\n");

	sporedni = 0;
	scanf("%c", &sporedni);
	while ((c = getchar()) != '\n' && c != EOF);

	switch (sporedni)
	{
	case '1':

		IspisOpcija(skladiste);

		
		break;
	case '2':

		break;
	case '3':

		break;
	case '4':

		break;
	case '5':

		break;

	case '0':


		return 0;
		break;
	default:
		printf("Pogresan odabir\n");
		sporedni = '0';
	}


	return sporedni;
}