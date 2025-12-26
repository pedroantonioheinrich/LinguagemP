registro Usuario {
    inteiro id
    real saldo
}

inicio() {
    Usuario lista[5]
    lista[0].id = 101
    lista[0].saldo = 50.5
    exibir(lista[0].saldo)
}