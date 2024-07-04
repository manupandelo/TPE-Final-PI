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

parkingTicketsADT newADT(void){

}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId - 1*/
void query1Read(parkingTicketsADT q, int infractionId){

}

/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]){

}





