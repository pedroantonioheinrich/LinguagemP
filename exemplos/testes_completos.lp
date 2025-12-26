// --- TESTE DE MODULOS ---
usar "utils.lp"

// --- TESTE DE REGISTROS (STRUCTS) ---
registro Usuario {
    inteiro id;
    cadeia nome;
    real saldo;
}

// --- TESTE DE FUNCOES COM DIFERENTES TIPOS ---
funcao inteiro somar(inteiro a, inteiro b) {
    retorne a + b;
}

funcao real aplicar_taxa(real valor) {
    retorne valor * 1.10;
}

funcao cadeia obter_status(real saldo) {
    se (saldo > 0) {
        retorne "Positivo";
    } senao {
        retorne "Negativo";
    }
}

inicio() {
    // 1. Teste de Variaveis Basicas
    inteiro x = 10;
    inteiro y = 20;
    real pi = 3.1415;
    cadeia saudacao = "Ola Compilador!";

    // 2. Teste de Operacoes Matematicas
    inteiro resultado = somar(x, y);
    exibir("--- Teste Matematica ---");
    exibir(resultado); // Deve exibir 30

    // 3. Teste de Modulo Externo (utils.lp)
    exibir_alerta("Teste de Modulo OK");

    // 4. Teste de Manipulacao de Registros
    Usuario p1;
    p1.id = 1;
    p1.nome = "Pedro";
    p1.saldo = 150.50;

    exibir("--- Teste Registro ---");
    exibir(p1.nome);
    exibir(p1.saldo);

    // 5. Teste de Logica Condicional
    exibir("--- Teste Condicional ---");
    se (p1.saldo > 100) {
        exibir("Saldo Rico");
    } senao {
        exibir("Saldo Pobre");
    }

    // 6. Teste de Strings e Funcoes de Texto
    cadeia nome1 = "Linguagem";
    cadeia nome2 = " P";
    juntar(nome1, nome2); // concatena
    exibir("--- Teste String ---");
    exibir(nome1);

    se (iguais(nome1, "Linguagem P")) {
        exibir("Comparacao String: OK");
    }

    // 7. Teste de Escopo e Retorno de Funcao
    real novo_saldo = aplicar_taxa(p1.saldo);
    exibir("--- Teste Saldo com Taxa ---");
    exibir(novo_saldo);

    cadeia status = obter_status(novo_saldo);
    exibir("Status Atual:");
    exibir(status);

    // 8. Teste de Encontros (Loops)
    inteiro contador = 1;
    exibir("--- Teste Loop ---");
    enquanto (contador <= 3) {
        exibir(contador);
        contador = contador + 1;
    }

    // 9. Teste de Entrada de Dados (Opcional - Requer interacao)
    // exibir("Digite um numero para dobrar:");
    // inteiro num;
    // ler(num);
    // exibir(num * 2);

    exibir("--- FIM DOS TESTES ---");
}