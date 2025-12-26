CC = gcc
CFLAGS = -Wall -Wextra -g

all: lp_compilador

lp_compilador: src/logs.o src/lexico.o src/gerador.o src/semantico.o src/sintatico.o src/principal.o
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: lp_compilador
# 	# Primeiro gera o C da biblioteca
# 	./lp_compilador exemplos/utils.lp
# 	mv codigo_gerado.c ./utils.lp.c


	
	./lp_compilador exemplos/testev31.lp
	mv codigo_gerado.c programa_final.c
	# Compila o programa final
	$(CC) programa_final.c -o meu_programa_p
	./meu_programa_p

clean:
	rm -f src/*.o lp_compilador exemplos/*.lp.c programa_final.c meu_programa_p