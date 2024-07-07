#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "parkingTicketsADT.h"

/*Lista ordenada alfabeticamente por nombre de agencia
con arreglo indexado por infractionId.
Tambien contiene el maximo infraction ammount
y el nombre de dicha infraccion*/
typedef struct agencyNode{
    char issuingAgencyName[MAX_CHAR_ISSUING_AGENCY];
    size_t * infractionsArr;
    size_t arrSize;
    size_t maxArrIndex;
    size_t maxInfractionAmm;
    char maxInfractionName[MAX_CHAR_INFRACTION_NAME];
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

static int my_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}


// Creo un nuevo ADT
parkingTicketsADT newADT(void){
    return calloc(1,sizeof(parkingTicketsCDT));
}

void addInfraction(parkingTicketsADT q, int infractionId, char infractionName[]){
    if (infractionId + 1 > q->infArraySize)
    {
        int i = q->infArraySize;
        if (infractionId + 1 > q->infArraySize + BLOQUE)
        {
            q->infArraySize = infractionId + 1;
            q->infractionArr = realloc(q->infractionArr, q->infArraySize * sizeof(infractionIdArr));
            
            if(q->infractionArr == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        }
        else{
            q->infArraySize += BLOQUE;
            q->infractionArr = realloc(q->infractionArr, q->infArraySize * sizeof(infractionIdArr));
            
            if(q->infractionArr == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
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
    if (next->tail == NULL || next->tail->infractionsAmm < l->infractionsAmm || ((next->tail->infractionsAmm == l->infractionsAmm) && my_strcasecmp(l->infractionName, next->tail->infractionName) < 0))
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
            if (first == NULL || first->infractionsAmm < aux->infractionsAmm || ((first->infractionsAmm == aux->infractionsAmm) && my_strcasecmp(aux->infractionName, first->infractionName) < 0))
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
void listToQ1CSV(FILE * query1File, q1List first){
    if (first == NULL){
        return;  /*Por ahi que poner algun error, seria raro que este vacia la lista*/
    }

    fprintf(query1File, "%s;%d\n", first->infractionName, first->infractionsAmm);

    listToQ1CSV(query1File, first->tail);
}


static void recQuery2Read(agencyList next, int infractionId, char issuingAgency[], int * flag){
    if (next->tail == NULL ||  my_strcasecmp(next->tail->issuingAgencyName, issuingAgency) > 0)
    {
        agencyList aux = malloc(sizeof(agencyNode));
        if( aux == NULL || errno == ENOMEM){
            *flag = 0; // devuelvo una flag si hubo un error para despues hacer free del ADT
            return;
        }
        strcpy(aux->issuingAgencyName, issuingAgency);
        aux->infractionsArr = calloc(infractionId + 1, sizeof(size_t));
        aux->tail = next->tail;
        next->tail = aux;
        aux->arrSize = infractionId + 1;
        aux->infractionsArr[infractionId] += 1;
        aux->maxArrIndex = infractionId;
        return;
    }
    
    if (my_strcasecmp(next->tail->issuingAgencyName, issuingAgency) == 0)
    {
        if (infractionId >= next->tail->arrSize)
        {
            int i = next->tail->arrSize;
            if (infractionId + 1 > next->tail->arrSize + BLOQUE)
            {
                next->tail->arrSize = infractionId + 1;
                next->tail->infractionsArr = realloc(next->tail->infractionsArr, next->tail->arrSize * sizeof(size_t));
                if(next->tail->infractionsArr == NULL || errno == ENOMEM){
                    *flag = 0;
                    return;
                }
                
            }
            else{
                next->tail->arrSize = next->tail->arrSize + BLOQUE;
                next->tail->infractionsArr = realloc(next->tail->infractionsArr, next->tail->arrSize * sizeof(size_t));
                if(next->tail->infractionsArr == NULL || errno == ENOMEM){
                    *flag = 0;
                    return;
                }
            }
              
            while(i < next->tail->arrSize){
                next->tail->infractionsArr[i++] = 0;
            }
            next->tail->infractionsArr[infractionId] += 1;
            next->tail->maxArrIndex = infractionId;
            return;
        }
        next->tail->infractionsArr[infractionId] += 1;
        if (next->tail->maxArrIndex < infractionId)
        {
            next->tail->maxArrIndex = infractionId;
        }
        return;
    }
    recQuery2Read(next->tail, infractionId, issuingAgency,flag);
    return;
}

/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]){
    if (q->firstQ2 == NULL || my_strcasecmp(q->firstQ2->issuingAgencyName, issuingAgency) > 0)
    {
        agencyList aux = malloc(sizeof(agencyNode));
        if( aux == NULL || errno == ENOMEM){
            freeADT(q);
            throwError("Memory error");
        }
        strcpy(aux->issuingAgencyName, issuingAgency);
        aux->infractionsArr = calloc(infractionId + 1, sizeof(size_t));
        if (aux->infractionsArr == NULL || errno == ENOMEM){
            freeADT(q);
            throwError("Memory error");
        }
        aux->tail = q->firstQ2;
        aux->arrSize = infractionId + 1;
        q->firstQ2 = aux;
        aux->infractionsArr[infractionId] += 1;
        return;
    }

    if (my_strcasecmp(q->firstQ2->issuingAgencyName, issuingAgency) == 0)
    {
        if (q->firstQ2->arrSize <= infractionId)
        {
            int i = q->firstQ2->arrSize;
            if (infractionId + 1 > q->firstQ2->arrSize + BLOQUE)
            {
                q->firstQ2->arrSize = infractionId + 1;
                q->firstQ2->infractionsArr = realloc(q->firstQ2->infractionsArr, q->firstQ2->arrSize * sizeof(size_t));
                if(q->firstQ2->infractionsArr == NULL || errno == ENOMEM){
                    freeADT(q);
                    throwError("Memory error");
                }
                
            }
            else{
                q->firstQ2->arrSize = q->firstQ2->arrSize + BLOQUE;
                q->firstQ2->infractionsArr = realloc(q->firstQ2->infractionsArr, q->firstQ2->arrSize * sizeof(size_t));
                if(q->firstQ2->infractionsArr == NULL || errno == ENOMEM){
                    freeADT(q);
                    throwError("Memory error");
                }
            } 

            while(i < q->firstQ2->arrSize){
                q->firstQ2->infractionsArr[i++] = 0;
            }
            q->firstQ2->infractionsArr[infractionId] += 1;
            q->firstQ2->maxArrIndex = infractionId;
            return;
        }
        q->firstQ2->infractionsArr[infractionId] += 1;
        if (q->firstQ2->maxArrIndex < infractionId)
        {
            q->firstQ2->maxArrIndex = infractionId;
        }
        return;
    
    }
    int flag = 1;
    recQuery2Read(q->firstQ2, infractionId, issuingAgency, &flag);
    if(flag == 0){
        freeADT(q);
        throwError("Memory error");
    }

    
}


/*Encuentra la maxima infraccion por issuing agency la pone en maxInfractionName
y maxInfractionAmm.
si empatan se define por el nombre, usar el arreglo del query 1 para esto*/

static void query2ProcessingRec(agencyList l, infractionIdArr * arr){
    if(l==NULL)
        return ;

    size_t idxMayor;
    /*Busco un index mayor valido (con nombre)*/
    for (size_t i = 0; i < l->maxArrIndex; i++)
    {
        if (arr[i].infractionName[0] != '\0')
        {
            idxMayor = i;
            break;
        }
        
    }
    
    for(size_t i = idxMayor + 1; i < l->maxArrIndex; i++ ){
        if(arr[i].infractionName[0] != '\0'){
                if(l->infractionsArr[i] > l->infractionsArr[idxMayor]){
                    idxMayor = i;
                } else if(l->infractionsArr[i] == l->infractionsArr[idxMayor]){
                    if(my_strcasecmp(arr[idxMayor].infractionName ,arr[i].infractionName)>0){
                    idxMayor = i;
                }
            }
        }
    }
    l->maxInfractionAmm = l->infractionsArr[idxMayor];
    strcpy(l->maxInfractionName, arr[idxMayor].infractionName);
    query2ProcessingRec(l->tail, arr);
}

void query2Processing(parkingTicketsADT q){
    query2ProcessingRec(q->firstQ2, q->infractionArr);
}

static void recQuery2ToCSV(FILE * query2File, agencyList l){
    if (l == NULL){
        return;
    }
    fprintf(query2File,"%s;%s;%d\n",l->issuingAgencyName, l->maxInfractionName, l->maxInfractionAmm);
    recQuery2ToCSV(query2File, l->tail);
}

void query2ToCSV(FILE * query2File, parkingTicketsADT q){
    if (q->firstQ2 == NULL){
        return;
    }
    fprintf(query2File,"%s;%s;%d\n",q->firstQ2->issuingAgencyName, q->firstQ2->maxInfractionName, q->firstQ2->maxInfractionAmm);
    recQuery2ToCSV(query2File, q->firstQ2->tail);
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
    for(int i = 0; i<t->infArraySize; i++){
        free(t->infractionArr[i].infractionName);
    }
    free(t->infractionArr);
    free(t->arrQ3);
    freeRec(t->firstQ2);
    free(t);
}





