#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <string>
#include <mutex>

#define S 2.0
#define M 1.5
#define H 1.0
#define DISTANCIA_TOTAL 1000 // distância total da corrida (em metros ou voltas)

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
    float distanciaPercorrida;
    mutex &pitstopMutex;

    Carro(char tipoPneu, mutex &pitstopMutex);
    ~Carro(); // libera memória do pneu

    void fazerPitStop(char novoPneu);
    void correr();                    // simulação do carro correndo
    void verificarProgressoCorrida(); // mostra o progresso e verfica o fim
};

// class FazerES{
// public:
//     void escolhaPitstop();
// };

#endif