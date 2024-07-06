#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"

void loadInfractions(parkingTicketsADT q, const char * infractionPath);
/*
Para omitir la primera línea del archivo (que contiene el encabezado), 
puedes usar fgets para leer y descartar la primera línea antes de comenzar
a usar fscanf para leer los datos. Aquí hay una manera de hacerlo:
    char header[256];
    fgets(header, sizeof(header), file);
*/


int main(int argc, char const *argv[]){
    if (argc != 4)
        throwError("Error en la cantidad de argumentos");

    const char * infractionPath = argv[2];
    const char * ticketPath = argv[1];

    parkingTicketsADT tickets = newADT();

    if (tickets == NULL)
        throwError("Error al reservar memoria");
    
    /*Leo el file de las infracciones y me guardo las infracciones correspondientes
    con su ID*/
    loadInfractions(tickets, infractionPath);
    
    /*Leo el file de los tickets*/
    ticket fine;
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
    q1List listaQ1 = arrToListQ1(tickets);
    
    FILE * query1CSV = fopen(argv[3], "w");
    if (!query1CSV) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    
    listToQ1CSV(query1CSV, listaQ1);

    freeADT(tickets);
    return 0;
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