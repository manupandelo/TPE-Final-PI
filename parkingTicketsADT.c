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
}infractionIdPlateArr;

typedef struct infractionIdArr{
    int infractionAmm;
    char infractionName[31];
}infractionIdArr;

typedef struct parkingTicketsCDT
{
    /*QUERY 1*/
    infractionIdArr * arrQ1; 
    size_t arrQ1Size;
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList firstQ2;
    /*QUERY 2*/
    
    /*QUERY 3*/
    infractionIdPlateArr * arrQ3;
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

void infractionIdToName(parkingTicketsADT q, int infractionId, char infractionName[]){
    if (infractionId + 1 > q->arrQ1Size)
    {
        int i = q->arrQ1Size;
        if (infractionId + 1 > q->arrQ1Size + BLOQUE)
        {
            q->arrQ1Size = infractionId + 1;
            q->arrQ1 = realloc(q->arrQ1, q->arrQ1Size * sizeof(infractionIdArr));
            /*HAY QUE VALIDARLOS*/
            
        }
        else{
            q->arrQ1Size += BLOQUE;
            q->arrQ1 = realloc(q->arrQ1, q->arrQ1Size * sizeof(infractionIdArr));
            /*HAY QUE VALIDARLOS*/
            
        }  
        while(i < q->arrQ1Size)
        {
            q->arrQ1[i].infractionAmm = 0;
            q->arrQ1[i++].infractionName[0] = '\0';
        }       
    }
    strcpy(q->arrQ1[infractionId].infractionName, infractionName);
}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId*/
void query1Read(parkingTicketsADT q, int infractionId){
    if (q->arrQ1Size <= infractionId)
    {
        return;
    }
    q->arrQ1[infractionId].infractionAmm += 1;
}



void recArrToListQ1(q1List next, q1List l){
    if (next->tail == NULL || next->tail->infractionsAmm < l->infractionsAmm || ((next->tail->infractionsAmm == l->infractionsAmm) && strcmp(l->infractionName, next->tail->infractionName) < 0))
    {
        l->tail = next->tail;
        next->tail = l;
        return;
    }
    recArrToListQ1(next->tail, l);  
}
/*Funcion que va recibiendo los datos del archivo de infracciones y arma la q1List*/
/*Devuelve un puntero al primero*/

q1List arrToListQ1(parkingTicketsADT q){
    q1List first = NULL;
    for (size_t i = 0; i < q->arrQ1Size; i++)
    {
        if (q->arrQ1[i].infractionName[0] != '\0') /*Si tiene nombre lo agrego*/
        {
            q1List aux = malloc(sizeof(q1Node));
            aux->infractionsAmm = q->arrQ1[i].infractionAmm;
            strcpy(aux->infractionName, q->arrQ1[i].infractionName);
            if (first == NULL || first->infractionsAmm < aux->infractionsAmm || ((first->infractionsAmm == aux->infractionsAmm) && strcmp(aux->infractionName, first->infractionName) < 0))
            {
                aux->tail = first;
                first = aux;
            }else{
                recArrToListQ1(first, aux);
            }
            
        }  
    }
    return first;
    
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





