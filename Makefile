COMPILER = gcc
FLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g

all: CHI NYC

CHI: parkingTicketsCHI.c parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -o parkingTicketsCHI.out $^

NYC: parkingTicketsNYC.c parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -o parkingTicketsNYC.out $^

clean:
	rm -f parkingTicketsCHI.out parkingTicketsNYC.out