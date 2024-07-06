#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"




/*HAY QUE HACER BIEN EL MANEJO DE ERRORES CUANDO ABRO ARCHIVOS*/
/*CREO QUE SE HACE CON ESTO: 
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
*/
/*
Para omitir la primera línea del archivo (que contiene el encabezado), 
puedes usar fgets para leer y descartar la primera línea antes de comenzar
a usar fscanf para leer los datos. Aquí hay una manera de hacerlo:
    char header[256];
    fgets(header, sizeof(header), file);
*/


int main(int argc, char const *argv[])
{
    parkingTicketsADT ticket = newADT();
    data fine;
    /*Lectura del file de infracciones*/
    FILE * infractionFile = fopen(argv[2], "r");
    if (!infractionFile) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fscanf(infractionFile, "%*[^\n]\n");
    while (fscanf(infractionFile, "%d;%30[^\n]", &fine.infractionId, fine.infractionName ) == 2)
    {
        infractionIdToName(ticket, fine.infractionId, fine.infractionName);
    }
    fclose(infractionFile);
    /*Lectura del file de infracciones*/

    /*Lectura del file de los tickets*/
    FILE * ticketFile = fopen(argv[1], "r");
    if (!ticketFile) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fscanf(ticketFile, "%*[^\n]\n");
    while (fscanf(ticketFile, "%10[^;];%*[^;];%d;%*[^;];%35[^\n]\n", fine.plate, &fine.infractionId, fine.infractionName) == 3)
    {
        query1Read(ticket, fine.infractionId);
    }
    fclose(ticketFile);
    q1List listaQ1 = arrToListQ1(ticket);
    /*Lectura del file de los tickets*/

    /*Resuelvo query1*/
    FILE * query1CSV = fopen(argv[3], "w");
    if (!query1CSV) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    listToQ1CSV(query1CSV, listaQ1);
    /*Resuelvo query1*/
}
