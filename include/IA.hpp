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
    counting_semaphore<5> &OrdemDeChegada;
    int ResetarPneu;

    IA(string nome, mutex &Semaforo, counting_semaphore<5> &OrdemDeChegadaSemaforo);
    ~IA(); 

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif