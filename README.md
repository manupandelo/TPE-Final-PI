# TPE - Programacion Imperativa - 1ºC 2024

## Descripcion Funcional

Este trabajo consiste en un programa que procesa los datos de multa de estacionamiento

El programa genera los siguientes queries, a traves de la informacion que el usuario le da mediantes archivos .csv

- Query 1: Total de multas por infraccion. La informacion se ordena de forma descendente por cantidad de multas por infraccion y se lista el nombre de la infraccion y la cantidad de multas.

- Query 2: Infraccion mas popular por agencia emisora. La informacion se ordena en forma alfabetica por agencia emisora y se lista el nombre de la agencia emisora, la infraccion mas popular de la dicha y la cantidad de multas correspondiente.

- Query 3: Patente con mas multas por infraccion. La informacion se ordena de forma alfabetica por infraccion y se lista el nombre de la infraccion, la patente con mas multas por dicha infraccion y la cantidad de multas que le corresponden a dicha patente.

## Compilacion y Ejecucion

Para la compilacion del programa, en caso de querer compilar los ejecutables tanto de NYC como de CHI, en linea de comandos desde el directorio en el que se encuentre el archivo `Makefile`, ejecute: 

```
    make All
```
Esto va a generar dos ejecutables llamados `parkingTicketsNYC.out` y `parkingTicketsCHI.out`

En caso de querer compilar solo uno, se realiza de la misma forma pero aclarando el de cual ciudad se quiere compilar:

```
    make parkingTicketsNYC
```
o

```
    make parkingTicketsCHI
```

Y esto va a generar solo un ejecutable correspondiente al programa de cada ciudad.

Una vez esten compilados, desde la linea de comandos pueden ser ejecutados de la siguiente manera:

Para `ParkingTicketsNYC`:

```
    ./parkingTicketsNYC.out <Path al archivo de multas> <Path al archivo de infracciones> <3 Path distintos para donde almacenar las queries (.csv)>
```

Para `ParkingTicketsCHI`:

```
    ./parkingTicketsCHI.out <Path al archivo de multas> <Path al archivo de infracciones> <3 Path distintos para donde almacenar las queries (.csv)>
```

Finalmente si se desea limpiar los ejecutables, de la siguiente manera:

```
    make clean
```

En la linea de comandos, eliminira los archivos generados durante la compilacion.

## Integrantes 

- Tiziano Ametller - 65004 - tametller@itba.edu.ar

- Manuel Pandelo - 65748 - mpandelo@itba.edu.ar

- Rocco Perrone - 65628 - rperrone@itba.edu,ar