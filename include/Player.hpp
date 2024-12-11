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
    mutex &pitstopMutex;
    counting_semaphore<5> &OrdemDeChegada;

public:
    Player(string nome, char tipoPneuInicial, mutex &Semaforo, counting_semaphore<5> &OrdemDeChegadaSemaforo);
    ~Player();

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif