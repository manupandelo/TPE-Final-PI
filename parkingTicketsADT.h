#ifndef QUERY1ADT_H
#define QUERY1ADT_H

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>  
#include <assert.h>
#include <string.h>

typedef struct data{
    char plate[11];
    char issuingAgency[35];
    int infractionId; 
}data;

typedef struct query1CDT * query1ADT;


#endif