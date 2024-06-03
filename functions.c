#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"
#include "sll_data_type.h"

//SafeInput
//-------------------------------------------------------------------------------------------	

void safeStringInput(char* buffer, int size) {
	if (fgets(buffer, size, stdin) != NULL) {
		size_t len = strlen(buffer);
		if (len > 0 && buffer[len - 1] == '\n') {
			buffer[len - 1] = '\0';
		}
		else {
			// Clear the rest of the input buffer if overflowed
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}
}

int safeIntInput() {
	char buffer[100];
	int value;
	
	while (1) {
		safeStringInput(buffer, sizeof(buffer));
		if (sscanf(buffer, "%3d", &value) == 1)
		{
			return value;
		}
		else {
			printf("Invalid input. Please enter a valid positive integer: ");
		}
	}
}

int safeIntInputAll() {
	int value;
	char ch;
	int result;

	while (1) {
		// Attempt to read an integer
		result = scanf("%d", &value);

		if (result == 1) {
			// Check for any trailing characters
			ch = getchar();
			if (ch == '\n' || ch == EOF) {
				return value;
				
			}
			else {
				// Clear the input buffer
				while ((ch = getchar()) != '\n' && ch != EOF);
				printf("Invalid input. Please enter a valid integer: ");
			}
		}
		else {
			// Handle invalid input
			printf("Invalid input. Please enter a valid integer: ");
			// Clear the input buffer
			while ((ch = getchar()) != '\n' && ch != EOF);
		}
	}
}


short safeShortInput() {
	char buffer[100];
	short value;
	while (1) {
		safeStringInput(buffer, sizeof(buffer));
		if (sscanf(buffer, "%2hd", &value) == 1) {
			return value;
		}
		else {
			printf("Invalid input. Please enter a valid short integer: ");
		}
	}
}

//Skladiste
//-------------------------------------------------------------------------------------------------------------------------


int getLastNumberFromFile(const char* filename) {
	SLLNODE* list = readListFromBinaryFile(filename);
	if (list == NULL) {
		return 0;  // No nodes, start numbering from 1
	}

	SLLNODE* current = list;
	int lastNumber = 0;

	while (current != NULL) {
		if (current->number > lastNumber) {
			lastNumber = current->number;
		}
		current = current->nextNode;
	}

	// Free the list
	current = list;
	while (current != NULL) {
		SLLNODE* next = current->nextNode;
		free(current);
		current = next;
	}

	return lastNumber;
}


void inputNodeData(SLLNODE* node) {
	do {
		printf("Unesite sirinu guma (3 digits max)!\n");
		getchar();
		node->width = safeIntInput();
		if (node->width == NULL) {
			printf("Invalid input. Width cannot exceed 3 digits. Please enter a valid width.\n");
		}
	} while (node->width == NULL);

	do {
		printf("Unesite visinu guma (2 digits max)!\n");
		node->height = safeShortInput();
		if (node->height == NULL) {
			printf("Invalid input. Height cannot exceed 2 digits. Please enter a valid height.\n");
		}
	} while (node->height == NULL);

	do {
		printf("Unesite promjer guma (2 digits max)!\n");
		node->diameter = safeShortInput();
		if (node->diameter == NULL) {
			printf("Invalid input. Diameter cannot exceed 2 digits. Please enter a valid diameter.\n");
		}
	} while (node->diameter == NULL);

	printf("Unesite DOT guma!\n");
	safeStringInput(node->dot, sizeof(node->dot));

	printf("Unesite marku guma!\n");
	safeStringInput(node->name, sizeof(node->name));


	do
	{
		printf("Unesite rezerviranost! (da ili ne)\n");
		safeStringInput(node->rezerviranost, sizeof(node->rezerviranost));


	} while (strcmp(node->rezerviranost, "da") != 0 && strcmp(node->rezerviranost, "ne") != 0);


	do
	{

		printf("Unesite dali su rabljene ili nove!\n");
		safeStringInput(node->starost, sizeof(node->starost));


	} while (strcmp(node->starost, "rabljene") != 0 && strcmp(node->starost, "nove"));


	do
	{

		printf("Unesite tip guma (zimske, ljetne, cijelogodisnje)!\n");
		safeStringInput(node->tip, sizeof(node->tip));

	} while (strcmp(node->tip, "zimske") != 0 && strcmp(node->tip, "ljetne") != 0 && strcmp(node->tip, "cijelogodisnje") != 0);


	node->nextNode = NULL;  // Initialize nextNode to NULL
}


void insertNewNodeSLList(SLLNODE** head, SLLNODE** tail, int* currentNumber) {
	SLLNODE* newNode = (SLLNODE*)malloc(sizeof(SLLNODE));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return;
	}

	newNode->number = (*currentNumber)++;  // Set and increment the node number

	inputNodeData(newNode);


	if (*head == NULL) {
		*head = newNode;
	}
	else {
		(*tail)->nextNode = newNode;
	}
	*tail = newNode;
}



void printList(SLLNODE* head) {
	SLLNODE* current = head;
	while (current != NULL) {
		printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
			current->number, current->width, current->height, current->diameter, current->dot, current->name,
			current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
		current = current->nextNode;
	}
}


void writeNodeToBinaryFile(FILE* file, SLLNODE* node) {
	fwrite(node, sizeof(SLLNODE), 1, file);
}



void writeListToBinaryFileWhenDeleted(const char* filename, SLLNODE* head) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

void writeListToBinaryFile(const char* filename, SLLNODE* head) {
	FILE* file = fopen(filename, "ab");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile(file, current);
		current = current->nextNode;
	}

	fclose(file);
}


SLLNODE* readNodeFromBinaryFile(FILE* file) {
	SLLNODE* newNode = (SLLNODE*)malloc(sizeof(SLLNODE));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	size_t readSize = fread(newNode, sizeof(SLLNODE), 1, file);
	if (readSize != 1) {
		free(newNode);
		return NULL;
	}

	newNode->nextNode = NULL;
	return newNode;
}

