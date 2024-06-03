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
#include <time.h>


#include "functions.h"
#include "sll_data_type.h"



int main(void) {



	int uvjet = 1;

	char skladiste[25] = { "VulkoBazaSkladiste.bin" };
	char usluge[25] = { "VulkoBazaUsluge.bin" };
	char troskovi[25] = { "VulkoBazaTroskovi.bin" };
	char termini[25] = { "VulkoBazaTermini.bin" };
	char prihodi[25] = { "VulkoBazaPrihodi.bin" };



	while (uvjet)
	{
		uvjet = izbornik(skladiste, usluge, troskovi, prihodi, termini);
	}

	printf("Zavrsetak programa!\n");


	return 0;

}

	



	//Vrijeme sada

	/*

	time_t my_time;
	struct tm* timeinfo;
	time(&my_time);
	timeinfo = localtime(&my_time);

	printf("year:%d\n", timeinfo->tm_year + 1900);
	printf("month:%d\n", timeinfo->tm_mon + 1);
	printf("date:%d\n", timeinfo->tm_mday);
	printf("hour:%d\n", timeinfo->tm_hour);
	printf("minutes:%d\n", timeinfo->tm_min);
	printf("seconds:%d\n", timeinfo->tm_sec);

	

	return 0;
}

*/