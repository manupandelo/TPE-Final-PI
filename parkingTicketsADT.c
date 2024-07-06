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
    char infractionName[MAX_CHAR_INFRACTION_NAME];
    size_t cant;
}infractionIdArr;

typedef struct parkingTicketsCDT
{
    infractionIdArr * infractionArr; //Array de infracciones, despues cambio a una lista
    size_t infArraySize; //Tamaño del array de infracciones
    

    /*QUERY 2*/
    agencyList firstQ2;
    /*QUERY 2*/
    
    /*QUERY 3*/
    infractionIdPlateArr * arrQ3;
    /*QUERY 3*/

}parkingTicketsCDT;


// Creo un nuevo ADT
parkingTicketsADT newADT(void){
    return calloc(1,sizeof(parkingTicketsCDT));
}

void addInfraction(parkingTicketsADT q, int infractionId, char infractionName[], int * flag){
    if (infractionId +1 > q->infArraySize)
    {
        int i = q->infArraySize;
        if (infractionId + 1 > q->infArraySize + BLOQUE)
        {
            q->infArraySize = infractionId + 1;
            q->infractionArr = realloc(q->infractionArr, q->infArraySize * sizeof(infractionIdArr));
            
            if(q->infractionArr == NULL || errno == ENOMEM)
                *flag = 0;
        }
        else{
            q->infArraySize += BLOQUE;
            q->infractionArr = realloc(q->infractionArr, q->infArraySize * sizeof(infractionIdArr));
            
            if(q->infractionArr == NULL || errno == ENOMEM)
                *flag = 0;
            
        }  
        while(i < q->infArraySize){
            q->infractionArr[i].cant = 0;
            q->infractionArr[i++].infractionName[0] = '\0';
        }     
    }
    strcpy(q->infractionArr[infractionId].infractionName, infractionName);
}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId*/
void query1Read(parkingTicketsADT q, int infractionId){
    if (q->infArraySize <= infractionId){
        return;
    }
    q->infractionArr[infractionId].cant += 1;
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
    for (size_t i = 0; i < q->infArraySize; i++)
    {
        if (q->infractionArr[i].infractionName[0] != '\0') /*Si tiene nombre lo agrego*/
        {
            q1List aux = malloc(sizeof(q1Node));
            aux->infractionsAmm = q->infractionArr[i].cant;
            strcpy(aux->infractionName, q->infractionArr[i].infractionName);
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

void throwError(const char * msg){
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

static void freeRec(q1List l){
    if (l != NULL){
        freeRec(l->tail);
        free(l);
    }
}

void freeADT(parkingTicketsADT t){
    free(t->infractionArr);
    free(t->arrQ3);
    freeRec(t->firstQ2);
    free(t);
}





