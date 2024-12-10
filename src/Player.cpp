#include "../include/Player.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Player::Player(string nome, char tipoPneuInicial, mutex &Semaforo): pitstopMutex(Semaforo) {
    this->nome = nome;
    this->carro = new Carro(tipoPneuInicial, Semaforo);
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
        printf("aksubdgasdasd");
        char escolha;

        cout << "Você pode entrar no pitstop a qulquer momento, digite 's', 'm' ou 'h' para escolher o tipo de pneu.\n";
        cin >> escolha;

        if(tolower(escolha) == 's' || tolower(escolha) == 'm' || tolower(escolha) == 'h'){
            carro->fazerPitStop(escolha); //fazer o pitstop
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}