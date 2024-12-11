/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <string>
#include <mutex>
#include <atomic>
#include <semaphore>

// velocidades base dos pneus
#define S 2.1
#define M 1.9
#define H 1.6
#define DISTANCIA_TOTAL 100 // distância total da corrida (em metros ou voltas)

using namespace std;

class Pneu {
public:
    char tipo; // s (Soft), m (Medium) ou h (Hard)
    float velocidadeBase; //velocidade base do pneu
    float desgaste; //desgaste do pneu

    Pneu(char tipo); //construtor

    float calcularVelocidade(); // velocidade ajustada ao desgaste
    void desgastar();           // incrementa o desgaste do pneu
};

class Carro{
public:
    Pneu *pneu; //instância do objeto pneu

    atomic<bool> DentroPitStop; //atomic para verfiicar se o carro está dentro do pitstop
    atomic <bool> ChegouNaLargada; //atomic para verificar se o carro concluiu a corrida
    atomic <bool> EstourouPneu; //atomic para verificar se o carro estourou o pneu
    atomic <float> distanciaPercorrida; //variável atomica para ver a distância percorrida (atomica para evitar race condition)
    atomic <int> &PosicaoDoCarro;

    mutex &pitstopMutex; //semáforo para o pitstop
    mutex &OrdemDeChegada; //semáforo para a linha de chegada

    string nome; //nome do carro
    
    Carro(char tipoPneu, mutex &pitstopMutex, string Nome, mutex &OrdemDeChegada, atomic <int> &PosicaoDoCarro); //construtor
    ~Carro(); // libera memória do pneu

    void fazerPitStop(char novoPneu); //função para fazer pitstop
    void correr(); // simulação do carro correndo
    string getNomeCarro(); //retornar o nome do carro
};

#endif