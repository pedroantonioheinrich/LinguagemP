registro Pessoa {
    cadeia nome;
    inteiro idade;
}

inicio() {
    Pessoa p;
    
    exibir("Digite o seu nome:");
    ler(p.nome);
    
    exibir("Digite a sua idade:");
    ler(p.idade);
    
    exibir("Ola!");
    exibir(p.nome);
    exibir("Sua idade eh:");
    exibir(p.idade);
}