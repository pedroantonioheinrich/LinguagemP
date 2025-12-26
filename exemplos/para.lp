inicio() {
    inteiro limite;
    exibir("Digite o limite para o loop PARA:");
    ler(limite);
    
    inteiro i;
    para (i = 1; i <= limite; i = i + 1) {
        exibir(i);
    }
    
    exibir("Fim do loop!");
}