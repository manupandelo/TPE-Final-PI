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
    agencyList agency;
    /*QUERY 2*/
    
    /*QUERY 3*/
    infractionIdPlateArr * infPlateArr; /*Arreglo indexado por InfractionID adentro */ 
    size_t infPlateSize;            /* tiene lista de patentes ordenadas alfabeticamente*/
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
    parkingTicketsADT new = calloc(1,sizeof(parkingTicketsCDT));
    if(new == NULL || errno == ENOMEM){
        throwError("Memory error");
    }
    return new;
}

void addInfraction(parkingTicketsADT q, int infractionId, char infractionName[]){
    if (infractionId + 1 > q->infArraySize){
        int i = q->infArraySize;
        if (infractionId + 1 > q->infArraySize + BLOQUE){ /*Si el infractionId es mayor al tamaño del array + BLOQUE, se reasigna el tamaño del array*/
            q->infArraySize = infractionId + 1;
            q->infractionArr = realloc(q->infractionArr, q->infArraySize * sizeof(infractionIdArr));
            
            if(q->infractionArr == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        }
        else{ /*Si no, se le suma BLOQUE al tamaño del array y se reasigna el tamaño*/
            q->infArraySize += BLOQUE;
            q->infractionArr = realloc(q->infractionArr, q->infArraySize * sizeof(infractionIdArr));
            
            if(q->infractionArr == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        }  
        while(i < q->infArraySize){ //Inicializo el array
            q->infractionArr[i].cant = 0;
            q->infractionArr[i++].infractionName[0] = '\0';
        }     
    }
    strcpy(q->infractionArr[infractionId].infractionName, infractionName); //Guardo el nombre de la infraccion
}

/*Funcion que suma 1 en infractionsAmm en el index del infractionId*/
void sumInfractionByTicket(parkingTicketsADT q, int infractionId){
    if (q->infArraySize <= infractionId){
        return;
    }
    q->infractionArr[infractionId].cant += 1; //Sumo 1 a la cantidad de infracciones
}

void getInfractionsListRec(infractionList next, infractionList l){
    if (next->tail == NULL || next->tail->infractionsAmm < l->infractionsAmm || ((next->tail->infractionsAmm == l->infractionsAmm) && my_strcasecmp(l->infractionName, next->tail->infractionName) < 0)){
        l->tail = next->tail; //Si la cantidad de infracciones es mayor o el nombre es menor, lo agrego ahi
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
                aux->tail = first;  //Si la cantidad de infracciones es mayor o el nombre es menor, lo agrego al principio
                first = aux;
            }else{
                getInfractionsListRec(first, aux); //Si no, lo agrego en el lugar correspondiente
            } 
        }  
    }
    return first;
    
}

/*Funcion recursiva que con la infractionList arma el CSV del query 1*/
void writeQuery1(FILE * query1File, infractionList first){
    if (first == NULL){
        return;
    }
    fprintf(query1File, "%s;%d\n", first->infractionName, first->infractionsAmm);
    writeQuery1(query1File, first->tail);
}

void query1(FILE * query1File, parkingTicketsADT q){
    infractionList listaQ1 = getInfractionsList(q); //Armo la lista de infracciones
    fprintf(query1File, "infraction;tickets\n");
    writeQuery1(query1File, listaQ1); //Escribo el CSV
    freeQ1(listaQ1); //Libero la memoria
}

static agencyList addInfByAgencyRec(agencyList l , int infractionId, char * issuingAgency){
    int cmp;
    if(l == NULL || (cmp = my_strcasecmp(l->issuingAgencyName, issuingAgency)) > 0){ //Si la agencia no existe o es mayor alfabeticamente
        agencyList aux = malloc(sizeof(agencyNode));
        if( aux == NULL || errno == ENOMEM){
            return NULL;
        }
        strcpy(aux->issuingAgencyName, issuingAgency);
        aux->infractionsArr = calloc(infractionId + 1, sizeof(size_t)); //Inicializo el array de infracciones
        if (aux->infractionsArr == NULL || errno == ENOMEM){
            free(aux);
            return NULL;
        }
        aux->tail = l;                      //Guardo la lista
        aux->arrSize = infractionId + 1;
        aux->maxArrIndex = infractionId;
        aux->infractionsArr[infractionId] += 1;
        l = aux;
    } else if(cmp == 0){ //Si la agencia ya existe
        if( infractionId >= l->arrSize){    //Si el infractionId es mayor al tamaño del array
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
            for(int i = l->maxArrIndex + 1; i < l->arrSize; i++){ //Inicializo el array de infracciones
                l->infractionsArr[i] = 0;
            }
            l->maxArrIndex = infractionId; //Guardo el maximo index
        }
        l->infractionsArr[infractionId] += 1;
        if(l->maxArrIndex < infractionId){
            l->maxArrIndex = infractionId; //Guardo el maximo index
        }
    } else {
        l->tail = addInfByAgencyRec(l->tail, infractionId, issuingAgency); //Si la agencia ya existe y es menor alfabeticamente
    }
    return l;
}


