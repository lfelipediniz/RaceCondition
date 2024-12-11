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

int GerarValorAleatorio(int inicio, int fim){ //função para gerar um inteiro aleatório de início a fim
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(inicio, fim);

    return distrib(gen);
}

//função para retornar um pneu aleatorio
char PneuAleatorio(){
    int numero_aleatorio = GerarValorAleatorio(1, 3);

    if (numero_aleatorio == 1){
        return 's';
    }
    else if (numero_aleatorio == 2){
        return 'm';
    }
    else{return 'h';}
}

//setar os semáforos e atomic passados
IA::IA(string nome, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro): pitstopMutex(Semaforo), OrdemDeChegada(OrdemDeChegadaSemaforo), PosicaoDoCarro(PosicaoDoCarro)  {
    this->nome = nome; //setar o nome
    char tipoPneuInicial = PneuAleatorio(); //pegar um pneu aleatório
    this->carro = new Carro(tipoPneuInicial, Semaforo, nome, OrdemDeChegada, PosicaoDoCarro); //criar um carro

    this->ResetarPneu = GerarValorAleatorio(2, 9); //gerar aleatoriamente quando que o pneu deve ser resetado
}

IA::~IA(){
    if(carro != nullptr){
        delete carro;
        carro = nullptr;
    }
}

string IA::getNome(){ //retorna o nome
    return nome;
}

// retorna o ponteiro para o carro do jogador
Carro *IA::getCarro(){
    return carro;
}

void IA::controlar() {
    while(true) {
        //caso o carro tenha acabado a corrida, finalizar a trhead que o controla
        if (this->carro->ChegouNaLargada.load() || this->carro->EstourouPneu.load()) break; 

        if (carro->pneu->desgaste >= this->ResetarPneu){ //verificar se deve fazer um pitstop
            carro->fazerPitStop(PneuAleatorio()); //fazer o pitstop

            this->ResetarPneu = GerarValorAleatorio(2, 9); //gerar um novo valor para fazer o pitstop
        }

        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para a próxima iteração
    }
}