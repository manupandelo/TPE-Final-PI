#ifndef PARKINGTICKETSADT_H
#define PARKINGTICKETSADT_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include <errno.h>

#define BLOQUE 30
#define MAX_CHAR_PLATE 11
#define MAX_CHAR_ISSUING_AGENCY 36
#define MAX_CHAR_INFRACTION_NAME 31


typedef struct ticket{
    char plate[MAX_CHAR_PLATE];
    char agency[MAX_CHAR_ISSUING_AGENCY];
    int infractionId;
    char infractionName[MAX_CHAR_INFRACTION_NAME];
}ticket;



/*Lista ordenada descendentemente por infractionsAmm*/
typedef struct q1Node{
    char infractionName[MAX_CHAR_INFRACTION_NAME];
    int infractionsAmm;
    struct q1Node * tail;
}q1Node;

typedef q1Node * q1List;

typedef struct q2Node{
    char issuingAgencyName[MAX_CHAR_ISSUING_AGENCY];
    char infractionName[MAX_CHAR_INFRACTION_NAME];
    int infractionAmm;
}q2Node;

typedef q2Node * q2List;

typedef struct parkingTicketsCDT * parkingTicketsADT;

// Creo un nuevo ADT que va a devolver un puntero a la estructura parkingTicketsCDT
parkingTicketsADT newADT(void);

// Funcion que recibe el archivo de tickets y guarda los datos de los tickets
// Recibe un flag que se va a modificar si hay un error en la lectura del archivo
void addInfraction(parkingTicketsADT q, int infractionId, char infractionName[]);

void query1Read(parkingTicketsADT q, int infractionId);

q1List arrToListQ1(parkingTicketsADT q);

void listToQ1CSV(FILE * query1File, q1List first);

void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]);

void query2Processing(parkingTicketsADT q);

void query2ToCSV(FILE * query2File, parkingTicketsADT q);

void throwError(const char * msg);

void freeADT(parkingTicketsADT q);

#endif
