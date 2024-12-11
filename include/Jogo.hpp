/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

// jogo.h
#ifndef JOGO_H
#define JOGO_H

#include "Player.hpp"
#include "IA.hpp"
#include <thread>
#include <atomic>
#include <vector>
#include <semaphore>

using namespace std;

class Jogo{

    // atributos privados para controle do jogo (incluindo mutex e variável atômica)
    private:
        // jogador do tipo Player
        Player *jogador;
        // mutex que controla a região crítica do pitstop
        mutex pitstopMutex;
        // mutex que controla a região crítica de chegada
        mutex OrdemDeChegada;
        // variável atômica da posição do carro, para evitar posição incorreta
        atomic <int> PosicaoDoCarro;

    // atributos públicos e métodos
    public:
        // vetor das threads
        vector<thread> threads;
        // vetor das IAs 
        vector<IA*> IAs;
        // vetor de todos os carros
        vector<Carro*> Carros;

        // inicializador do jogo, que recebe o nome do jogador e seu pneu inicial como parâmetros
        Jogo(string nomeJogador, char pneuInicial);
        ~Jogo();

        // método para inicialização
        void iniciar();
        // método que exibe a pista no terminal
        void desenharPista(const vector<Carro*> carros);
};

#endif