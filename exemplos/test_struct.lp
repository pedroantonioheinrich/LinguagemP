registro Carro {
    inteiro ano;
    real preco;
}

inicio() {
    Carro meuCarro;
    meuCarro.ano = 2025;
    meuCarro.preco = 55000.50;
    
    exibir("Ano do carro:");
    exibir(meuCarro.ano);
}