SLLNODE* readListFromBinaryFile(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return NULL;
	}

	SLLNODE* head = NULL;
	SLLNODE* tail = NULL;

	while (1) {
		SLLNODE* newNode = readNodeFromBinaryFile(file);
		if (newNode == NULL) {
			break;
		}

		if (head == NULL) {
			head = newNode;
		}
		else {
			tail->nextNode = newNode;
		}
		tail = newNode;
	}

	fclose(file);
	return head;
}


static void sortedInsertByDot(SLLNODE** headNode, SLLNODE* newNode) {
	// Extract year and week from DOT
	int yearNew = (newNode->dot[2] - '0') * 10 + (newNode->dot[3] - '0');
	int weekNew = (newNode->dot[0] - '0') * 10 + (newNode->dot[1] - '0');

	// Special case for the head end
	if (*headNode == NULL) {
		newNode->nextNode = NULL;
		*headNode = newNode;
	}
	else {
		SLLNODE* current = *headNode;
		SLLNODE* previous = NULL;
		while (current != NULL) {
			int yearCurrent = (current->dot[2] - '0') * 10 + (current->dot[3] - '0');
			int weekCurrent = (current->dot[0] - '0') * 10 + (current->dot[1] - '0');

			if (yearNew > yearCurrent || (yearNew == yearCurrent && weekNew > weekCurrent)) {
				break;
			}
			previous = current;
			current = current->nextNode;
		}
		if (previous == NULL) {
			newNode->nextNode = *headNode;
			*headNode = newNode;
		}
		else {
			newNode->nextNode = current;
			previous->nextNode = newNode;
		}
	}
}

void insertSortSLListByDot(SLLNODE** headNode) {
	SLLNODE* sortedList = NULL; // Initialize sorted linked list
	SLLNODE* currentNode = *headNode; // Current node to be inserted
	while (currentNode != NULL) {
		// Advance the current pointer to next node
		SLLNODE* nextNode = currentNode->nextNode;

		// Insert the current node into the sorted linked list
		sortedInsertByDot(&sortedList, currentNode);

		// Update current
		currentNode = nextNode;
	}

	// Update headRef to point to sorted linked list
	*headNode = sortedList;
}

