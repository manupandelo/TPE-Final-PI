COMPILER = gcc
FLAGS = -Wall -pedantic -std=c99 -fsanitize=address -g


all: CHI NYC

CHI: parkingTicketsCHI.c parkingTicketsADT.c 
	$(COMPILER) $(FLAGS) -o parkingTicketsCHICHI.out $^

NYC: parkingTicketsNYC.c parkingTicketsADT.c
	$(COMPILER) $(FLAGS) -DNY -o parkingTicketsNYC.out $^

clean:
	rm -rf CHI.out NYC.out CHI.out.dSYM NYC.out.dSYM query1.csv query2.csv query3.csv