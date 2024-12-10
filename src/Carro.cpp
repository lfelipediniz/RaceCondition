#include "../include/Carro.hpp"
#include <thread>
#include <chrono>

using namespace std;

Pneu::Pneu(char tipo)
{
    this->tipo = tipo;
    this->desgaste = 0;

    if (tipo == 's'){
        velocidadeBase = S;
    }
    else if (tipo == 'm') {
        velocidadeBase = M;
    }
    else if (tipo == 'h'){
        velocidadeBase = H;
    }
    else{
        cout << "Tipo de pneu inválido. Usando pneu médio (M) por padrão.\n";
        velocidadeBase = M; // setando o pneu médio como padrão
        this->tipo = 'm';
    }
}

float Pneu::calcularVelocidade(){
    return velocidadeBase - desgaste * 0.1;
}

void Pneu::desgastar()
{
    if (tipo == 's') {
        desgaste += 0.3f;
    }
    else if (tipo == 'm'){
        desgaste += 0.2f;
    }
    else if (tipo == 'h'){
        desgaste += 0.1f;
    }
}

Carro::Carro(char tipoPneu){
    distanciaPercorrida = 0;
    pneu = new Pneu(tipoPneu); // alocando o pneu dinamicaente
}

Carro::~Carro(){
    if (pneu != nullptr){
        delete pneu; 
        pneu = nullptr;
    }
}

void Carro::fazerPitStop(char novoPneu){
    pitstopMutex.lock(); // trava o mutex para garantir que apenas um carro faça o pitstop por vez

    delete pneu;
    pneu = new Pneu(novoPneu);

    cout << "Pit stop concluido. Pneu trocado para: " << novoPneu << endl;

    // simulando o tempo de pit stop
    this_thread::sleep_for(chrono::seconds(3));

    pitstopMutex.unlock(); // destrava o mutex
}

void Carro::correr(){
    while (distanciaPercorrida < DISTANCIA_TOTAL){
        distanciaPercorrida += pneu->calcularVelocidade();

        pneu->desgastar();
        verificarProgressoCorrida();
        
        // setando o tempo de corrida para 1 segundo
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Carro::verificarProgressoCorrida(){
    cout << "Distância percorrida por " << distanciaPercorrida << " metros\n";

    if(distanciaPercorrida >= DISTANCIA_TOTAL){
        cout << "Ai toma!!! Carro chegou na linha de chegada!\n";
    } else if (pneu->desgaste >= 10){
        cout << "Pneu furou! Você está fora da corrida\n";
        distanciaPercorrida = DISTANCIA_TOTAL;
    }
}