void updateNodeData(SLLNODE* node) {
	int choice;
	do {
		printf("Select the field to update:\n");
		printf("1. Width\n");
		printf("2. Height\n");
		printf("3. Diameter\n");
		printf("4. DOT\n");
		printf("5. Name\n");
		printf("6. Rezerviranost\n");
		printf("7. Starost\n");
		printf("8. Tip\n");
		printf("0. Exit update\n");
		printf("Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Unesite novu sirinu guma (max 3 digits):\n");
			getchar();
			node->width = safeIntInput();
			break;
		case 2:
			printf("Unesite novu visinu guma (max 3 digits):\n");
			getchar();
			node->height = safeIntInput();
			break;
		case 3:
			printf("Unesite novi promjer guma (max 2 digits):\n");
			getchar();
			node->diameter = safeShortInput();
			break;
		case 4:
			printf("Unesite novi DOT guma:\n");
			getchar();
			safeStringInput(node->dot, sizeof(node->dot));
			break;
		case 5:
			printf("Unesite novu marku guma:\n");
			getchar();
			safeStringInput(node->name, sizeof(node->name));
			break;
		case 6:
			printf("Unesite novu rezerviranost:\n");
			getchar();
			safeStringInput(node->rezerviranost, sizeof(node->rezerviranost));
			break;
		case 7:
			printf("Unesite dali su rabljene ili nove:\n");
			getchar();
			safeStringInput(node->starost, sizeof(node->starost));
			break;
		case 8:
			printf("Unesite novi tip guma (zimske, ljetne):\n");
			getchar();
			safeStringInput(node->tip, sizeof(node->tip));
			break;
		case 0:
			printf("Exiting update menu.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 0);
}

void updateNodeByNumber(SLLNODE* head, int number) {
	SLLNODE* current = head;
	while (current != NULL && current->number != number) {
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	updateNodeData(current);
}


void deleteNodeByNumber(SLLNODE** head, int number) {
	SLLNODE* current = *head;
	SLLNODE* previous = NULL;

	while (current != NULL && current->number != number) {
		previous = current;
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	if (previous == NULL) {
		*head = current->nextNode;
	}
	else {
		previous->nextNode = current->nextNode;
	}

	free(current);
	printf("Node with number %d deleted.\n", number);
}










//Usluge
//--------------------------------------------------------------------------------------------



void inputNodeData2(SLLNODE2* node) {
	
	printf("Odaberite opciju: \n");
	printf("Usluga od sada: 1 ili Usluga od prije: 2: ");
	
	int uvjet = 0;
	scanf("%d", &uvjet);

	if (uvjet == 1)
	{
		time_t my_time;
		struct tm* timeinfo;
		time(&my_time);
		timeinfo = localtime(&my_time);


		node->day = timeinfo->tm_mday;
		node->month = timeinfo->tm_mon + 1;
		node->year = timeinfo->tm_year + 1900;
		node->hour = timeinfo->tm_hour;
		node->minute = timeinfo->tm_min;

		getchar();
		printf("Unesite opis usluge!\n");
		safeStringInput(node->usluga, sizeof(node->usluga));
	

		do {
			printf("Unesite cijenu usluge!\n");
			node->cijena = safeIntInputAll();
			if (node->cijena == NULL) {
				printf("Invalid input. Please enter a valid price.\n");
			}
		} while (node->cijena == NULL);

		node->nextNode = NULL;  // Initialize nextNode to NULL

	}
	else
	{
		getchar();
		do {
			printf("Unesite dan obavljanja usluge (2 digits max)!\n");
			node->day = safeShortInput();
			if (node->day == NULL) {
				printf("Invalid input. Day cannot exceed 2 digits. Please enter a valid day.\n");
			}
		} while (node->day == NULL);

		do {
			printf("Unesite mjesec obavljanja usluge (2 digits max)!\n");
			node->month = safeShortInput();
			if (node->month == NULL) {
				printf("Invalid input. Month cannot exceed 2 digits. Please enter a valid month.\n");
			}
		} while (node->month == NULL);

		do {
			printf("Unesite godinu obavljanja usluge!\n");
			node->year = safeIntInputAll();
			if (node->year == NULL) {
				printf("Invalid input. Year cannot exceed 2 digits. Please enter a valid year.\n");
			}
		} while (node->year == NULL);


		do {
			printf("Unesite sat obavljanja usluge (2 digits max)!\n");
			node->hour = safeShortInput();
			if (node->hour == NULL) {
				printf("Invalid input. Hour cannot exceed 2 digits. Please enter a valid hour.\n");
			}
		} while (node->hour == NULL);

		do {
			printf("Unesite minutu obavljanja usluge (2 digits max)!\n");
			node->minute = safeShortInput();
			if (node->minute == NULL) {
				printf("Invalid input. Minutes cannot exceed 2 digits. Please enter a valid minutes.\n");
			}
		} while (node->minute == NULL);


		printf("Unesite opis usluge!\n");
		safeStringInput(node->usluga, sizeof(node->usluga));
		

		do {
			printf("Unesite cijenu usluge!\n");
			node->cijena = safeIntInputAll();
			if (node->cijena == NULL) {
				printf("Invalid input. Please enter a valid price.\n");
			}
		} while (node->cijena == NULL);

		node->nextNode = NULL;  // Initialize nextNode to NULL


	}


}


void insertNewNodeSLList2(SLLNODE2** head, SLLNODE2** tail, int* currentNumber) {
	SLLNODE2* newNode = (SLLNODE2*)malloc(sizeof(SLLNODE2));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return;
	}

	newNode->number = (*currentNumber)++;  // Set and increment the node number

	inputNodeData2(newNode);

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		(*tail)->nextNode = newNode;
	}
	*tail = newNode;
}

void printList2(SLLNODE2* head) {
	SLLNODE2* current = head;
	while (current != NULL) {
		printf("Number: %d, Day: %hd, Month: %hd, Year: %d, Hour: %hd, Minute: %hd, Name: %.19s, Price: %d, NextNode: %p\n",
			current->number, current->day, current->month, current->year, current->hour, current->minute,
			current->usluga, current->cijena, (void*)current->nextNode);
		current = current->nextNode;
	}
}

void printListUslugePoMjesecu(SLLNODE2* head,short mjesec) {
	SLLNODE2* current = head;
	while (current != NULL) {

		if (current->month == mjesec)
		{
			printf("Number: %d, Day: %hd, Month: %hd, Year: %d, Hour: %hd, Minute: %hd, Name: %.19s, Price: %d\n",
				current->number, current->day, current->month, current->year, current->hour, current->minute,
				current->usluga, current->cijena);
		}
		

		current = current->nextNode;
	}

	if (current == NULL)
	{
		printf("Ne postoji usluga u %d mjesecu upisana u bazu! \n", mjesec);
	}

}


void writeListToBinaryFileWhenDeleted2(const char* filename, SLLNODE2* head) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE2* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile2(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

void writeNodeToBinaryFile2(FILE* file, SLLNODE2* node) {
	fwrite(node, sizeof(SLLNODE2), 1, file);
}

void writeListToBinaryFile2(const char* filename, SLLNODE2* head) {
	FILE* file = fopen(filename, "ab");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE2* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile2(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

SLLNODE2* readNodeFromBinaryFile2(FILE* file) {
	SLLNODE2* newNode = (SLLNODE2*)malloc(sizeof(SLLNODE2));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	size_t readSize = fread(newNode, sizeof(SLLNODE2), 1, file);
	if (readSize != 1) {
		free(newNode);
		return NULL;
	}

	newNode->nextNode = NULL;
	return newNode;
}

SLLNODE2* readListFromBinaryFile2(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return NULL;
	}

	SLLNODE2* head = NULL;
	SLLNODE2* tail = NULL;

	while (1) {
		SLLNODE2* newNode = readNodeFromBinaryFile2(file);
		if (newNode == NULL) {
			break;
		}
		if (head == NULL) {
			head = newNode;
		}
		else {
			tail->nextNode = newNode;
		}
		tail = newNode;
	}

	fclose(file);
	return head;
}

void deleteNodeByNumber2(SLLNODE2** head, int number) {
	SLLNODE2* current = *head;
	SLLNODE2* previous = NULL;

	while (current != NULL && current->number != number) {
		previous = current;
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	if (previous == NULL) {
		*head = current->nextNode;
	}
	else {
		previous->nextNode = current->nextNode;
	}

	free(current);
	printf("Node with number %d deleted.\n", number);
}

int getLastNumberFromFile2(const char* filename) {
	SLLNODE2* list = readListFromBinaryFile2(filename);
	if (list == NULL) {
		return 0;  // No nodes, start numbering from 1
	}

	SLLNODE2* current = list;
	int lastNumber = 0;

	while (current != NULL) {
		if (current->number > lastNumber) {
			lastNumber = current->number;
		}
		current = current->nextNode;
	}

	// Free the list
	current = list;
	while (current != NULL) {
		SLLNODE2* next = current->nextNode;
		free(current);
		current = next;
	}

	return lastNumber;
}

void updateNodeData2(SLLNODE2* node) {
	int choice;
	do {
		printf("Select the field to update:\n");
		printf("1. Day update\n");
		printf("2. Month update\n");
		printf("3. Year update\n");
		printf("4. Hour update\n");
		printf("5. Minute update\n");
		printf("6. Usluge update\n");
		printf("7. Cijena update\n");
		printf("0. Exit update\n");
		printf("Choice: ");
		scanf("%d", &choice);


		switch (choice) {
		case 1:
			printf("Unesite novu vrijednost za dan:\n");
			getchar();
			node->day = safeShortInput();
			break;
		case 2:
			printf("Unesite novu vrijednost za mjesec:\n");
			getchar();
			node->month = safeShortInput();
			break;
		case 3:
			printf("Unesite novu vrijednost za godinu:\n");
			getchar();
			node->year = safeIntInputAll();
			break;
		case 4:
			printf("Unesite novu vrijednost za sat:\n");
			getchar();
			node->hour = safeShortInput();
			break;
		case 5:
			printf("Unesite novu vrijednost za minute:\n");
			getchar();
			node->minute = safeShortInput();
			break;
		case 6:
			printf("Unesite novu usluge:\n");
			getchar();
			safeStringInput(node->usluga, sizeof(node->usluga));
			break;
		case 7:
			printf("Unesite novu vrijednost za cijenu:\n");
			getchar();
			node->cijena = safeIntInputAll();
			break;
		case 0:
			printf("Exiting update menu.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 0);
}

void updateNodeByNumber2(SLLNODE2* head, int number) {
	SLLNODE2* current = head;
	while (current != NULL && current->number != number) {
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	updateNodeData2(current);
}




//Troskovi
//--------------------------------------------------------------------------------------------



void inputNodeData3(SLLNODE3* node) {

	printf("Odaberite opciju: \n");
	printf("Trosak od sada: 1 ili trosak od prije: 2: ");

	int uvjet = 0;
	scanf("%d", &uvjet);

	if (uvjet == 1)
	{
		time_t my_time;
		struct tm* timeinfo;
		time(&my_time);
		timeinfo = localtime(&my_time);


		node->day = timeinfo->tm_mday;
		node->month = timeinfo->tm_mon + 1;
		node->year = timeinfo->tm_year + 1900;
		node->hour = timeinfo->tm_hour;
		node->minute = timeinfo->tm_min;

		getchar();
		printf("Unesite opis troska!\n");
		safeStringInput(node->trosak, sizeof(node->trosak));


		do {
			printf("Unesite cijenu troska!\n");
			node->cijena = safeIntInputAll();
			if (node->cijena == NULL) {
				printf("Invalid input. Please enter a valid price.\n");
			}
		} while (node->cijena == NULL);

		node->nextNode = NULL;  // Initialize nextNode to NULL

	}
	else
	{
		getchar();
		do {
			printf("Unesite dan koji ste imali trosak (2 digits max)!\n");
			node->day = safeShortInput();
			if (node->day == NULL) {
				printf("Invalid input. Day cannot exceed 2 digits. Please enter a valid day.\n");
			}
		} while (node->day == NULL);

		do {
			printf("Unesite mjesec koji ste imali trosak (2 digits max)!\n");
			node->month = safeShortInput();
			if (node->month == NULL) {
				printf("Invalid input. Month cannot exceed 2 digits. Please enter a valid month.\n");
			}
		} while (node->month == NULL);

		do {
			printf("Unesite godinu koji ste imali trosak!\n");
			node->year = safeIntInputAll();
			if (node->year == NULL) {
				printf("Invalid input. Year cannot exceed 2 digits. Please enter a valid year.\n");
			}
		} while (node->year == NULL);


		do {
			printf("Unesite sat u kojem ste imali trosak (2 digits max)!\n");
			node->hour = safeShortInput();
			if (node->hour == NULL) {
				printf("Invalid input. Hour cannot exceed 2 digits. Please enter a valid hour.\n");
			}
		} while (node->hour == NULL);

		do {
			printf("Unesite minutu u kojem ste imali trosak (2 digits max)!\n");
			node->minute = safeShortInput();
			if (node->minute == NULL) {
				printf("Invalid input. Minutes cannot exceed 2 digits. Please enter a valid minutes.\n");
			}
		} while (node->minute == NULL);


		printf("Unesite opis za trosak!\n");
		safeStringInput(node->trosak, sizeof(node->trosak));


		do {
			printf("Unesite cijenu troska!\n");
			node->cijena = safeIntInputAll();
			if (node->cijena == NULL) {
				printf("Invalid input. Please enter a valid price.\n");
			}
		} while (node->cijena == NULL);

		node->nextNode = NULL;  // Initialize nextNode to NULL


	}


}


void insertNewNodeSLList3(SLLNODE3** head, SLLNODE3** tail, int* currentNumber) {
	SLLNODE3* newNode = (SLLNODE3*)malloc(sizeof(SLLNODE3));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return;
	}

	newNode->number = (*currentNumber)++;  // Set and increment the node number

	inputNodeData3(newNode);

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		(*tail)->nextNode = newNode;
	}
	*tail = newNode;
}



void printList3(SLLNODE3* head) {
	SLLNODE3* current = head;
	while (current != NULL) {
		printf("Number: %d, Day: %hd, Month: %hd, Year: %d, Hour: %hd, Minute: %hd, Name: %.19s, Price: %d, NextNode: %p\n",
			current->number, current->day, current->month, current->year, current->hour, current->minute,
			current->trosak, current->cijena, (void*)current->nextNode);
		current = current->nextNode;
	}
}


void writeListToBinaryFileWhenDeleted3(const char* filename, SLLNODE3* head) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE3* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile3(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

void writeNodeToBinaryFile3(FILE* file, SLLNODE3* node) {
	fwrite(node, sizeof(SLLNODE3), 1, file);
}

void writeListToBinaryFile3(const char* filename, SLLNODE3* head) {
	FILE* file = fopen(filename, "ab");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE3* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile3(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

SLLNODE3* readNodeFromBinaryFile3(FILE* file) {
	SLLNODE3* newNode = (SLLNODE3*)malloc(sizeof(SLLNODE3));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	size_t readSize = fread(newNode, sizeof(SLLNODE3), 1, file);
	if (readSize != 1) {
		free(newNode);
		return NULL;
	}

	newNode->nextNode = NULL;
	return newNode;
}

SLLNODE3* readListFromBinaryFile3(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return NULL;
	}

	SLLNODE3* head = NULL;
	SLLNODE3* tail = NULL;

	while (1) {
		SLLNODE3* newNode = readNodeFromBinaryFile3(file);
		if (newNode == NULL) {
			break;
		}
		if (head == NULL) {
			head = newNode;
		}
		else {
			tail->nextNode = newNode;
		}
		tail = newNode;
	}

	fclose(file);
	return head;
}

void deleteNodeByNumber3(SLLNODE3** head, int number) {
	SLLNODE3* current = *head;
	SLLNODE3* previous = NULL;

	while (current != NULL && current->number != number) {
		previous = current;
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	if (previous == NULL) {
		*head = current->nextNode;
	}
	else {
		previous->nextNode = current->nextNode;
	}

	free(current);
	printf("Node with number %d deleted.\n", number);
}

int getLastNumberFromFile3(const char* filename) {
	SLLNODE3* list = readListFromBinaryFile3(filename);
	if (list == NULL) {
		return 0;  // No nodes, start numbering from 1
	}

	SLLNODE3* current = list;
	int lastNumber = 0;

	while (current != NULL) {
		if (current->number > lastNumber) {
			lastNumber = current->number;
		}
		current = current->nextNode;
	}

	// Free the list
	current = list;
	while (current != NULL) {
		SLLNODE3* next = current->nextNode;
		free(current);
		current = next;
	}

	return lastNumber;
}

void updateNodeData3(SLLNODE3* node) {
	int choice;
	do {
		printf("Select the field to update:\n");
		printf("1. Day update\n");
		printf("2. Month update\n");
		printf("3. Year update\n");
		printf("4. Hour update\n");
		printf("5. Minute update\n");
		printf("6. Trosak update\n");
		printf("7. Iznos update\n");
		printf("0. Exit update\n");
		printf("Choice: ");
		scanf("%d", &choice);


		switch (choice) {
		case 1:
			printf("Unesite novu vrijednost za dan:\n");
			getchar();
			node->day = safeShortInput();
			break;
		case 2:
			printf("Unesite novu vrijednost za mjesec:\n");
			getchar();
			node->month = safeShortInput();
			break;
		case 3:
			printf("Unesite novu vrijednost za godinu:\n");
			getchar();
			node->year = safeIntInputAll();
			break;
		case 4:
			printf("Unesite novu vrijednost za sat:\n");
			getchar();
			node->hour = safeShortInput();
			break;
		case 5:
			printf("Unesite novu vrijednost za minute:\n");
			getchar();
			node->minute = safeShortInput();
			break;
		case 6:
			printf("Unesite novu vrijednost za trosak:\n");
			getchar();
			safeStringInput(node->trosak, sizeof(node->trosak));
			break;
		case 7:
			printf("Unesite novu vrijednost za cijenu:\n");
			getchar();
			node->cijena = safeIntInputAll();
			break;
		case 0:
			printf("Exiting update menu.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 0);
}

void updateNodeByNumber3(SLLNODE3* head, int number) {
	SLLNODE3* current = head;
	while (current != NULL && current->number != number) {
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	updateNodeData3(current);
}




//Prihodi
//--------------------------------------------------------------------------------------------



void inputNodeData4(SLLNODE4* node) {

	printf("Odaberite opciju: \n");
	printf("Prihod od sada: 1 ili prihod od prije: 2: ");

	int uvjet = 0;
	scanf("%d", &uvjet);

	if (uvjet == 1)
	{
		time_t my_time;
		struct tm* timeinfo;
		time(&my_time);
		timeinfo = localtime(&my_time);


		node->day = timeinfo->tm_mday;
		node->month = timeinfo->tm_mon + 1;
		node->year = timeinfo->tm_year + 1900;
		node->hour = timeinfo->tm_hour;
		node->minute = timeinfo->tm_min;

		getchar();
		printf("Unesite opis prihoda!\n");
		safeStringInput(node->prihod, sizeof(node->prihod));


		do {
			printf("Unesite iznos prihoda!\n");
			node->cijena = safeIntInputAll();
			if (node->cijena == NULL) {
				printf("Invalid input. Please enter a valid price.\n");
			}
		} while (node->cijena == NULL);

		node->nextNode = NULL;  // Initialize nextNode to NULL

	}
	else
	{
		getchar();
		do {
			printf("Unesite dan dobijanja prihoda (2 digits max)!\n");
			node->day = safeShortInput();
			if (node->day == NULL) {
				printf("Invalid input. Day cannot exceed 2 digits. Please enter a valid day.\n");
			}
		} while (node->day == NULL);

		do {
			printf("Unesite mjesec dobijanja prihoda (2 digits max)!\n");
			node->month = safeShortInput();
			if (node->month == NULL) {
				printf("Invalid input. Month cannot exceed 2 digits. Please enter a valid month.\n");
			}
		} while (node->month == NULL);

		do {
			printf("Unesite godinu dobijanja prihoda!\n");
			node->year = safeIntInputAll();
			if (node->year == NULL) {
				printf("Invalid input. Year cannot exceed 2 digits. Please enter a valid year.\n");
			}
		} while (node->year == NULL);


		do {
			printf("Unesite sat dobijanja prihoda (2 digits max)!\n");
			node->hour = safeShortInput();
			if (node->hour == NULL) {
				printf("Invalid input. Hour cannot exceed 2 digits. Please enter a valid hour.\n");
			}
		} while (node->hour == NULL);

		do {
			printf("Unesite minutu dobijanja prihoda (2 digits max)!\n");
			node->minute = safeShortInput();
			if (node->minute == NULL) {
				printf("Invalid input. Minutes cannot exceed 2 digits. Please enter a valid minutes.\n");
			}
		} while (node->minute == NULL);


		printf("Unesite opis prihoda!\n");
		safeStringInput(node->prihod, sizeof(node->prihod));


		do {
			printf("Unesite iznos prihoda!\n");
			node->cijena = safeIntInputAll();
			if (node->cijena == NULL) {
				printf("Invalid input. Please enter a valid price.\n");
			}
		} while (node->cijena == NULL);

		node->nextNode = NULL;  // Initialize nextNode to NULL


	}


}


void insertNewNodeSLList4(SLLNODE4** head, SLLNODE4** tail, int* currentNumber) {
	SLLNODE4* newNode = (SLLNODE4*)malloc(sizeof(SLLNODE4));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return;
	}

	newNode->number = (*currentNumber)++;  // Set and increment the node number

	inputNodeData4(newNode);

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		(*tail)->nextNode = newNode;
	}
	*tail = newNode;
}



void printList4(SLLNODE4* head) {
	SLLNODE4* current = head;
	while (current != NULL) {
		printf("Number: %d, Day: %hd, Month: %hd, Year: %d, Hour: %hd, Minute: %hd, Name: %.19s, Price: %d, NextNode: %p\n",
			current->number, current->day, current->month, current->year, current->hour, current->minute,
			current->prihod, current->cijena, (void*)current->nextNode);
		current = current->nextNode;
	}
}


void writeListToBinaryFileWhenDeleted4(const char* filename, SLLNODE4* head) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE4* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile4(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

void writeNodeToBinaryFile4(FILE* file, SLLNODE4* node) {
	fwrite(node, sizeof(SLLNODE4), 1, file);
}

void writeListToBinaryFile4(const char* filename, SLLNODE4* head) {
	FILE* file = fopen(filename, "ab");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE4* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile4(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

SLLNODE4* readNodeFromBinaryFile4(FILE* file) {
	SLLNODE4* newNode = (SLLNODE4*)malloc(sizeof(SLLNODE4));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	size_t readSize = fread(newNode, sizeof(SLLNODE4), 1, file);
	if (readSize != 1) {
		free(newNode);
		return NULL;
	}

	newNode->nextNode = NULL;
	return newNode;
}

SLLNODE4* readListFromBinaryFile4(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return NULL;
	}

	SLLNODE4* head = NULL;
	SLLNODE4* tail = NULL;

	while (1) {
		SLLNODE4* newNode = readNodeFromBinaryFile4(file);
		if (newNode == NULL) {
			break;
		}
		if (head == NULL) {
			head = newNode;
		}
		else {
			tail->nextNode = newNode;
		}
		tail = newNode;
	}

	fclose(file);
	return head;
}

void deleteNodeByNumber4(SLLNODE4** head, int number) {
	SLLNODE4* current = *head;
	SLLNODE4* previous = NULL;

	while (current != NULL && current->number != number) {
		previous = current;
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	if (previous == NULL) {
		*head = current->nextNode;
	}
	else {
		previous->nextNode = current->nextNode;
	}

	free(current);
	printf("Node with number %d deleted.\n", number);
}

int getLastNumberFromFile4(const char* filename) {
	SLLNODE4* list = readListFromBinaryFile4(filename);
	if (list == NULL) {
		return 0;  // No nodes, start numbering from 1
	}

	SLLNODE4* current = list;
	int lastNumber = 0;

	while (current != NULL) {
		if (current->number > lastNumber) {
			lastNumber = current->number;
		}
		current = current->nextNode;
	}

	// Free the list
	current = list;
	while (current != NULL) {
		SLLNODE4* next = current->nextNode;
		free(current);
		current = next;
	}

	return lastNumber;
}

void updateNodeData4(SLLNODE4* node) {
	int choice;
	do {
		printf("Select the field to update:\n");
		printf("1. Day update\n");
		printf("2. Month update\n");
		printf("3. Year update\n");
		printf("4. Hour update\n");
		printf("5. Minute update\n");
		printf("6. Prihod update\n");
		printf("7. Iznos update\n");
		printf("0. Exit update\n");
		printf("Choice: ");
		scanf("%d", &choice);


		switch (choice) {
		case 1:
			printf("Unesite novu vrijednost za dan:\n");
			getchar();
			node->day = safeShortInput();
			break;
		case 2:
			printf("Unesite novu vrijednost za mjesec:\n");
			getchar();
			node->month = safeShortInput();
			break;
		case 3:
			printf("Unesite novu vrijednost za godinu:\n");
			getchar();
			node->year = safeIntInputAll();
			break;
		case 4:
			printf("Unesite novu vrijednost za sat:\n");
			getchar();
			node->hour = safeShortInput();
			break;
		case 5:
			printf("Unesite novu vrijednost za minute:\n");
			getchar();
			node->minute = safeShortInput();
			break;
		case 6:
			printf("Unesite novi prihod:\n");
			getchar();
			safeStringInput(node->prihod, sizeof(node->prihod));
			break;
		case 7:
			printf("Unesite novu vrijednost za cijenu:\n");
			getchar();
			node->cijena = safeIntInputAll();
			break;
		case 0:
			printf("Exiting update menu.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 0);
}

void updateNodeByNumber4(SLLNODE4* head, int number) {
	SLLNODE4* current = head;
	while (current != NULL && current->number != number) {
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	updateNodeData4(current);
}






//Termini
//--------------------------------------------------------------------------------------------


void inputNodeData5(SLLNODE5* node) {

		getchar();
		do {
			printf("Unesite dan za termin (2 digits max)!\n");
			node->day = safeShortInput();
			if (node->day == NULL) {
				printf("Invalid input. Day cannot exceed 2 digits. Please enter a valid day.\n");
			}
		} while (node->day == NULL);

		do {
			printf("Unesite mjesec za termin (2 digits max)!\n");
			node->month = safeShortInput();
			if (node->month == NULL) {
				printf("Invalid input. Month cannot exceed 2 digits. Please enter a valid month.\n");
			}
		} while (node->month == NULL);

		do {
			printf("Unesite godinu za termin!\n");
			node->year = safeIntInputAll();
			if (node->year == NULL) {
				printf("Invalid input. Year cannot exceed 2 digits. Please enter a valid year.\n");
			}
		} while (node->year == NULL);


		do {
			printf("Unesite sat za termin (2 digits max)!\n");
			node->hour = safeShortInput();
			if (node->hour == NULL) {
				printf("Invalid input. Hour cannot exceed 2 digits. Please enter a valid hour.\n");
			}
		} while (node->hour == NULL);

		do {
			printf("Unesite minutu za termin (2 digits max)!\n");
			node->minute = safeShortInput();
			if (node->minute == NULL) {
				printf("Invalid input. Minutes cannot exceed 2 digits. Please enter a valid minutes.\n");
			}
		} while (node->minute == NULL);


		printf("Unesite opis termina!\n");
		safeStringInput(node->opis, sizeof(node->opis));


		node->nextNode = NULL;  // Initialize nextNode to NULL



}


void insertNewNodeSLList5(SLLNODE5** head, SLLNODE5** tail, int* currentNumber) {
	SLLNODE5* newNode = (SLLNODE5*)malloc(sizeof(SLLNODE5));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return;
	}

	newNode->number = (*currentNumber)++;  // Set and increment the node number

	inputNodeData5(newNode);

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		(*tail)->nextNode = newNode;
	}
	*tail = newNode;
}



void printList5(SLLNODE5* head) {
	SLLNODE5* current = head;
	while (current != NULL) {
		printf("Number: %d, Day: %hd, Month: %hd, Year: %d, Hour: %hd, Minute: %hd, Name: %.19s, NextNode: %p\n",
			current->number, current->day, current->month, current->year, current->hour, current->minute,
			current->opis, (void*)current->nextNode);
		current = current->nextNode;
	}
}


void writeListToBinaryFileWhenDeleted5(const char* filename, SLLNODE5* head) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE5* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile5(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

void writeNodeToBinaryFile5(FILE* file, SLLNODE5* node) {
	fwrite(node, sizeof(SLLNODE5), 1, file);
}

void writeListToBinaryFile5(const char* filename, SLLNODE5* head) {
	FILE* file = fopen(filename, "ab");
	if (file == NULL) {
		perror("Failed to open file for writing");
		return;
	}

	SLLNODE5* current = head;
	while (current != NULL) {
		writeNodeToBinaryFile5(file, current);
		current = current->nextNode;
	}

	fclose(file);
}

SLLNODE5* readNodeFromBinaryFile5(FILE* file) {
	SLLNODE5* newNode = (SLLNODE5*)malloc(sizeof(SLLNODE5));
	if (newNode == NULL) {
		perror("Failed to allocate memory");
		return NULL;
	}

	size_t readSize = fread(newNode, sizeof(SLLNODE5), 1, file);
	if (readSize != 1) {
		free(newNode);
		return NULL;
	}

	newNode->nextNode = NULL;
	return newNode;
}

SLLNODE5* readListFromBinaryFile5(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return NULL;
	}

	SLLNODE5* head = NULL;
	SLLNODE5* tail = NULL;

	while (1) {
		SLLNODE5* newNode = readNodeFromBinaryFile5(file);
		if (newNode == NULL) {
			break;
		}
		if (head == NULL) {
			head = newNode;
		}
		else {
			tail->nextNode = newNode;
		}
		tail = newNode;
	}

	fclose(file);
	return head;
}

void deleteNodeByNumber5(SLLNODE5** head, int number) {
	SLLNODE5* current = *head;
	SLLNODE5* previous = NULL;

	while (current != NULL && current->number != number) {
		previous = current;
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	if (previous == NULL) {
		*head = current->nextNode;
	}
	else {
		previous->nextNode = current->nextNode;
	}

	free(current);
	printf("Node with number %d deleted.\n", number);
}

int getLastNumberFromFile5(const char* filename) {
	SLLNODE5* list = readListFromBinaryFile5(filename);
	if (list == NULL) {
		return 0;  // No nodes, start numbering from 1
	}

	SLLNODE5* current = list;
	int lastNumber = 0;

	while (current != NULL) {
		if (current->number > lastNumber) {
			lastNumber = current->number;
		}
		current = current->nextNode;
	}

	// Free the list
	current = list;
	while (current != NULL) {
		SLLNODE5* next = current->nextNode;
		free(current);
		current = next;
	}

	return lastNumber;
}

void updateNodeData5(SLLNODE5* node) {
	int choice;
	do {
		printf("Select the field to update:\n");
		printf("1. Day update\n");
		printf("2. Month update\n");
		printf("3. Year update\n");
		printf("4. Hour update\n");
		printf("5. Minute update\n");
		printf("6. Opis termina update\n");
		printf("0. Exit update\n");
		printf("Choice: ");
		scanf("%d", &choice);


		switch (choice) {
		case 1:
			printf("Unesite novu vrijednost za dan:\n");
			getchar();
			node->day = safeShortInput();
			break;
		case 2:
			printf("Unesite novu vrijednost za mjesec:\n");
			getchar();
			node->month = safeShortInput();
			break;
		case 3:
			printf("Unesite novu vrijednost za godinu:\n");
			getchar();
			node->year = safeIntInputAll();
			break;
		case 4:
			printf("Unesite novu vrijednost za sat:\n");
			getchar();
			node->hour = safeShortInput();
			break;
		case 5:
			printf("Unesite novu vrijednost za minute:\n");
			getchar();
			node->minute = safeShortInput();
			break;
		case 6:
			printf("Unesite novi opis termina:\n");
			getchar();
			safeStringInput(node->opis, sizeof(node->opis));
			break;
		case 0:
			printf("Exiting update menu.\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 0);
}

void updateNodeByNumber5(SLLNODE5* head, int number) {
	SLLNODE5* current = head;
	while (current != NULL && current->number != number) {
		current = current->nextNode;
	}

	if (current == NULL) {
		printf("Node with number %d not found.\n", number);
		return;
	}

	updateNodeData5(current);
}


//Dobit ili gubitak


int printListCijena(SLLNODE2* head2, SLLNODE3* head3, SLLNODE4* head4,short mjesec)
{

	int UkupnaCijena = 0;

	SLLNODE2* current2 = head2;
	while (current2 != NULL) {

		if (current2->month == mjesec)
		{
			UkupnaCijena = UkupnaCijena + current2->cijena;
		}

		current2 = current2->nextNode;
	}

	SLLNODE3* current3 = head3;
	while (current3 != NULL) {

		if (current3->month == mjesec)
		{
			UkupnaCijena = UkupnaCijena - current3->cijena;
		}

		current3 = current3->nextNode;
	}

	SLLNODE4* current4 = head4;
	while (current4 != NULL) {

		if (current4->month == mjesec)
		{
			UkupnaCijena = UkupnaCijena + current4->cijena;
		}

		current4 = current4->nextNode;
	}


	return UkupnaCijena;


}


void DobitIliGubitak(const char* usluge, const char* troskovi, const char* prihodi)
{

	int UkupnaCijena = 0;

	SLLNODE2* list2 = NULL;

	// Read the list from the binary file
	list2 = readListFromBinaryFile2(usluge);
	if (list2 == NULL) {
		printf("Failed to read list from file\n");
		
	}

	SLLNODE3* list3 = NULL;

	// Read the list from the binary file
	list3 = readListFromBinaryFile3(troskovi);
	if (list3 == NULL) {
		printf("Failed to read list from file\n");
		
	}

	SLLNODE4* list4 = NULL;

	// Read the list from the binary file
	list4 = readListFromBinaryFile4(prihodi);
	if (list4 == NULL) {
		printf("Failed to read list from file\n");
		
	}

	short mjesec = 0;

	getchar();
	printf("Unesite mjesec: ");
	mjesec = safeShortInput();

	UkupnaCijena = printListCijena(list2, list3, list4, mjesec);

	printf("Izvjestaj dobitka i gubitka po mjesecu! \n");

	if (UkupnaCijena > 0)
	{
		printf("Ukupni dobitak iznosi: %d\n", UkupnaCijena);
	}
	else if (UkupnaCijena < 0)
	{
		printf("Ukupni gubitak iznosi: %d\n", UkupnaCijena);
	}
	else if (UkupnaCijena == 0)
	{
		printf("Dobitak iznosi: %d. Ili nema zapisa u tom mjesecu.\n", UkupnaCijena);
	}

	free(list2);
	free(list3);
	free(list4);


}



//Pretrazivanje

//Skladiste

void pretrazivanjeSkladisteInt(SLLNODE* head, int broj, int odabir)
{

	SLLNODE* current = head;

	if (odabir == 1)
	{
		
		while (current != NULL) 
		{
			if (current->number == broj)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}
	}
	else if (odabir == 2)
	{

		while (current != NULL)
		{
			if (current->width == broj)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}

	}
	else if (odabir == 3)
	{

		while (current != NULL)
		{
			if (current->height == broj)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}


	}
	

	
}

int pretrazivanjeSkladisteShort(SLLNODE* head, short diameter)
{

	SLLNODE* current = head;

	while (current != NULL) {

		if (current->diameter == diameter)
		{
			printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
				current->number, current->width, current->height, current->diameter, current->dot, current->name,
				current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
		}

		current = current->nextNode;
	}
}

int pretrazivanjeSkladisteString(SLLNODE* head, char znak[], int odabir)
{

	SLLNODE* current = head;


	if (odabir == 1)
	{

		while (current != NULL) {

			if (strcmp(current->dot, znak) == 0)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}


	}
	else if (odabir == 2)
	{

		while (current != NULL) {

			if (strcmp(current->name, znak) == 0)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}


	}
	else if (odabir == 3)
	{

		while (current != NULL) {

			if (strcmp(current->rezerviranost, znak) == 0)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}


	}
	else if (odabir == 4)
	{

		while (current != NULL) {

			if (strcmp(current->starost, znak) == 0)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}


	}
	else if (odabir == 5)
	{

		while (current != NULL) {

			if (strcmp(current->tip, znak) == 0)
			{
				printf("Number: %d, Width: %d, Height: %d, Diameter: %hd, Dot: %.5s, Name: %.29s, Rezerviranost: %.2s, Starost: %.9s, Tip: %.14s, NextNode: %p\n",
					current->number, current->width, current->height, current->diameter, current->dot, current->name,
					current->rezerviranost, current->starost, current->tip, (void*)current->nextNode);
			}

			current = current->nextNode;
		}


	}


}


void IspisOpcija(skladiste)
{



	SLLNODE* list = NULL;
	// Read the list from the binary file
	list = readListFromBinaryFile(skladiste);
	if (list == NULL) {
		printf("Failed to read list from file\n");
		return 1;
	}


	int choice;

	int BrojInt;
	short BrojShort;
	char Znak[30];

	do {
		printf("Odaberi opciju za pretrazivanje:\n");
		printf("1. ID\n");
		printf("2. Width\n");
		printf("3. Height\n");
		printf("4. Diameter\n");
		printf("5. DOT\n");
		printf("6. Name\n");
		printf("7. Rezerviranost\n");
		printf("8. Starost\n");
		printf("9. Tip\n");
		printf("0. Exit filter\n");
		printf("Choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Unesite ID!\n");
			getchar();
			BrojInt = safeIntInput();

			pretrazivanjeSkladisteInt(list, BrojInt, 1);


			break;
		case 2:
			printf("Unesite sirinu guma (3 digits max)!\n");
			getchar();
			BrojInt = safeIntInput();
		
			pretrazivanjeSkladisteInt(list, BrojInt, 2);
			

			break;
		case 3:
			printf("Unesite visinu guma (2 digits max)!\n");
			getchar();
			BrojInt = safeShortInput();
		
			pretrazivanjeSkladisteInt(list, BrojInt, 3);
			
			break;
		case 4:
			printf("Unesite promjer guma (2 digits max)!\n");
			getchar();
			BrojShort = safeShortInput();
			
			pretrazivanjeSkladisteShort(list, BrojShort);

			break;
		case 5:
			printf("Unesite DOT guma!\n");
			getchar();
			safeStringInput(Znak, sizeof(Znak));

			pretrazivanjeSkladisteString(list, Znak, 1);

			break;
		case 6:
			printf("Unesite marku guma!\n");
			getchar();
			safeStringInput(Znak, sizeof(Znak));

			pretrazivanjeSkladisteString(list, Znak, 2);

			break;
		case 7:
			printf("Unesite rezerviranost! (da ili ne)\n");
			getchar();
			safeStringInput(Znak, sizeof(Znak));

			pretrazivanjeSkladisteString(list, Znak, 3);


			break;
		case 8:
			printf("Unesite dali su rabljene ili nove!\n");
			getchar();
			safeStringInput(Znak, sizeof(Znak));

			pretrazivanjeSkladisteString(list, Znak, 4);

			break;
		case 9:
			printf("Unesite tip guma (zimske, ljetne):\n");
			getchar();
			safeStringInput(Znak, sizeof(Znak));

			pretrazivanjeSkladisteString(list, Znak, 5);

			break;
		case 0:
			printf("Exiting menu.\n");
			break;

		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	
		return 0;
	} while (choice != 0);
}









int izlazIzPrograma(SLLNODE* list, SLLNODE2* list2, SLLNODE3* list3, SLLNODE4* list4, SLLNODE5* list5) {


	char sigurno[3];

	printf("Da li ste sigurni kako zelite zavrsiti program?\n");
	printf("da/ne\n");
	scanf("%3[^\n]", sigurno);
	getchar();

	if (strcmp(sigurno, "da") == 0)
	{
		free(list);
		free(list2);
		free(list3);
		free(list4);
		free(list5);
		return '0';
	}
	else
	{
		return '1';
	}


}

