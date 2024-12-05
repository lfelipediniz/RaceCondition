#ifndef CARRO_H
#define CARRO_H

#define S 2.0
#define M 1.5 
#define H 1.0
#define DISTANCIA_TOTAL 1000  // Distância total da corrida (em metros ou voltas)

#include <iostream>

class Carro{
public:
    Carro(string nome, char tipoPneu);
    void FazerPitStop(char TipoPneu);
    void Correr();
};

class FazerES{
public:
    void escolhaPitstop();
};

#endif