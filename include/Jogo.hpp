// jogo.h
#ifndef JOGO_H
#define JOGO_H

#include "Player.hpp"
#include <thread>
#include <atomic>

using namespace std;

class Jogo{
    private:
        Player *jogador;

    public:
        Jogo(string nomeJogador);
        ~Jogo();

        void iniciar();
};

#endif