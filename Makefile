COMPILER = gcc
FLAGS = -Wall -pedantic -std=c99 -fsanitize=adress -g

all: parkingTicketsCHI parkingTicketsNYC

parkingTicketsCHI: parkingTicketsCHI.c .parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -o parkingTicketsCHI.out $^

parkingTicketsNYC: parkingTicketsNYC.c .parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -o parkingTicketsNYC.out $^

clean:
	rm -f parkingTicketsCHI.out parkingTicketsNYC.out