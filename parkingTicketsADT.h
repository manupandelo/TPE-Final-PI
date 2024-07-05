#ifndef QUERY1ADT_H
#define QUERY1ADT_H

#include <stdio.h>

#define BLOQUE 20
#define MAX_CHAR_PLATE 10
#define MAX_CHAR_ISSUING_AGENCY
typedef struct data{
    char plate[MAX_CHAR_PLATE];
    char issuingAgency[MAX_CHAR_PLATE];
    size_t infractionId; 
}data;

typedef struct parkingTicketsCDT * parkingTicketsADT;

void query1Read(parkingTicketsADT q, int infractionId);

parkingTicketsADT newADT(void);


#endif