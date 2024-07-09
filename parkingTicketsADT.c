#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include "parkingTicketsADT.h"



/* Estructuras de respuestas*/
typedef struct infractionNode{
    char infractionName[MAX_CHAR_INFRACTION_NAME];
    int infractionsAmm;
    struct infractionNode * tail;
}infractionNode;

typedef struct maxPlateByInfNode{
    char maxPlateName[MAX_CHAR_PLATE];
    char infractionName[MAX_CHAR_INFRACTION_NAME];
    size_t maxInfractionAmm;
    struct maxPlateByInfNode * tail;
}maxPlateByInfNode;
/* Estructuras de respuestas */


typedef struct agencyNode{
    char issuingAgencyName[MAX_CHAR_ISSUING_AGENCY];
    size_t * infractionsArr;
    size_t arrSize;
    size_t maxArrIndex;
    size_t maxInfractionAmm;
    char maxInfractionName[MAX_CHAR_INFRACTION_NAME];
    struct agencyNode * tail;
}agencyNode;

typedef struct plateNode{
    char plate[MAX_CHAR_PLATE];
    size_t cant; /*Cantidad de infracciones por patente*/
    struct plateNode * left;
    struct plateNode * right;
}plateNode;

typedef struct infraction{
    plateList first;
}infractionIdPlateArr;

typedef struct infractionIdArr{
    char infractionName[MAX_CHAR_INFRACTION_NAME];
    size_t cant;
}infractionIdArr;

typedef struct parkingTicketsCDT
{
    /*QUERY 1*/
    infractionIdArr * infractionArr; //Array de infracciones, despues cambio a una lista
    size_t infArraySize; //Tamaño del array de infracciones
    /*QUERY 1*/

    /*QUERY 2*/
    agencyList firstQ2;
    /*QUERY 2*/
    
    /*QUERY 3*/
    infractionIdPlateArr * arrQ3; /*Arreglo indexado por InfractionID adentro */ 
    size_t arrQ3Size;            /* tiene lista de patentes ordenadas alfabeticamente*/
    /*QUERY 3*/

}parkingTicketsCDT;

