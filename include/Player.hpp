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
    mutex &OrdemDeChegada;
    atomic <int> &PosicaoDoCarro;

public:
    Player(string nome, char tipoPneuInicial, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro);
    ~Player();

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif