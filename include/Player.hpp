/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Carro.hpp"
#include <string>
#include <atomic>

using namespace std;

class Player
{
private:
    mutex &pitstopMutex; //mutex para o pitstop
    mutex &OrdemDeChegada; //mutex para a linha de chegada

    atomic <int> &PosicaoDoCarro; //variável atomica para ver a posição do carro quando ele passa na linha de chegada

    string nome; //nome do jogador
    Carro *carro; //carro do jogador

public:
    Player(string nome, char tipoPneuInicial, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro); //construtor
    ~Player(); //quando ele for distruido

    string getNome(); //retornar o nome
    Carro *getCarro(); //retornar o carro   
    void controlar(); //controlar o carro
};

#endif