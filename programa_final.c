#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int status;
    int erro_critico;
} Sistema;

int main() {
     {
    int matriz[2][2];
    Sistema sys;
    int x;
    sys.status = 1 ;
    sys.erro_critico = 0 ;
    matriz[0][0] = 10 ;
    matriz[1][1] = 20 ;
    x = 50 ;
    printf("%s\n", "--- Iniciando Suite de Testes V31.0 ---" );
    if (! ( sys . erro_critico == 1 ) )  {
    printf("%s\n", "Teste 1: Sucesso - Negação de igualdade" );
    }
    if (! ( sys . status == 0 ) && x > 40 )  {
    printf("%s\n", "Teste 2: Sucesso - NAO combinado com E" );
    }
    if (! ( matriz [ 0 ] [ 0 ] == 0 ) || matriz [ 1 ] [ 1 ] == 100 )  {
    printf("%s\n", "Teste 3: Sucesso - Matriz validada com negação" );
    }
    printf("%s\n", "Resultado logico complexo (deve ser 1):" );
    printf("%g\n", (double)(! ( x < 10 ) && ( sys . status == 1 ) ));
    if (! ( sys . erro_critico == 1 || x == 0 ) )  {
    printf("%s\n", "Teste 5: Sucesso - Seguranca validada (NAO OU)" );
    }
    printf("%s\n", "--- Fim dos Testes V31.0 ---" );
    }
    
    return 0;
}
