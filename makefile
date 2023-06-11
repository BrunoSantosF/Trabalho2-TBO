compile: pilha filaPrioridade dados dijkstra
	@gcc -o trab2 main.c *.o


menor: clean compile
	@./trab2 entradas/menor.csv saidas/menor.csv
	-diff gabarito/menor.csv saidas/menor.csv
entrada10: clean compile
	@./trab2 entradas/entrada10.csv saidas/saida10.csv
	-diff gabarito/saida10.csv saidas/saida10.csv
entrada50: clean compile
	@./trab2 entradas/entrada50.csv saidas/saida50.csv
	-diff gabarito/saida50.csv saidas/saida50.csv
entrada100: clean compile
	@./trab2 entradas/entrada100.csv saidas/saida100.csv
	-diff gabarito/saida100.csv saidas/saida100.csv

all: menor entrada10 entrada50 entrada100

dados: 
	@gcc -c Dados.c
filaPrioridade:
	@gcc -c FilaPrioridade.c
pilha:
	@gcc -c Pilha.c
dijkstra:
	@gcc -c Dijkstra.c


valgrind: clean compile
	@ valgrind ./trab2 entradas/menor.csv saidas/menor.csv

clean:
	@rm -rf *.o trab2