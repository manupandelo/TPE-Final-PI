#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>
#include "parkingTicketsADT.h"

typedef struct data{
    char plate[11];
    char issuingAgency[35];
    int infractionId;
    char infractionName[31]; 
}data;


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
    FILE * file = fopen(argv[1], "r");
    data fine;
    parkingTicketsADT tickets = newADT();
    
    /* Aca agarra los datos de la linea del CSV y los pone en las variables*/ /* No se si esta bien hecho para que no agarre los datos no necesitamos*/
    /* De aca hacemos todo el programa, ya que tenemos todo separado bien en los datos como los vamos a usar*/
    while (fscanf(file,"%10[^;];%*[^;];%d;%*[^;];%35[^\n]\n",fine.plate , &fine.infractionId, fine.issuingAgency ) == 3) 
    {                                                                                                      
        query1Read(tickets, fine.infractionId);                                               
    }

    /*Aca leo el archivo de infracciones*/
    FILE * infractionFile = fopen(argv[2], "r");
    data fine2;
    q1List firstQ1List = NULL;

    /*HAY QUE HACER BIEN LO DE "%d;%30[^;];" EN EL DE ARRIB TAMBIEN*/
    while (fscanf(infractionFile, "%d;%30[^;];"), &fine.infractionId, fine.infractionName)
    {
        firstQ1List = arrToListQ1(tickets, fine.infractionId, fine.infractionName, firstQ1List);
    }
    
    /*Aca pongo los datos en el CSV del query1*/
    FILE * query1File = fopen(argv[3], "w");
    listToQ1CSV(query1File, firstQ1List);
    
    
    return 0;
}
