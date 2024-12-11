#include "../include/Jogo.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "=====================================\n";
    cout << "  Bem-vindo ao RaceCodition!\n";
    cout << "=====================================\n";

    string nomeJogador;
    char tipoPneuInicial;
    cout << "Qual o nome do seu corredor: ";
    getline(cin, nomeJogador);
    cout << "Com qual tipo de pneu você deseja iniciar a corrida (s/m/h): ";
    cin >> tipoPneuInicial;

    Jogo jogo(nomeJogador, tipoPneuInicial);

    jogo.iniciar();

    cout << "Obrigado por jogar!\n";

    return 0;
}
