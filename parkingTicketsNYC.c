#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"


int main(int argc, char const *argv[])
{
    if (argc != 4)
        throwError("Error en la cantidad de argumentos");
    parkingTicketsADT tickets = newADT();
    if (tickets == NULL)
        throwError("Error al reservar memoria");
    ticket fine;

    /*Lectura del file de infracciones*/
    FILE * infractionFile = fopen(argv[2], "r");
    if (!infractionFile) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fscanf(infractionFile, "%*[^\n]\n");
    int flag = 1;
    while (fscanf(infractionFile, "%d;%30[^\n]", &fine.infractionId, fine.infractionName ) == 2)
    {
        addInfraction(tickets, fine.infractionId, fine.infractionName, flag);
        /*VALIDAR LO DEL FLAG*/
    }
    fclose(infractionFile);
    /*Lectura del file de infracciones*/

    /*Lectura del file de los tickets*/
    FILE * ticketFile = fopen(argv[1], "r");
    if (ticketFile == NULL) {
        freeADT(tickets);
        throwError("Error at opening tickets file");
    }
    fscanf(ticketFile, "%*[^\n]\n");
    while (fscanf(ticketFile, "%10[^;];%*[^;];%d;%*[^;];%35[^\n]\n", fine.plate, &fine.infractionId, fine.infractionName) == 3){
        query1Read(tickets, fine.infractionId);
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
}


//Funcion que recibe el archivo de infracciones y guarda los nombres de las infracciones con su ID

void loadInfractions(parkingTicketsADT t, const char * infractionPath){
    FILE * infractionFile = fopen(infractionPath, "r");
    if(infractionFile == NULL){
        freeADT(t);
        throwError("Error at opening infractions file");
    }

    fscanf(infractionFile, "%*[^\n]\n");

    int flag = 1;
    int infractionId;
    char infractionName[MAX_CHAR_INFRACTION_NAME];

    while (fscanf(infractionFile, "%d;%30[^\n]\n", &infractionId, infractionName) == 2 && flag){
        addInfraction(t, infractionId, infractionName, &flag);
    }

    fclose(infractionFile);
    
    if(flag == 0){
        freeADT(t);
        throwError("Memory error");
    }
}