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

typedef struct agency * agencyList;

struct parkingTicketsCDT
{
    /*QUERY 1*/
    int * infractionsAmm;
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList first;
    /*QUERY 2*/
};

void 
