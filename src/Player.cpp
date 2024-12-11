/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

#include "../include/Player.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std;

Player::Player(string nome, char tipoPneuInicial, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro): pitstopMutex(Semaforo), OrdemDeChegada(OrdemDeChegadaSemaforo), PosicaoDoCarro(PosicaoDoCarro) {
    this->nome = nome;
    this->carro = new Carro(tipoPneuInicial, Semaforo, nome, OrdemDeChegada, PosicaoDoCarro);
}

Player::~Player(){
    if(carro != nullptr){
        delete carro;
        carro = nullptr;
    }
}

string Player::getNome(){
    return nome;
}

// retorna o ponteiro para o carro do jogador
Carro *Player::getCarro(){
    return carro;
}


void Player::controlar(){
    while(true) {
        if (this->carro->ChegouNaLargada.load() || this->carro->EstourouPneu.load()) break;
        
        char escolha;
        escolha = cin.get();

        if(tolower(escolha) == 's' || tolower(escolha) == 'm' || tolower(escolha) == 'h'){
            carro->fazerPitStop(escolha); //fazer o pitstop
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}