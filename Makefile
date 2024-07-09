COMPILER = gcc
FLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g

all: CHI NYC

CHI: parkingTicketsCHI.c parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -o CHI.out $^

NYC: parkingTicketsNYC.c parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -o NYC.out $^

clean:
	rm -f CHI.out NYC.out