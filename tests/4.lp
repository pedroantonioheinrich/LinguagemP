inicio() {
    inteiro contador = 1;
    inteiro limite;
    
    exibir("Ate quanto quer contar?");
    ler(limite);
    
    enquanto (contador <= limite) {
        se (contador == 5) {
            exibir("Meio do caminho (5)...");
        } senao {
            exibir(contador);
        }
        contador = contador + 1;
    }
    
    exibir("Fim da contagem!");
}