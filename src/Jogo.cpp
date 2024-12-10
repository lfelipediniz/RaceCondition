#include "../include/Jogo.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Jogo::Jogo(string nomeJogador)
{
    jogador = new Player(nomeJogador, 'm'); // começa com pneu médio
}

// desalocando o jogador
Jogo::~Jogo()
{
    if (jogador != nullptr)
    {
        delete jogador;
        jogador = nullptr;
    }
}

void Jogo::iniciar()
{
    thread threadCorrida(&Carro::correr, jogador->getCarro()); // inicia a thread do carro
    thread threadControle(&Player::controlar, jogador);        // inicia a thread de controle do jogador

    while (jogador->getCarro()->distanciaPercorrida < DISTANCIA_TOTAL)
    {
        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para encerrar as threads
    }

    // aguarda a conclusão das thread corrida
    threadCorrida.join();
    // desanexa a thread controle do programa principal, assim ela consegue executar de maneira independente
    threadControle.detach();

    cout << "Fim da corrida! Parabéns, " << jogador->getNome() << "!\n";
}
