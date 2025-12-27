registro Pessoa {
    cadeia nome;
    inteiro idade;
}

inicio() {
    Pessoa p;
    p.nome = "Pedro";
    p.idade = 25;
    exibir(p.nome); // Nota: o printf %g ainda vai dar erro aqui se tentarmos exibir a variável, pois o exibir() ainda é focado em números.
}