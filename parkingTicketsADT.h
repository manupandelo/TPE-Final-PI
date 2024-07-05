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

#define BLOQUE 20
#define MAX_CHAR_PLATE 10
#define MAX_CHAR_ISSUING_AGENCY


typedef struct data{
    char plate[MAX_CHAR_PLATE];
    char issuingAgency[MAX_CHAR_PLATE];
    size_t infractionId; 
}data;

/*Lista ordenada descendentemente por infractionsAmm*/
typedef struct q1Node{
    char infractionName[31];
    int infractionsAmm;
    struct q1 * tail;
}q1Node;

typedef q1Node * q1List;

typedef struct parkingTicketsCDT * parkingTicketsADT;

void query1Read(parkingTicketsADT q, int infractionId);

parkingTicketsADT newADT(void);

q1List arrToListQ1(parkingTicketsADT q, int infractionId, char infractionName[], q1List l);





#endif