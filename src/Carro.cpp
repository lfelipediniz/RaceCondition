/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

#include "../include/Carro.hpp"
#include <thread>
#include <chrono>

using namespace std;

//
Pneu::Pneu(char tipo) {
    this->tipo = tipo;
    this->desgaste = 0;

    //seleciona a velocidade do pneu de acordo com o tipo escolhido
    if (tipo == 's'){
        velocidadeBase = S;
    }
    else if (tipo == 'm') {
        velocidadeBase = M;
    }
    else if (tipo == 'h'){
        velocidadeBase = H;
    }
    else{ //se o jogador nao selecionar nenhum dos tipos existentes, o medio sera selecionado como padrao
        velocidadeBase = M; 
        this->tipo = 'm';
    }
}

//funcao para calcular velocidade do pneu com base no desgaste dele
float Pneu::calcularVelocidade(){
    return velocidadeBase - desgaste * 0.1;
}

//funcao que aumenta o desgaste do pneu de acordo com o tipo
void Pneu::desgastar() {
    if (tipo == 's') {
        desgaste += 0.5f;
    }
    else if (tipo == 'm'){
        desgaste += 0.3f;
    }
    else if (tipo == 'h'){
        desgaste += 0.1f;
    }
}

//retorna o nome do carro
string Carro::getNomeCarro(){
    return this->nome;
}

//gente, é assim que faz inicialização em C++, se n fizer assim pode dar ruim (principalmente com o semáforo)
Carro::Carro(char tipoPneu, mutex &Semaforo, string Nome, mutex &OrdemDeChegadaSemaforo, atomic<int> &PosicaoDoCarro)
    : pneu(new Pneu(tipoPneu)), //pneu
      distanciaPercorrida(0.0), //seta a distância percorrida para 0
      PosicaoDoCarro(PosicaoDoCarro), //atomic para a posição
      pitstopMutex(Semaforo), //semáforo para o pitstop
      OrdemDeChegada(OrdemDeChegadaSemaforo),  //semáforo para a linha de chegada 
      nome(Nome) //nome do carro
{
    this->DentroPitStop.store(false); //inicialmente está fora do pitstop
    this->ChegouNaLargada.store(false); //nao terminou a corrida
    this->EstourouPneu.store(false); //pneu não está estourado
}


Carro::~Carro(){
    if (pneu != nullptr){
        delete pneu; 
        pneu = nullptr;
    }
}

void Carro::fazerPitStop(char novoPneu){
    pitstopMutex.lock(); // tenta acessar o semáforo para fazer o pitstop
    this->DentroPitStop.store(true); //seta o atomic de que está dentro do pitstop

    delete pneu; //deleta o pneu atual
    pneu = new Pneu(novoPneu); //cria um novo pneu, baseado no pneu passado

    // simulando o tempo de pit stop
    this_thread::sleep_for(chrono::seconds(3));

    this->DentroPitStop.store(false); //coloca que está fora do pitstop

    pitstopMutex.unlock(); // sai da região crítica
}

void Carro::correr(){
    while (true){
        //verificar se estourou o pneu
        if (this->pneu->desgaste >= 10) {
            this->EstourouPneu.store(true); //colocar que este carro estourou o pneu
            break; //acabar com a thread do carro (está fora do corrida)
        }

        if (this->DentroPitStop.load() == false){ //executar a função somente se o carro não estiver no pitstop
            //atualizar o valor da distância percorrida
            distanciaPercorrida.fetch_add(pneu->calcularVelocidade());

            this->pneu->desgastar(); //desgastar o pneu

            if (distanciaPercorrida >= DISTANCIA_TOTAL) { //verificar se assou na linha de chegada
                OrdemDeChegada.lock(); //tenta acessar a região crítica da chegada
                
                //adicionar na distância pontuação baseado na posição que ele chegou
                distanciaPercorrida.fetch_add(100/PosicaoDoCarro.load()); 

                //aumentar o atomic de posição do carro, pois um carro acabou de terminar a corrida
                PosicaoDoCarro.fetch_add(1);

                this->ChegouNaLargada.store(true); //setar que o carro terminou a corrida

                OrdemDeChegada.unlock(); //após passar pela linha de chegada liberar ela para o outros carros
                break; //acabou com a thread desse carro (terminou a corrida)
            }

            // setando o tempo de corrida para 1 segundo
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}