static int my_strcasecmp(const char *s1, const char *s2) {
    return strcasecmp(s1, s2);
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
    parkingTicketsADT new = calloc(1,sizeof(parkingTicketsCDT));
    if(new == NULL || errno == ENOMEM){
        throwError("Memory error");
    }

    return new;
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
void sumInfractionByTicket(parkingTicketsADT q, int infractionId){
    if (q->infArraySize <= infractionId){
        return;
    }
    q->infractionArr[infractionId].cant += 1;
}



void getInfractionsListRec(infractionList next, infractionList l){
    if (next->tail == NULL || next->tail->infractionsAmm < l->infractionsAmm || ((next->tail->infractionsAmm == l->infractionsAmm) && my_strcasecmp(l->infractionName, next->tail->infractionName) < 0))
    {
        l->tail = next->tail;
        next->tail = l;
        return;
    }
    getInfractionsListRec(next->tail, l);  
}

/*Funcion que va recibiendo los datos del archivo de infracciones y arma la infractionList*/
/*Devuelve un puntero al primero*/
infractionList getInfractionsList(parkingTicketsADT q){
    infractionList first = NULL;
    for (size_t i = 0; i < q->infArraySize; i++){
        if (q->infractionArr[i].infractionName[0] != '\0') /*Si tiene nombre lo agrego*/{
            infractionList aux = malloc(sizeof(infractionNode));
            aux->infractionsAmm = q->infractionArr[i].cant;
            strcpy(aux->infractionName, q->infractionArr[i].infractionName);
            if (first == NULL || first->infractionsAmm < aux->infractionsAmm || ((first->infractionsAmm == aux->infractionsAmm) && my_strcasecmp(aux->infractionName, first->infractionName) < 0)){
                aux->tail = first;
                first = aux;
            }else{
                getInfractionsListRec(first, aux);
            } 
        }  
    }
    return first;
    
}

/*Funcion recursiva que con la infractionList arma el CSV del query 1*/
void writeQuery1(FILE * query1File, infractionList first){
    if (first == NULL){
        return;  /*Por ahi que poner algun error, seria raro que este vacia la lista*/
    }

    fprintf(query1File, "%s;%d\n", first->infractionName, first->infractionsAmm);

    writeQuery1(query1File, first->tail);
}

void query1(FILE * query1File, parkingTicketsADT q){
    infractionList listaQ1 = getInfractionsList(q);
    writeQuery1(query1File, listaQ1);
    freeQ1(listaQ1);
}

static agencyList query2ReadRec(agencyList l , int infractionId, char * issuingAgency){
    int cmp;
    if(l == NULL || (cmp = my_strcasecmp(l->issuingAgencyName, issuingAgency)) > 0){
        agencyList aux = malloc(sizeof(agencyNode));
        if( aux == NULL || errno == ENOMEM){
            return NULL;
        }
        strcpy(aux->issuingAgencyName, issuingAgency);
        aux->infractionsArr = calloc(infractionId + 1, sizeof(size_t));
        if (aux->infractionsArr == NULL || errno == ENOMEM){
            free(aux);
            return NULL;
        }
        aux->tail = l;
        aux->arrSize = infractionId + 1;
        aux->maxArrIndex = infractionId;
        aux->infractionsArr[infractionId] += 1;
        l = aux;
    } else if(cmp == 0){
        if( infractionId >= l->arrSize){
            if(infractionId +1 > l->arrSize + BLOQUE){
                l->arrSize = infractionId + 1;
                l->infractionsArr = realloc(l->infractionsArr, l->arrSize * sizeof(size_t));
                if(l->infractionsArr == NULL || errno == ENOMEM){
                    return NULL;
                }
            } else {
                l->arrSize += BLOQUE;
                l->infractionsArr = realloc(l->infractionsArr, l->arrSize * sizeof(size_t));
                if(l->infractionsArr == NULL || errno == ENOMEM){
                    return NULL;
                }
            }
            for(int i = l->maxArrIndex + 1; i < l->arrSize; i++){
                l->infractionsArr[i] = 0;
            }
            l->maxArrIndex = infractionId;
        }
        l->infractionsArr[infractionId] += 1;
        if(l->maxArrIndex < infractionId){
            l->maxArrIndex = infractionId;
        }
    } else {
        l->tail = query2ReadRec(l->tail, infractionId, issuingAgency);
    }
    return l;
}


/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void query2Read(parkingTicketsADT q, int infractionId, char * issuingAgency){
    q->firstQ2 = query2ReadRec(q->firstQ2, infractionId, issuingAgency);
    if (q->firstQ2 == NULL){
        freeADT(q);
        throwError("Memory error");
    }
}


/*Encuentra la maxima infraccion por issuing agency la pone en maxInfractionName
y maxInfractionAmm.
si empatan se define por el nombre, usar el arreglo del query 1 para esto*/

static agencyList query2ProcessingRec(agencyList l, infractionIdArr * arr, size_t minIndex){
    if (l == NULL){
        return NULL;
    }
    l->tail = query2ProcessingRec(l->tail, arr, minIndex);
    size_t max = 0;
    for(size_t i = minIndex; i < l->arrSize; i++){
        if(l->infractionsArr[i] > max){
            max = l->infractionsArr[i];
            strcpy(l->maxInfractionName, arr[i].infractionName);
        } else if(l->infractionsArr[i] == max && my_strcasecmp(arr[i].infractionName, l->maxInfractionName) < 0){
            strcpy(l->maxInfractionName, arr[i].infractionName);
        }
    }
    l->maxInfractionAmm = max;
    return l;
}

void query2Processing(parkingTicketsADT q){
    size_t minIndex = 0;
    for(size_t i = 0; i < q->infArraySize; i++){
        if(q->infractionArr[i].infractionName[0] != '\0'){
            minIndex = i;
            break;
        }
    }

    q->firstQ2 = query2ProcessingRec(q->firstQ2, q->infractionArr, minIndex);
}

void writeQuery2(FILE * query2File, agencyList l){
    if (l == NULL){
        return;
    }
    fprintf(query2File,"%s;%s;%zu\n",l->issuingAgencyName, l->maxInfractionName, l->maxInfractionAmm);
    writeQuery2(query2File, l->tail);
}


void query2(FILE * query2File, parkingTicketsADT q){
    query2Processing(q);
    writeQuery2(query2File, q->firstQ2);
}



static plateList recQuery3Read(plateList root, char * plate, int * flag){
    if (root == NULL){
        plateList aux = malloc(sizeof(plateNode));
        if (aux == NULL || errno == ENOMEM){
            *flag = 0;
            return NULL;
        }
        strcpy(aux->plate, plate);
        aux->cant = 1;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    }
    int cmp = my_strcasecmp(plate, root->plate);
    if (cmp == 0){
        root->cant += 1;
    } else if (cmp < 0){
        root->left = recQuery3Read(root->left, plate, flag);
    } else{
        root->right = recQuery3Read(root->right, plate, flag);
    }
    return root;
}

void query3Read(parkingTicketsADT q, size_t infractionId, char plate[]){
    /*No hace nada si la infraccion no tiene nombre*/
    if (q->infractionArr[infractionId].infractionName[0] == '\0'){
        return;
    }
    
    if(infractionId + 1 > q->arrQ3Size){
        int i = q->arrQ3Size;
        if( infractionId + 1 > q->arrQ3Size + BLOQUE ){
            q->arrQ3Size = infractionId + 1;
            q->arrQ3 = realloc(q->arrQ3, q->arrQ3Size * sizeof(infractionIdPlateArr));
            if(q->arrQ3 == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        } else {
            q->arrQ3Size += BLOQUE;            
            q->arrQ3 = realloc(q->arrQ3, q->arrQ3Size * sizeof(infractionIdPlateArr));
            if(q->arrQ3 == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        }

        while(i < q->arrQ3Size){
            q->arrQ3[i].first = NULL;
            i++;
        }
    }
    int flag = 1;
    q->arrQ3[infractionId].first = recQuery3Read(q->arrQ3[infractionId].first, plate, &flag);
    if(flag == 0){
        freeADT(q);
        throwError("Memory error");
    }
}

void writeQuery3(FILE * query3File, maxPlateByInfList l){
    if (l == NULL){
        return;
    }
    fprintf(query3File,"%s;%s;%zu\n",l->infractionName, l->maxPlateName, l->maxInfractionAmm);
    writeQuery3(query3File, l->tail);
}


void recArrToListQuery3(maxPlateByInfList *l, maxPlateByInfList aux){
    while (*l != NULL && my_strcasecmp((*l)->infractionName, aux->infractionName) <= 0) {
        l = &(*l)->tail;
    }
    aux->tail = *l;
    *l = aux;
}

/*Busca por el arbol de patentes*/
void maxPlateFinder(plateList first, maxPlateByInfList aux, size_t * max){
    if (first == NULL){
        return;
    }
    maxPlateFinder(first->left, aux, max);
    if (first->cant > *max){
        *max = first->cant;
        strcpy(aux->maxPlateName, first->plate);
    } else if( first->cant == *max && my_strcasecmp(first->plate, aux->maxPlateName) < 0){
        strcpy(aux->maxPlateName, first->plate);
    }
    maxPlateFinder(first->right, aux, max);
}

/*Retorna la lista armada con los datos como corresponde para pasarla a la funcion del CSV*/
maxPlateByInfList arrToListQ3(parkingTicketsADT q){
    maxPlateByInfList first = NULL;
    for (size_t i = 0; i < q->arrQ3Size; i++){
        if (q->infractionArr[i].infractionName[0] != '\0'){
            maxPlateByInfList aux = malloc(sizeof(maxPlateByInfNode));
            if (aux == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
            aux->maxInfractionAmm = 0;
            maxPlateFinder(q->arrQ3[i].first, aux, &aux->maxInfractionAmm);
            strcpy(aux->infractionName, q->infractionArr[i].infractionName);
            if (aux->maxInfractionAmm == 0){ /*No encontro patente*/
                free(aux);
            } else {
                if (first == NULL || my_strcasecmp(first->infractionName, q->infractionArr[i].infractionName) > 0){
                    aux->tail = first;
                    first = aux;           
                } else {
                    recArrToListQuery3(&first->tail, aux); 
                }
            }
        }
    }
    return first;
}

void query3(FILE * query3file, parkingTicketsADT q){
    maxPlateByInfList l = arrToListQ3(q);
    writeQuery3(query3file, l);
    freeQ3(l);    
}

void throwError(const char * msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

static void freeRec(agencyList l){
    if (l != NULL){
        freeRec(l->tail);
        free(l);
    }
}

void freeQ1(infractionList l){
    if (l != NULL){
        freeQ1(l->tail);
        free(l);
    }
}

void freeQ3(maxPlateByInfList l){
    if (l != NULL){
        freeQ3(l->tail);
        free(l);
    }
}

static void freePlateList(plateList l){
    if (l != NULL){
        freePlateList(l->left);
        freePlateList(l->right);
        free(l);
    }
}

static void freeRecArr(infractionIdPlateArr * arr, size_t size){
    for (size_t i = 0; i < size; i++){
        freePlateList(arr[i].first);
    }
    free(arr);
}

static void freeArr(infractionIdArr * arr, size_t size){
    for (size_t i = 0; i < size; i++){
        if (arr[i].infractionName[0] != '\0')
            free(arr[i].infractionName);
    }
    free(arr);
} 

void freeADT(parkingTicketsADT t){
    freeArr(t->infractionArr, t->infArraySize);
    freeRec(t->firstQ2);
    freeRecArr(t->arrQ3, t->arrQ3Size);
    free(t);
}





