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


typedef struct data{
    char plate[MAX_CHAR_PLATE];
    char issuingAgency[MAX_CHAR_ISSUING_AGENCY];
    int infractionId;
    char infractionName[MAX_CHAR_INFRACTION_NAME]; 
}data;

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

parkingTicketsADT newADT(void);

void infractionIdToName(parkingTicketsADT q, int infractionId, char infractionName[]);

void query1Read(parkingTicketsADT q, int infractionId);

q1List arrToListQ1(parkingTicketsADT q);

void listToQ1CSV(FILE * query1File, q1List first);



#endif