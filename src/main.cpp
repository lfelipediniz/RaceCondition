/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

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

    cout << R"(
 ________ ___  _____ ______           ________  _______              ___  ________  ________  ________
|\  _____\\  \|\   _ \  _   \        |\   ___ \|\  ___ \            |\  \|\   __  \|\   ____\|\   __  \
\ \  \__/\ \  \ \  \\\__\ \  \       \ \  \_|\ \ \   __/|           \ \  \ \  \|\  \ \  \___|\ \  \|\  \
 \ \   __\\ \  \ \  \\|__| \  \       \ \  \ \\ \ \  \_|/__       __ \ \  \ \  \\\  \ \  \  __\ \  \\\  \
  \ \  \_| \ \  \ \  \    \ \  \       \ \  \_\\ \ \  \_|\ \     |\  \\_\  \ \  \\\  \ \  \|\  \ \  \\\  \
   \ \__\   \ \__\ \__\    \ \__\       \ \_______\ \_______\    \ \________\ \_______\ \_______\ \_______\
    \|__|    \|__|\|__|     \|__|        \|_______|\|_______|     \|________|\|_______|\|_______|\|_______|
    )" << endl;

    return 0;
}
