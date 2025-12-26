inicio() {
    cadeia senha_correta;
    senha_correta = "p123";
    
    cadeia tentativa;
    exibir("Digite a senha:");
    ler(tentativa);
    
    se (iguais(tentativa, senha_correta)) {
        cadeia msg;
        msg = "Bem-vindo";
        juntar(msg, ", Pedro!");
        exibir(msg);
    } senao {
        exibir("Senha Incorreta!");
    }
}