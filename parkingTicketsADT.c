#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"

typedef struct agencyNode{
    int * infractions;
    char issuingAgency[35];
    struct agencyNode * tail;
}agencyNode;

typedef struct agencyNode * agencyList;

typedef struct plateNode{
    char plate[11];
    int cant;
    struct plateNode * tail;
}plateNode;

typedef struct plateNode * plateList;

typedef struct infraction{
    plateList first;
}infraction;


struct parkingTicketsCDT
{
    /*QUERY 1*/
    int * infractionsAmm;
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList first;
    /*QUERY 2*/
    /*QUERY 3*/
    infraction * infractionPlate;
    /*QUERY 3*/
};

void 