/* Funcion que busca la issuingAgnecy que corresponda por la lista sumar en el InfractionId que corresponda*/
void addInfByAgency(parkingTicketsADT q, int infractionId, char * issuingAgency){
    q->agency = addInfByAgencyRec(q->agency, infractionId, issuingAgency);
    if (q->agency == NULL){
        freeADT(q);
        throwError("Memory error");
    }
}

static agencyList getMaxInfByAgencyRec(agencyList l, infractionIdArr * arr, size_t minIndex){
    if (l == NULL){
        return NULL;
    }
    l->tail = getMaxInfByAgencyRec(l->tail, arr, minIndex); //Recorro la lista
    size_t max = 0;
    for(size_t i = minIndex; i < l->arrSize; i++){
        if(l->infractionsArr[i] > max){ //Busco la infraccion con mas tickets
            max = l->infractionsArr[i];
            strcpy(l->maxInfractionName, arr[i].infractionName);
        } else if(l->infractionsArr[i] == max && my_strcasecmp(arr[i].infractionName, l->maxInfractionName) < 0){
            strcpy(l->maxInfractionName, arr[i].infractionName);    //Si hay dos con la misma cantidad de tickets, me quedo con la que tenga el nombre menor alfabeticamente
        }
    }
    l->maxInfractionAmm = max; //Guardo la cantidad de tickets
    return l;
}

void getMaxInfByAgency(parkingTicketsADT q){
    size_t minIndex = 0;

    for(size_t i = 0; i < q->infArraySize; i++){ //Busco el primer index que tenga nombre
        if(q->infractionArr[i].infractionName[0] != '\0'){
            minIndex = i;
            break;
        }
    }

    q->agency = getMaxInfByAgencyRec(q->agency, q->infractionArr, minIndex); //Busco la infraccion con mas tickets
}

void writeQuery2(FILE * query2File, agencyList l){
    if (l == NULL){
        return;
    } 
    fprintf(query2File,"%s;%s;%zu\n",l->issuingAgencyName, l->maxInfractionName, l->maxInfractionAmm); //Escribo el CSV
    writeQuery2(query2File, l->tail);
}

void query2(FILE * query2File, parkingTicketsADT q){
    getMaxInfByAgency(q); //Busco la infraccion con mas tickets
    fprintf(query2File,"issuingAgency;infraction;tickets\n");
    writeQuery2(query2File, q->agency); //Escribo el CSV
}

