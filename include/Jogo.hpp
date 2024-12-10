// jogo.h
#ifndef JOGO_H
#define JOGO_H

#include "Player.hpp"
#include <thread>
#include <atomic>

using namespace std;

// enum class DesejaEntrarNoPitStop(s, m, h, NotPit); //enumerador para definir os valores de quando o jogador pode entrar no pitstop


class Jogo{
    private:
        Player *jogador;

    public:
        Jogo(string nomeJogador);
        ~Jogo();

        void iniciar();
};

#endif