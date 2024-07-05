#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"




/*HAY QUE HACER BIEN EL MANEJO DE ERRORES CUANDO ABRO ARCHIVOS*/
/*CREO QUE SE HACE CON ESTO: 
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
*/
/*
Para omitir la primera línea del archivo (que contiene el encabezado), 
puedes usar fgets para leer y descartar la primera línea antes de comenzar
a usar fscanf para leer los datos. Aquí hay una manera de hacerlo:
    char header[256];
    fgets(header, sizeof(header), file);
*/
int main(int argc, char const *argv[])
{
    FILE * infractionFile = fopen(argv[2], "r");
    parkingTicketsADT ticket = newADT();
    data fine;
    /*Leo el file de las infracciones y me guardo las infracciones correspondientes
    con su ID*/
    
    while (fscanf(infractionFile, "%d;%[^;];", &fine.infractionId, fine.infractionName ) == 2)
    {
        infractionIdToName(ticket, fine.infractionId, fine.infractionName);
    }
    
    /*Leo el file de los tickets*/
    FILE * ticketFile = fopen(argv[1], "r");
    while (fscanf(ticketFile, ""))
    {
        /* code */
    }
    

}
