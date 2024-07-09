#ifndef PARKINGTICKETSADT_H
#define PARKINGTICKETSADT_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#define BLOQUE 30
#define MAX_CHAR_PLATE 11
#define MAX_ARGS 6
#include "config.h"

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

// Funcion que recibe un InfractionId y depende esta sumaa 1 a la cantidad de tickets que tienen esa infraccion
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

//Recibe el id de Infraccion y la agencia que la emitio, si la agencia no existe la agrega
//Si la agencia existe, suma 1 a la cantidad de tickets que tiene dicha infraccion
void addInfByAgency(parkingTicketsADT q, int infractionId, char * issuingAgency);

void getMaxInfByAgency(parkingTicketsADT q);

// Funcion que recibe un arbol de patentes, un puntero a la lista de patentes y un puntero al maximo
// Recorre el arbol y guarda en la lista las patentes que tienen la mayor cantidad de infracciones
void maxPlateFinder(plateList first, maxPlateByInfList aux, size_t * max);

// Funcion que recibe un id de infraccion y una patente, si la patente no existe la agrega
// Si la patente existe, suma 1 a la cantidad de infracciones que tiene
void addPlateTicketsByInf(parkingTicketsADT q, size_t infractionId, char * plate);

// Funcion que devuelve una lista ordenada alfabeticamente por el nombre de la infraccion
// con la patente que tiene la mayor cantidad de tickets de dicha infraccion y su cantidad
maxPlateByInfList getMaxPlateByInf(parkingTicketsADT q);

// Solo invocada si hubo un error
void throwError(const char * msg);

// Funcion que libera la memoria de la lista de infracciones
void freeQ1(infractionList l);

// Funcion que libera la memoria de la lista de agencias
void freeQ3(maxPlateByInfList l);

// Funcion que libera la memoria del ADT
void freeADT(parkingTicketsADT q);

#endif
