#pragma once

#include "sll_data_type.h"

/*

extern char skladiste[25] = { "VulkoBazaSkladiste.bin" };
extern char usluge[25] = { "VulkoBazaUsluge.bin" };
extern char troskovi[25] = { "VulkoBazaTroskovi.bin" };
extern char termini[25] = { "VulkoBazaTermini.bin" };
extern char prihodi[25] = { "VulkoBazaPrihodi.bin" };

*/

//Izbornik

int izbornik (const char* const, const char* const, const char* const, const char* const, const char* const);
int izbornik1 (const char* const, const char* const, const char* const, const char* const, const char* const);
int izbornik2 (const char* const, const char* const, const char* const, const char* const, const char* const);
int izbornik3 (const char* const, const char* const, const char* const, const char* const, const char* const);
int izbornik4 (const char* const, const char* const, const char* const, const char* const, const char* const);
int izbornik5 (const char* const, const char* const, const char* const, const char* const, const char* const);
int izbornik6 (const char* const, const char* const, const char* const, const char* const, const char* const);

//Safe Input

void safeStringInput(char* buffer, int size);
int safeIntInput();
int safeIntInputAll();
short safeShortInput();

//Skladiste
void inputNodeData(SLLNODE* node);
void printList(SLLNODE* head);
void writeListToBinaryFileWhenDeleted(const char* filename, SLLNODE* head);
void writeNodeToBinaryFile(FILE* file, SLLNODE* node);
void writeListToBinaryFile(const char* filename, SLLNODE* head);
SLLNODE* readNodeFromBinaryFile(FILE* file);
SLLNODE* readListFromBinaryFile(const char* filename);
void insertNewNodeSLList(SLLNODE** head, SLLNODE** tail, int* currentNumber);
void deleteNodeByNumber(SLLNODE** head, int number);
int getLastNumberFromFile(const char* filename);

static void sortedInsertByDot(SLLNODE** headNode, SLLNODE* newNode);
void insertSortSLListByDot(SLLNODE** headNode);
void updateNodeByNumber(SLLNODE* head, int number);
void updateNodeData(SLLNODE* node);


//Usluge

void inputNodeData2(SLLNODE2* node);
void printList2(SLLNODE2* head);
void printListUslugePoMjesecu(SLLNODE2* head, short broj);
void writeListToBinaryFileWhenDeleted2(const char* filename, SLLNODE2* head);
void writeNodeToBinaryFile2(FILE* file, SLLNODE2* node);
void writeListToBinaryFile2(const char* filename, SLLNODE2* head);
SLLNODE2* readNodeFromBinaryFile2(FILE* file);
SLLNODE2* readListFromBinaryFile2(const char* filename);
void insertNewNodeSLList2(SLLNODE2** head, SLLNODE2** tail, int* currentNumber);
void deleteNodeByNumber2(SLLNODE2** head, int number);
int getLastNumberFromFile2(const char* filename);
void updateNodeByNumber2(SLLNODE2* head, int number);
void updateNodeData2(SLLNODE2* node);



//Troskovi

void inputNodeData3(SLLNODE3* node);
void printList3(SLLNODE3* head);
void writeListToBinaryFileWhenDeleted3(const char* filename, SLLNODE3* head);
void writeNodeToBinaryFile3(FILE* file, SLLNODE3* node);
void writeListToBinaryFile3(const char* filename, SLLNODE3* head);
SLLNODE3* readNodeFromBinaryFile3(FILE* file);
SLLNODE3* readListFromBinaryFile3(const char* filename);
void insertNewNodeSLList3(SLLNODE3** head, SLLNODE3** tail, int* currentNumber);
void deleteNodeByNumber3(SLLNODE3** head, int number);
int getLastNumberFromFile3(const char* filename);
void updateNodeByNumber3(SLLNODE3* head, int number);
void updateNodeData3(SLLNODE3* node);


//Prihodi

void inputNodeData4(SLLNODE4* node);
void printList4(SLLNODE4* head);
void writeListToBinaryFileWhenDeleted4(const char* filename, SLLNODE4* head);
void writeNodeToBinaryFile4(FILE* file, SLLNODE4* node);
void writeListToBinaryFile4(const char* filename, SLLNODE4* head);
SLLNODE4* readNodeFromBinaryFile4(FILE* file);
SLLNODE4* readListFromBinaryFile4(const char* filename);
void insertNewNodeSLList4(SLLNODE4** head, SLLNODE4** tail, int* currentNumber);
void deleteNodeByNumber4(SLLNODE4** head, int number);
int getLastNumberFromFile4(const char* filename);
void updateNodeByNumber4(SLLNODE4* head, int number);
void updateNodeData4(SLLNODE4* node);


//Termini

void inputNodeData5(SLLNODE5* node);
void printList5(SLLNODE5* head);
void writeListToBinaryFileWhenDeleted5(const char* filename, SLLNODE5* head);
void writeNodeToBinaryFile5(FILE* file, SLLNODE5* node);
void writeListToBinaryFile5(const char* filename, SLLNODE5* head);
SLLNODE5* readNodeFromBinaryFile5(FILE* file);
SLLNODE5* readListFromBinaryFile5(const char* filename);
void insertNewNodeSLList5(SLLNODE5** head, SLLNODE5** tail, int* currentNumber);
void deleteNodeByNumber5(SLLNODE5** head, int number);
int getLastNumberFromFile5(const char* filename);
void updateNodeByNumber5(SLLNODE5* head, int number);
void updateNodeData5(SLLNODE5* node);




int printListCijena(SLLNODE2* head2, SLLNODE3* head3, SLLNODE4* head4, short broj);
void DobitIliGubitak(const char* usluge, const char* troskovi, const char* prihodi);


int izlazIzPrograma(SLLNODE*, SLLNODE2*, SLLNODE3*, SLLNODE4*, SLLNODE5*);