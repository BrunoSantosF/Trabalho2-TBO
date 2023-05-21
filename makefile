make :
	@gcc -c *.c
	@gcc -o trab2 *.o
run :
	@./trab2 entrada.txt saida.txt
clean :
	@rm -rf *.o trab2