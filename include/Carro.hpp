#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <string>
#include <mutex>
#include <atomic>
#include <semaphore>

// velocidades base dos pneus
#define S 2.0
#define M 1.7
#define H 1.5
#define DISTANCIA_TOTAL 100 // distância total da corrida (em metros ou voltas)

using namespace std;

class Pneu {
public:
    char tipo; // s (Soft), m (Medium) ou h (Hard)
    float velocidadeBase;
    float desgaste;

    Pneu(char tipo);

    float calcularVelocidade(); // velocidade ajustada ao desgaste
    void desgastar();           // incrementa o desgaste do pneu
};

class Carro{
public:
    Pneu *pneu;
    atomic <float> distanciaPercorrida;
    mutex &pitstopMutex;
    string nome;
    atomic<bool> DentroPitStop;
    atomic <bool> ChegouNaLargada;
    atomic <bool> EstourouPneu;
    mutex &OrdemDeChegada;
    atomic <int> &PosicaoDoCarro;

    Carro(char tipoPneu, mutex &pitstopMutex, string Nome, mutex &OrdemDeChegada, atomic <int> &PosicaoDoCarro);
    ~Carro(); // libera memória do pneu

    void fazerPitStop(char novoPneu);
    void correr();                    // simulação do carro correndo
    string getNomeCarro();
};

#endif