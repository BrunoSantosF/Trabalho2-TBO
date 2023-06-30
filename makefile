compile: lista filaPrioridade dados dijkstra
	@gcc -o trab2 main.c *.o

entrada10: clean compile
	@./trab2 entradas/entrada10.csv saidas/out-entrada10.csv
	-diff -b gabarito/out-entrada10.csv saidas/out-entrada10.csv
entrada50: clean compile
	@./trab2 entradas/entrada50.csv saidas/out-entrada50.csv
	-diff -b gabarito/out-entrada50.csv saidas/out-entrada50.csv
entrada100: clean compile
	@./trab2 entradas/entrada100.csv saidas/out-entrada100.csv
	-diff -b gabarito/out-entrada100.csv saidas/out-entrada100.csv
in50: clean compile
	@./trab2 entradas/in50.csv saidas/out-in50.csv
	-diff -b gabarito/out-in50.csv saidas/out-in50.csv
in80: clean compile
	@./trab2 entradas/in80.csv saidas/out-in80.csv
	-diff -b gabarito/out-in80.csv saidas/out-in80.csv
in100: clean compile
	@./trab2 entradas/in100.csv saidas/out-in100.csv
	-diff -b gabarito/out-in100.csv saidas/out-in100.csv
in250: clean compile
	@./trab2 entradas/in250.csv saidas/out-in250.csv
	-diff -b gabarito/out-in250.csv saidas/out-in250.csv
in500: clean compile
	@./trab2 entradas/in500.csv saidas/out-in500.csv
	-diff -b gabarito/out-in500.csv saidas/out-in500.csv
in750: clean compile
	@./trab2 entradas/in750.csv saidas/out-in750.csv
	-diff -b gabarito/out-in750.csv saidas/out-in750.csv
in2500: clean compile
	@./trab2 entradas/in2500.csv saidas/out-in2500.csv
	-diff -b gabarito/out-in2500.csv saidas/out-in2500.csv
	

#problemas a partir daqui
in5000: clean compile
	@./trab2 entradas/in5000.csv saidas/out-in5000.csv
	-diff -b gabarito/out-in5000.csv saidas/out-in5000.csv
in7500: clean compile
	@./trab2 entradas/in7500.csv saidas/out-in7500.csv
	-diff -b gabarito/out-in7500.csv saidas/out-in7500.csv
in25000: clean compile
	@./trab2 entradas/in25000.csv saidas/out-in25000.csv
	-diff -b gabarito/out-in25000.csv saidas/out-in25000.csv
in50000: clean compile
	@./trab2 entradas/in50000.csv saidas/out-in50000.csv
	-diff -b gabarito/out-in50000.csv saidas/out-in50000.csv
in75000: clean compile
	@./trab2 entradas/in75000.csv saidas/out-in75000.csv
	-diff -b gabarito/out-in75000.csv saidas/out-in75000.csv
in100000: clean compile
	@./trab2 entradas/in100000.csv saidas/out-in100000.csv
	-diff -b gabarito/out-in100000.csv saidas/out-in100000.csv
in500000: clean compile
	@./trab2 entradas/in500000.csv saidas/out-in500000.csv
	-diff -b gabarito/out-in500000.csv saidas/out-in500000.csv
in1000000: clean compile
	@./trab2 entradas/in1000000.csv saidas/out-in1000000.csv
	-diff -b gabarito/out-in1000000.csv saidas/out-in1000000.csv

all: entrada10 entrada50 entrada100 in50 in80 in100 in250 in500 in750 in2500 in5000 in7500 in25000 in50000 in75000 in100000 in500000 in1000000

dados: 
	@gcc -c Dados.c
filaPrioridade:
	@gcc -c FilaPrioridade.c
lista:
	@gcc -c Lista.c
dijkstra:
	@gcc -c Dijkstra.c


valgrind: clean compile
	@ valgrind ./trab2 entradas/entrada100.csv saidas/out-entrada100.csv

clean:
	@rm -rf *.o trab2