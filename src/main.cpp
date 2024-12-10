#include "../include/Jogo.hpp"
#include <iostream>

using namespace std;

int main() {
    // Exibe uma mensagem de boas-vindas
    cout << "=====================================\n";
    cout << "  Bem-vindo ao RaceCodition!\n";
    cout << "=====================================\n";

    // Inicializa o jogo
    Jogo jogo;

    // Inicia o jogo
    jogo.iniciar();

    // Mensagem final após o término do jogo
    cout << "Obrigado por jogar!\n";

    return 0;
}
