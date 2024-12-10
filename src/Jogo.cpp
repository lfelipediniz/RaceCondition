#include "../include/Jogo.h"
#include <iostream>
#include <cctype>

using namespace std;

Jogo::Jogo(char tipoPneuInicial) : desejaPitStop(false), corridaTerminou(false) {
    tipoPneuInicial = tolower(tipoPneuInicial);
    if (tipoPneuInicial != 's' && tipoPneuInicial != 'm' && tipoPneuInicial != 'h') {
        cout << "tipo de pneu inválido. usando pneu 's' por padrão." << endl;
        tipoPneuInicial = 's';
    }

    tipoPneuEscolhido.store(tipoPneuInicial, memory_order_relaxed);

    jogador = new Carro(tipoPneuInicial, pitstop_mutex, desejaPitStop, tipoPneuEscolhido, corridaTerminou);
    inputHandler = new FazerES(desejaPitStop, tipoPneuEscolhido, corridaTerminou);
}

Jogo::~Jogo() {
    delete jogador;
    delete inputHandler;
}

void Jogo::iniciar() {

    thread_carro = thread(&Carro::Correr, jogador);
    thread_input = thread(&FazerES::escolhaPitstop, inputHandler);
    thread_carro.join();

    // aguarda a thread de entrada finalizar
    thread_input.join();
}
