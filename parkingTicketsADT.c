#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "parkingTicketsADT.h"

typedef struct agencyNode{
    size_t * infractions;
    char issuingAgency[35];
    struct agencyNode * tail;
}agencyNode;

typedef struct agencyNode * agencyList;

typedef struct plateNode{
    char plate[11];
    size_t cant;
    struct plateNode * tail;
}plateNode;

typedef struct plateNode * plateList;

typedef struct infraction{
    plateList first;
}infraction;


typedef struct parkingTicketsCDT
{
    /*QUERY 1*/
    size_t * infractionsAmm;
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList first;
    /*QUERY 2*/
    
    /*QUERY 3*/
    infraction * infractionPlate;
    /*QUERY 3*/

} parkingTicketsCDT;

parkingTicketsADT newADT(void){
    errno=0;
    parkingTicketsADT aux = calloc(1,sizeof(parkingTicketsCDT));
    if( aux == NULL || errno == ENOMEM)
        return NULL;

    return aux;
}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId - 1*/
void query1Read(parkingTicketsADT q, int infractionId){

}

/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]){

}





