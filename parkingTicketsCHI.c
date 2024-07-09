#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"

typedef struct ticket{
    char plate[MAX_CHAR_PLATE];
    char agency[MAX_CHAR_ISSUING_AGENCY];
    int infractionId;
    char infractionName[MAX_CHAR_INFRACTION_NAME];
}ticket;

void loadInfractions(parkingTicketsADT t, FILE * infractionFile);

void loadTickets(parkingTicketsADT t, FILE * ticketFile);

int main(int argc, char const *argv[])
{
    if (argc != MAX_ARGS)
        throwError("Error en la cantidad de argumentos");
    parkingTicketsADT tickets = newADT();

    /*Lectura del file de infracciones*/
    FILE * infractionFile = fopen(argv[2], "r");
    if (!infractionFile) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    loadInfractions(tickets, infractionFile);
    fclose(infractionFile);
    /*Lectura del file de infracciones*/

    /*Lectura del file de los tickets*/
    FILE * ticketFile = fopen(argv[1], "r");
    loadTickets(tickets, ticketFile);
    fclose(ticketFile);
    /*Lectura del file de los tickets*/

    /*Resuelvo query1*/
    FILE * query1CSV = fopen(argv[3],"w");
    if (query1CSV == NULL) {
        freeADT(tickets);
        throwError("Error opening file for writing");
    }
    query1(query1CSV, tickets);
    fclose(query1CSV);
    /*Resuelvo query1*/

    /*Resuelvo query2*/
    FILE * query2CSV = fopen(argv[4],"w");
    if (query2CSV == NULL) {
        throwError("Error opening file for writing");
    } else {
        query2(query2CSV, tickets);
        fclose(query2CSV);
    }
    /*Resuelvo query2*/
    
    
    /*Resuelvo query3*/
    FILE * query3CSV = fopen(argv[5],"w");
    if (query3CSV == NULL) {
        freeADT(tickets);
        throwError("Error opening file for writing");
    } else {
        query3(query3CSV, tickets);
        fclose(query3CSV);
    }
    /*Resuelvo query3*/
    return 0;
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

    while (fscanf(infractionFile, "%d;%50[^\n]\n", &infractionId, infractionName) == 2){
        addInfraction(t, infractionId, infractionName);
    }
}

//Funcion que recibe el archivo de tickets y guarda los datos de los tickets
void loadTickets(parkingTicketsADT t, FILE * ticketFile){
    if(ticketFile == NULL){
        freeADT(t);
        throwError("Error at opening tickets file");
    }

    ticket fine;

    fscanf(ticketFile, "%*[^\n]\n");
    while (fscanf(ticketFile, "%*[^;];%10[^;];%13[^;];%d;%*[^\n]\n", fine.plate, fine.agency, &fine.infractionId) == 3){
        sumInfractionByTicket(t, fine.infractionId);
        query2Read(t, fine.infractionId, fine.agency);
        query3Read(t, fine.infractionId, fine.plate); 
    }
}
