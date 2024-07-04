#ifndef QUERY1ADT_H
#define QUERY1ADT_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>

typedef struct data{
    char plate[11];
    char issuingAgency[35];
    int infractionId; 
}data;

typedef struct parkingTicketsCDT * parkingTicketsADT;

void query1Read(parkingTicketsADT q, int infractionId);
parkingTicketsADT newADT(void);


#endif