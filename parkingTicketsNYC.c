#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>

typedef struct multa{
    char plate[11];
    char issuingAgency[35];
    int infractionId; 
}multa;


int main(int argc, char const *argv[])
{
    FILE * file = fopen(argv[1], "r");
    multa fine;
    /* Aca agarra los datos de la linea del CSV y los pone en las variables*/ /* No se si esta bien hecho para que no agarre los datos no necesitamos*/
    /* De aca hacemos todo el programa, ya que tenemos todo separado bien en los datos como los vamos a usar*/
    while (fscanf(file,"%10[^;];;%d;;\%35[^;]\n",fine.plate , fine.infractionId, fine.issuingAgency ) == 3) 
    {                                                                                                      
                                                         
    }
    return 0;
}
