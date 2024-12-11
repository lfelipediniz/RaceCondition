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
    int ResetarPneu;
    IA(string nome, char tipoPneuInicial, mutex &Semaforo);
    ~IA();

    string getNome();    
    Carro *getCarro();   
    void controlar();
    int GerarValorAleatorio(int inicio, int fim);
};

#endif