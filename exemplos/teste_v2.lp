inicio() {
    exibir("--- Teste Versão 1.2 ---");
    
    exibir("Digite a sua idade:");
    inteiro idade = ler();
    
    exibir("Digite o ano atual:");
    inteiro ano = ler();
    
    // Teste de Operadores Lógicos (E / OU)
    se (idade >= 18 e ano > 2020) {
        exibir("Acesso permitido: Adulto na era digital.");
    } senao {
        exibir("Acesso restrito.");
    }

    exibir("Contagem regressiva:");
    para (inteiro i = 3; i > 0; i -= 1) {
        exibir(i);
        esperar(500);
    }
}