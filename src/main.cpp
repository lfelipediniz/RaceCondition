#include "../include/Jogo.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "=====================================\n";
    cout << "  Bem-vindo ao RaceCodition!\n";
    cout << "=====================================\n";

    string nomeJogador;
    cout << "Qual o nome do seu corredor: ";
    getline(cin, nomeJogador);
    Jogo jogo(nomeJogador);


    jogo.iniciar();


    cout << "Obrigado por jogar!\n";

    return 0;
}
