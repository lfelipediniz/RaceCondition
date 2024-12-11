/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

#include "../include/IA.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

int GerarValorAleatorio(int inicio, int fim){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(inicio, fim);

    return distrib(gen);
}

//
char PneuAleatorio(){
    int numero_aleatorio = GerarValorAleatorio(1, 3);

    char NovoPneu;

    if (numero_aleatorio == 1){
        NovoPneu = 's';
    }
    else if (numero_aleatorio == 2){
        NovoPneu = 'm';
    }
    else{NovoPneu = 'h';}

    return NovoPneu;
}

IA::IA(string nome, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro): pitstopMutex(Semaforo), OrdemDeChegada(OrdemDeChegadaSemaforo), PosicaoDoCarro(PosicaoDoCarro)  {
    this->nome = nome;
    char tipoPneuInicial = PneuAleatorio();
    this->carro = new Carro(tipoPneuInicial, Semaforo, nome, OrdemDeChegada, PosicaoDoCarro);

    this->ResetarPneu = GerarValorAleatorio(2, 9); //gerar aleatoriamente quando que o pneu deve ser resetado
}

IA::~IA(){
    if(carro != nullptr){
        delete carro;
        carro = nullptr;
    }
}

string IA::getNome(){
    return nome;
}

// retorna o ponteiro para o carro do jogador
Carro *IA::getCarro(){
    return carro;
}

void IA::controlar() {
    while(true) {
        if (this->carro->ChegouNaLargada.load()) break;

        if (carro->pneu->desgaste >= this->ResetarPneu){
            carro->fazerPitStop(PneuAleatorio()); //fazer o pitstop

            this->ResetarPneu = GerarValorAleatorio(2, 9);
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}