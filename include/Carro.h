// carro.h
#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <mutex>
#include <atomic>

using namespace std;

class Carro {
public:
    Carro(char tipoPneu, mutex& semaforo, atomic<bool>& desejaPitStop, atomic<char>& tipoPneuEscolhido, atomic<bool>& corridaTerminou);
    ~Carro();
    void FazerPitStop(char TipoPneu);
    void Correr();

private:
    // atributos do carro
    string Nome;
    class Pneu* pneu;
    float distanciaPercorrida;
    float velocidade;

    // referências para objetos de sincronização compartilhados
    mutex& semaforo;
    atomic<bool>& desejaPitStop;
    atomic<char>& tipoPneuEscolhido;
    atomic<bool>& corridaTerminou;
};

class FazerES {
public:
    FazerES(atomic<bool>& desejaPitStop, atomic<char>& tipoPneuEscolhido, atomic<bool>& corridaTerminou);
    void escolhaPitstop();

private:
    atomic<bool>& desejaPitStop;
    atomic<char>& tipoPneuEscolhido;
    atomic<bool>& corridaTerminou;
};

#endif
