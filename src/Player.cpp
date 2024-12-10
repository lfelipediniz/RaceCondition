#include "../include/Player.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Player::Player(string nome, char tipoPneuInicial){
    this->nome = nome;
    this->desejaPitStop = false;
    this->carro = new Carro(tipoPneuInicial);
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

bool Player::querPitStop(){
    return desejaPitStop;
}

// resetando a flag
void Player::resetPitStop(){
    desejaPitStop = false;
}

void Player::controlar(){
    while(true) {
        char escolha;

        cout << "Jogador " << nome << ", deseja fazer pitstop? (s/n): ";
        cin >> escolha;

        if(escolha == 's' || escolha == 'S'){
            desejaPitStop = true;
            cout << nome << " deseja fazer pitstop.\n";
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}

char Player::escolherNovoPneu() {
    char novoPneu;

    while(true){
        cout << "Escolha o tipo de pneu pra fazer o pitstop?\n";
        cout << "s - Soft\n";
        cout << "m - Medium\n";
        cout << "h - Hard\n";
        cout << "Escolha: ";
        cin >> novoPneu;

        if(novoPneu == 's' || novoPneu == 'm' || novoPneu == 'h'){
            return novoPneu
        }
        else{
            cout << "Tipo de pneu inválido. Tente novamente.\n";
        }
    }
}