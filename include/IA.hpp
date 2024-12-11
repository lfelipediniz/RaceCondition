#ifndef IA_H
#define IA_H

#include "Carro.hpp"
#include "Player.hpp"
#include <string>
#include <atomic>

using namespace std;

class IA {
public:
    string nome;
    Carro *carro;
    mutex &pitstopMutex;
    mutex &OrdemDeChegada;
    int ResetarPneu;
    atomic <int> &PosicaoDoCarro;

    IA(string nome, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro);
    ~IA(); 

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif