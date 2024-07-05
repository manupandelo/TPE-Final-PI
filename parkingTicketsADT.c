#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"

typedef struct agencyNode{
    char issuingAgencyName[36];
    int * infractionsArr;
    int arrSize;
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
    int * arrQ1; 
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList firstQ2;
    /*QUERY 2*/
    /*QUERY 3*/
    infraction * arrQ3;
    /*QUERY 3*/
};

parkingTicketsADT newADT(void){

}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId - 1*/
void query1Read(parkingTicketsADT q, int infractionId){

}

/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]){

    
    if (q->firstQ2 == NULL || strcmp(q->firstQ2->issuingAgencyName, issuingAgency) > 0)
    {
        agencyList aux = malloc(sizeof(agencyNode));
        strcpy(aux->issuingAgencyName, issuingAgency);
        aux->infractionsArr = calloc(infractionId, sizeof(int));
        aux->tail = q->firstQ2;
        aux->arrSize = infractionId;
        q->firstQ2 = aux;
        aux->infractionsArr[infractionId - 1] += 1;
    }

    if (strcmp(q->firstQ2->issuingAgencyName, issuingAgency) == 0)
    {
        if (q->firstQ2->arrSize < infractionId - 1)
        {
        /* REALLOC POR BLOQUES A INFRACTIONSARR */
        /* FUNCION QUE SETEE TODOS LOS LUGARES NUEVOS DEL ARREGLO EN 0 */
        }
        q->firstQ2->infractionsArr[infractionId - 1] += 1;
    
    }
    /* RECURSIVA QUE BUSQUE LA AGENCY */
    
}





