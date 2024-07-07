#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"

void loadInfractions(parkingTicketsADT t, FILE * infractionFile);

int main(int argc, char const *argv[])
{
    if (argc != 5)
        throwError("Error en la cantidad de argumentos");
    parkingTicketsADT tickets = newADT();

    ticket fine;

    /*Lectura del file de infracciones*/
    FILE * infractionFile = fopen(argv[2], "r");
    loadInfractions(tickets, infractionFile);
    fclose(infractionFile);
    /*Lectura del file de infracciones*/

    /*Lectura del file de los tickets*/
    FILE * ticketFile = fopen(argv[1], "r");
    if (ticketFile == NULL) {
        freeADT(tickets);
        throwError("Error at opening tickets file");
    }
    fscanf(ticketFile, "%*[^\n]\n");
    while (fscanf(ticketFile, "%10[^;];%*[^;];%d;%*[^;];%35[^\n]\n", fine.plate, &fine.infractionId, fine.agency) == 3){
        query1Read(tickets, fine.infractionId);
        query2Read(tickets, fine.infractionId, fine.agency);
    }
    fclose(ticketFile);
    /*Lectura del file de los tickets*/

    /*Resuelvo query1*/
    q1List listaQ1 = arrToListQ1(tickets);
    FILE * query1CSV = fopen(argv[3], "w");
    if (!query1CSV) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    listToQ1CSV(query1CSV, listaQ1);
    /*Resuelvo query1*/

    /*Resuelvo query2*/
    FILE * query2CSV = fopen(argv[4],"w");
    if (!query2CSV) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    query2Processing(tickets);
    query2ToCSV(query2CSV, tickets);
    /*Resuelvo query2*/
}


//Funcion que recibe el archivo de infracciones y guarda los nombres de las infracciones con su ID

void loadInfractions(parkingTicketsADT t, FILE * infractionFile){
    if(infractionFile == NULL){
        freeADT(t);
        throwError("Error at opening infractions file");
    }

    fscanf(infractionFile, "%*[^\n]\n");
    
    int infractionId;
    char infractionName[MAX_CHAR_INFRACTION_NAME];

    while (fscanf(infractionFile, "%d;%30[^\n]\n", &infractionId, infractionName) == 2){
        addInfraction(t, infractionId, infractionName);
    }
}
