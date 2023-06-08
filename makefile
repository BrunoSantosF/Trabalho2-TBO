compile: dados filaPrioridade pilha dijkstra
	@gcc -o trab2 main.c *.o

all: clean compile
	@./trab2 entradas/menor.csv saida.txt

dados: 
	@gcc -c Dados.c

filaPrioridade:
	@gcc -c FilaPrioridade.c

pilha:
	@gcc -c Pilha.c

dijkstra:
	@gcc -c Dijkstra.c


valgrind: clean compile
	@valgrind ./trab2 entradas/menor.csv saida.txt

test: clean
	@gcc -c FilaPrioridade.c
	@gcc -o testPQ client.c FilaPrioridade.o
	@./testPQ

clean:
	@rm -rf *.o trab2