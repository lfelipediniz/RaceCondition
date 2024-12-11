#include "../include/IA.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

IA::IA(string nome, char tipoPneuInicial, mutex &Semaforo): pitstopMutex(Semaforo) {
    this->nome = nome;
    this->carro = new Carro(tipoPneuInicial, Semaforo, nome);

    //this->ResetarPneu = GerarValorAleatorio(2, 9); //gerar aleatoriamente quando que o pneu deve ser resetado
    this->ResetarPneu = 2;
}

int IA::GerarValorAleatorio(int inicio, int fim){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(inicio, fim);

    return distrib(gen);
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
        if (carro->pneu->desgaste >= this->ResetarPneu){
            int numero_aleatorio = GerarValorAleatorio(1, 3);

            char NovoPneu;

            if (numero_aleatorio == 1){
                NovoPneu = 's';
            }
            else if (numero_aleatorio == 2){
                NovoPneu = 'm';
            }
            else{NovoPneu = 'h';}

            carro->fazerPitStop(NovoPneu); //fazer o pitstop
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}