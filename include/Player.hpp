#ifndef PLAYER_H
#define PLAYER_H

#include "Carro.hpp"
#include <string>
#include <atomic>

using namespace std;

class Player
{
private:
    string nome;
    Carro *carro;
    atomic<bool> desejaPitStop;

public:
    Player(string nome, char tipoPneuInicial);
    ~Player();

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif