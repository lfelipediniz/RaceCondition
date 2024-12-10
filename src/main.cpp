#include "../include/Jogo.hpp"
#include <iostream>

using namespace std;

int main() {
    // Exibe uma mensagem de boas-vindas
    cout << "=====================================\n";
    cout << "  Bem-vindo ao RaceCodition!\n";
    cout << "=====================================\n";

    string nomeJogador;
    cout << "Qual o nome do seu corredor: ";
    getline(cin, nomeJogador);
    // Inicializa o jogo
    Jogo jogo(nomeJogador);

    // Inicia o jogo
    jogo.iniciar();

    // Mensagem final após o término do jogo
    cout << "Obrigado por jogar!\n";

    return 0;
}
