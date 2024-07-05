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
    char issuingAgencyName[36];
    int * infractionsArr;
    int arrSize;
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
    int * arrQ1; 
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList firstQ2;
    /*QUERY 2*/
    
    /*QUERY 3*/
    infraction * arrQ3;
    /*QUERY 3*/

}parkingTicketsCDT;


// Creo un nuevo ADT
parkingTicketsADT newADT(void){
    errno=0;
    parkingTicketsADT aux = calloc(1,sizeof(parkingTicketsCDT));
    if( aux == NULL || errno == ENOMEM)
        return NULL;

    return aux;
}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId*/
void query1Read(parkingTicketsADT q, int infractionId){
    if (infractionId + 1 > q->arrQ1Size)
    {
        int i = q->arrQ1Size;
        if (infractionId + 1 > q->arrQ1Size + BLOQUE)
        {
            q->arrQ1 = realloc(infractionId + 1, sizeof(int));
            q->arrQ1Size = infractionId + 1;
        }
        else{
            q->arrQ1 = realloc(q->arrQ1Size + BLOQUE, sizeof(int));
            q->arrQ1Size += BLOQUE;
        }  
        while(i < q->arrQ1Size)
        {
            q->arrQ1[i++] = 0;
        }       
    }
    q->arrQ1[infractionId] += 1;
}

/*Funcion que va recibiendo los datos del archivo de infracciones y arma la q1List*/
/*Devuelve un puntero al primero*/
q1List arrToListQ1(parkingTicketsADT q, int infractionId, char infractionName[], q1List l){

}

/*Funcion recursiva que con la q1List arma el CSV del query 1*/
static void recListToQ1CSV(FILE * query1File, q1List l){
    if (l == NULL)
    {
        return;
    }
    fprintf(query1File, "%s;%d\n", l->infractionName, l->infractionsAmm);
    recListToQ1CSV(query1File, l->tail);
    
}

/*Funcion recursiva que con la q1List arma el CSV del query 1*/
void listToQ1CSV(FILE * query1File, q1List first){
    if (first == NULL)
    {
        /*Por ahi que poner algun error, seria raro que este vacia la lista*/
        return;
    }
    fprintf(query1File, "%s;%d\n", first->infractionName, first->infractionsAmm);

    recListToQ1CSV(query1File, first->tail);
}

/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]){

    
    if (q->firstQ2 == NULL || strcmp(q->firstQ2->issuingAgencyName, issuingAgency) > 0)
    {
        agencyList aux = malloc(sizeof(agencyNode));
        if( aux == NULL || errno == ENOMEM)
            return NULL;
        strcpy(aux->issuingAgencyName, issuingAgency);
        aux->infractionsArr = calloc(infractionId + 1, sizeof(int));
        aux->tail = q->firstQ2;
        aux->arrSize = infractionId;
        q->firstQ2 = aux;
        aux->infractionsArr[infractionId] += 1;
    }

    if (strcmp(q->firstQ2->issuingAgencyName, issuingAgency) == 0)
    {
        if (q->firstQ2->arrSize < infractionId)
        {
        /* REALLOC POR BLOQUES A INFRACTIONSARR */
        /* FUNCION QUE SETEE TODOS LOS LUGARES NUEVOS DEL ARREGLO EN 0 */
        }
        q->firstQ2->infractionsArr[infractionId] += 1;
    
    }
    /* RECURSIVA QUE BUSQUE LA AGENCY */
    
}




/*Paso los datos de la lista ordenada en orden alfabetico de las agencias
a una lista (q2List) ordenada alfabeticamente por nombre de agencia con las infracciones 
mas populares por agencia
(tener en cuenta que nombre de infraccion desempata)
*/
q2List query2Processing(parkingTicketsADT q){

}



