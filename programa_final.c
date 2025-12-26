#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char nome[256];
    float preco;
} Produto;

float aplicar_desconto(float  valor , float  taxa ) {
    return valor * ( 1.0 - taxa ) ;
    }
    
int main() {
     {
    int notas[3];
    notas[0] = 10 ;
    notas[1] = 8 ;
    notas[2] = 9 ;
    printf("%s\n", "--- TESTE 1: VETORES ---" );
    printf("%s\n", "Nota 1:" );
    printf("%g\n", (double)(notas [ 0 ] ));
    Produto p1;
    strcpy(p1.nome, "Monitor");
    p1.preco = 1200.0 ;
    printf("%s\n", "--- TESTE 2: REGISTROS E FUNCOES ---" );
    printf("%s\n", "Produto:" );
    printf("%s\n", p1 . nome );
    printf("%s\n", "Preco original:" );
    printf("%g\n", (double)(p1 . preco ));
    float preco_final;
    preco_final = aplicar_desconto ( p1 . preco , 0.10 ) ;
    printf("%s\n", "Preco com 10% de desconto:" );
    printf("%g\n", (double)(preco_final ));
    printf("%s\n", "--- TESTE 3: LOOP COM VETOR ---" );
    int i;
    i = 0 ;
    while (i < 3 )  {
    printf("%s\n", "Lendo nota do indice:" );
    printf("%g\n", (double)(i ));
    printf("%g\n", (double)(notas [ i ] ));
    i = i + 1 ;
    }
    }
    
    return 0;
}
