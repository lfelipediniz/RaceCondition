#include "../include/Player.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Player::Player(string nome, char tipoPneuInicial, mutex &Semaforo, counting_semaphore<5> &OrdemDeChegadaSemaforo): pitstopMutex(Semaforo), OrdemDeChegada(OrdemDeChegadaSemaforo) {
    this->nome = nome;
    this->carro = new Carro(tipoPneuInicial, Semaforo, nome, OrdemDeChegada);
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
        if (this->carro->ChegouNaLargada.load()) break;
        
        char escolha;
        cin >> escolha;

        if(tolower(escolha) == 's' || tolower(escolha) == 'm' || tolower(escolha) == 'h'){
            carro->fazerPitStop(escolha); //fazer o pitstop
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}