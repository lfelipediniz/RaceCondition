// jogo.h
#ifndef JOGO_H
#define JOGO_H

#include "Player.hpp"
#include "IA.hpp"
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

class Jogo{
    private:
        Player *jogador;
        mutex pitstopMutex;

    public:
        vector<thread> threads;
        vector<IA*> IAs;
        vector<Carro*> Carros;

        Jogo(string nomeJogador);
        ~Jogo();

        void iniciar();
        void desenharPista(const vector<Carro*> carros);
};

#endif