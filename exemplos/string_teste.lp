inicio() {
    cadeia nome;
    exibir("Qual o seu nome?");
    ler(nome);
    
    cadeia saudacao;
    saudacao = "Ola, ";
    
    exibir(saudacao);
    exibir(nome);
    
    inteiro tam;
    tam = tamanho_texto(nome);
    
    exibir("Seu nome tem este numero de letras:");
    exibir(tam);
}