/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

#ifndef IA_H
#define IA_H

#include "Carro.hpp"
#include "Player.hpp"
#include <string>
#include <atomic>

using namespace std;

class IA {
public:
    string nome; //nome da IA
    Carro *carro; //carro da IA
    int ResetarPneu; //para saber quando resetar o pneu

    mutex &pitstopMutex; //semáforo para fazer pitstop
    mutex &OrdemDeChegada; //semáforo para a linha de chegada

    atomic <int> &PosicaoDoCarro; //atomico para verificar qual é a posição do carro quando passa pela linha de chegada
    
    IA(string nome, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro); //construtor
    ~IA(); //método para quando a classe for excluida

    string getNome();    //pegar o nome da ia
    Carro *getCarro();   //pegar o carro
    void controlar(); //controlar o carro
};

#endif