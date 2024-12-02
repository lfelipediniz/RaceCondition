int main() {
    // Criando o jogo com 5 carros, e com um raio de 10 unidades
    Jogo jogo(5, 10.0);
    
    // Inicia as threads dos carros
    jogo.iniciar();

    return 0;
}