static plateList addPlateTicketsByInfRec(plateList root, char * plate, int * flag){
    if (root == NULL){ /*Si no existe la patente, la agrego*/
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
    if (cmp == 0){ /*Si la patente ya existe, sumo 1 a la cantidad de infracciones*/
        root->cant += 1;
    } else if (cmp < 0){
        root->left = addPlateTicketsByInfRec(root->left, plate, flag); /*Si la patente es menor alfabeticamente, la agrego a la izquierda*/
    } else{
        root->right = addPlateTicketsByInfRec(root->right, plate, flag); /*Si la patente es mayor alfabeticamente, la agrego a la derecha*/
    }
    return root;
}

void addPlateTicketsByInf(parkingTicketsADT q, size_t infractionId, char * plate){
    /*No hace nada si la infraccion no tiene nombre*/
    if (q->infractionArr[infractionId].infractionName[0] == '\0'){
        return;
    }
    
    if(infractionId + 1 > q->infPlateSize){
        int i = q->infPlateSize;
        if( infractionId + 1 > q->infPlateSize + BLOQUE ){
            q->infPlateSize = infractionId + 1;
            q->infPlateArr = realloc(q->infPlateArr, q->infPlateSize * sizeof(infractionIdPlateArr));
            if(q->infPlateArr == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        } else {
            q->infPlateSize += BLOQUE;            
            q->infPlateArr = realloc(q->infPlateArr, q->infPlateSize * sizeof(infractionIdPlateArr));
            if(q->infPlateArr == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
        }

        while(i < q->infPlateSize){
            q->infPlateArr[i].first = NULL;
            i++;
        }
    }
    int flag = 1;
    q->infPlateArr[infractionId].first = addPlateTicketsByInfRec(q->infPlateArr[infractionId].first, plate, &flag);
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


static void getMaxPlateByInfRec(maxPlateByInfList *l, maxPlateByInfList aux){
    while (*l != NULL && my_strcasecmp((*l)->infractionName, aux->infractionName) <= 0){ 
        l = &(*l)->tail; /*Busco el lugar donde agregar la infraccion*/
    }
    aux->tail = *l; 
    *l = aux;
}

/*Busca por el arbol de patentes*/
void maxPlateFinder(plateList first, maxPlateByInfList aux, size_t * max){
    if (first == NULL){
        return;
    }
    maxPlateFinder(first->left, aux, max); /*Recorro el subarbol izquierdo*/
    if (first->cant > *max){ /*Si la cantidad de infracciones es mayor al maximo, actualizo el maximo*/
        *max = first->cant;
        strcpy(aux->maxPlateName, first->plate);
    } else if( first->cant == *max && my_strcasecmp(first->plate, aux->maxPlateName) < 0){ /*Si la cantidad de infracciones es igual al maximo, me quedo con la patente que tenga el nombre menor alfabeticamente*/
        strcpy(aux->maxPlateName, first->plate);
    }
    maxPlateFinder(first->right, aux, max); /*Recorro el subarbol derecho*/
}

/*Retorna la lista armada con los datos como corresponde para pasarla a la funcion del CSV*/
maxPlateByInfList getMaxPlateByInf(parkingTicketsADT q){
    maxPlateByInfList first = NULL;
    for (size_t i = 0; i < q->infPlateSize; i++){
        if (q->infractionArr[i].infractionName[0] != '\0'){ /*Si la infraccion tiene nombre*/
            maxPlateByInfList aux = malloc(sizeof(maxPlateByInfNode));
            if (aux == NULL || errno == ENOMEM){
                freeADT(q);
                throwError("Memory error");
            }
            aux->maxInfractionAmm = 0;
            maxPlateFinder(q->infPlateArr[i].first, aux, &aux->maxInfractionAmm); /*Busco la patente con mas infracciones*/
            strcpy(aux->infractionName, q->infractionArr[i].infractionName); /*Guardo el nombre de la infraccion*/
            if (aux->maxInfractionAmm == 0){ /*No encontro patente*/
                free(aux);
            } else {
                if (first == NULL || my_strcasecmp(first->infractionName, q->infractionArr[i].infractionName) > 0){ /*Si la infraccion es mayor alfabeticamente, la agrego al principio*/
                    aux->tail = first;
                    first = aux;           
                } else {
                    getMaxPlateByInfRec(&first->tail, aux); /*Si no, la agrego en el lugar correspondiente*/
                }
            }
        }
    }
    return first;
}

void query3(FILE * query3file, parkingTicketsADT q){
    maxPlateByInfList l = getMaxPlateByInf(q); //Armo la lista de patentes
    fprintf(query3file,"infraction;plate;tickets\n");
    writeQuery3(query3file, l); //Escribo el CSV
    freeQ3(l);            //Libero la memoria
}

void throwError(const char * msg){
    perror(msg); //Imprimo el mensaje de error
    exit(EXIT_FAILURE); 
}

static void freeRec(agencyList l){
    if (l != NULL){
        freeRec(l->tail);
        free(l->infractionsArr);
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

void freeADT(parkingTicketsADT t){
    free(t->infractionArr);
    freeRec(t->agency);
    freeRecArr(t->infPlateArr, t->infPlateSize);
    free(t);
}





