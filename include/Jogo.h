#ifndef JOGO_H
#define JOGO_H

#include "../include/Carro.h"  

#include <string>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

class Jogo {
private:
    Carro* jogador;
    FazerES* inputHandler;
    mutex pitstop_mutex; // semáforo para pit stop

    atomic<bool> desejaPitStop;
    atomic<char> tipoPneuEscolhido;
    atomic<bool> corridaTerminou;
    thread thread_carro;
    thread thread_input;

public:
    Jogo(char tipoPneuInicial);
    ~Jogo();
    void iniciar();
};

#endif
