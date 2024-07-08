#ifndef PARKINGTICKETSADT_H
#define PARKINGTICKETSADT_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include <errno.h>

#define BLOQUE 30
#define MAX_CHAR_PLATE 11
#define MAX_CHAR_ISSUING_AGENCY 36
#define MAX_CHAR_INFRACTION_NAME 31
#define MAX_ARGS 6

/*Lista ordenada descendentemente por infractionsAmm*/
typedef struct parkingTicketsCDT * parkingTicketsADT;

typedef struct infractionNode * infractionList;

typedef struct maxPlateByInfNode * maxPlateByInfList;

typedef struct agencyNode * agencyList;

typedef struct plateNode * plateList;

// Creo un nuevo ADT que va a devolver un puntero a la estructura parkingTicketsCDT
parkingTicketsADT newADT(void);

// Funcion que recibe el archivo de tickets y guarda los datos de los tickets
// Recibe un flag que se va a modificar si hay un error en la lectura del archivo
void addInfraction(parkingTicketsADT q, int infractionId, char infractionName[]);

/* QUERIES */
void query1 (FILE * query1File, parkingTicketsADT q);

void query2 (FILE * query2File, parkingTicketsADT q);

void query3(FILE * query3file, parkingTicketsADT q);
/*QUERIES*/

// Funcion que recibe un InfractionId y depende esta suma 1 a la cantidad de tickets que tienen esa infraccion
// Si no existe la infraccion, retorna.
void sumInfractionByTicket(parkingTicketsADT q, int infractionId);

// Funcion que devuelve una lista ordenada descendentemente por la cantidad de infracciones 
infractionList getInfractionsList(parkingTicketsADT q);

// Escribe en el archivo query1File la lista de infracciones
void writeQuery1(FILE * query1File, infractionList first);

// Escribe en el archivo query2File la lista de agencias con la mayor cantidad de infracciones
void writeQuery2(FILE * query2File, agencyList l);

// Escribe en el archivo query3File la lista de patentes con la mayor cantidad de infracciones
void writeQuery3(FILE * query3File, maxPlateByInfList l);

void query2Read(parkingTicketsADT q, int infractionId, char issuingAgency[]);

void query2Processing(parkingTicketsADT q);

// Funcion que recibe un arbol de patentes, un puntero a la lista de patentes y un puntero al maximo
// Recorre el arbol y guarda en la lista las patentes que tienen la mayor cantidad de infracciones
void maxPlateFinder(plateList first, maxPlateByInfList aux, size_t * max);

void query3Read(parkingTicketsADT q, size_t infractionId, char plate[]);


maxPlateByInfList arrToListQ3(parkingTicketsADT q);

void throwError(const char * msg);

void freeQ1(infractionList l);

void freeQ3(maxPlateByInfList l);

void freeADT(parkingTicketsADT q);

#endif
