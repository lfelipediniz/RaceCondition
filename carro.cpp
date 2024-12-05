#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

#include <atomic>

#include <semaphore>

#include "carro.h"
#include "jogo.h"

using namespace std;

mutex pitstop_mutex;  // Mutex para sincronizar o pitstop
mutex user_input_mutex; // Mutex para controlar o input do usuário

#define S 2.0
#define M 1.5 
#define H 1.0
#define DISTANCIA_TOTAL 1000  // Distância total da corrida (em metros ou voltas)

class Pneu {
public:
    float Velocidade;
    int NumeroVoltas;
    char TipoPneu;  // 's' para soft, 'm' para medium, 'h' para hard
    float Desgaste;

    Pneu(char TipoPneu) {
        this->TipoPneu = TipoPneu;

        this->NumeroVoltas = 0;
        
        this->Desgaste = 0.0f;

        if (TipoPneu == 's') {
            Velocidade = S;  // Pneus soft são mais rápidos
        } else if (TipoPneu == 'm') {
            Velocidade = M;   // Pneus medium são medianos
        } else if (TipoPneu == 'h') {
            Velocidade = H;   // Pneus hard são mais lentos
        }
    }

    float CalcularVelocidade() {
        // Aqui podemos ajustar a velocidade com base no desgaste
        return Velocidade - Desgaste * 0.1f;  // Exemplo simples de cálculo de velocidade baseado no desgaste
    }

    void DesgastarPneu() {
        // O desgaste depende do tipo do pneu
        if (TipoPneu == 's') {
            Desgaste += 0.3f;  // Pneus soft desgastam mais rápido
        } else if (TipoPneu == 'm') {
            Desgaste += 0.2f;  // Pneus medium desgastam a uma taxa média
        } else if (TipoPneu == 'h') {
            Desgaste += 0.1f;  // Pneus hard desgastam mais lentamente
        }
    }
};

class Carro {
public:
    string Nome;
    Pneu* pneu;
    float distanciaPercorrida;
    float velocidade;

    Carro(char tipoPneu) {
        pneu = new Pneu(tipoPneu);
        distanciaPercorrida = 0.0;

        this->velocidade = (this->pneu)->CalcularVelocidade();
    }

    void FazerPitStop(char TipoPneu) {
        delete this->pneu;

        this->pneu = new Pneu(TipoPneu); //trocar o pneu para o novo escolhido
    }

    void Correr() {
        bool FezPitStop = false;
        while (distanciaPercorrida < DISTANCIA_TOTAL) {
            distanciaPercorrida += velocidade; //aumentar a distância percorrida baseada na velocidade

            char EscolhaFazerPitStop;
            cin >> EscolhaFazerPitStop; //s ou n

            if (desejaPitStop.load(memory_order_relaxed) == true){ //significa que o usuário quer fazer o pitstop
                semaforo.lock(); //tentar acessar o PitStop
                FazerPitStop('s'); 

                //obs aqui tem que ver como é que vai fazer para descobrir pela E/S qual o tipo de pneu que ele vai colocar

                semaforo.unlock();

                desejaPitStop.store(false, memory_order_relaxed); //coloca como falso
            }

            float velocidade = pneu->CalcularVelocidade(); //calcular qual que vai ser a velocide

            pneu->DesgastarPneu(); //desgastar o pneu
            
        }
    }
};

class FazerES {
    void escolhaPitstop() {
        while (true) { //tem que ver isso daqui depois, pois se n isso daqui vai rodar pra sempre
            char escolha;
            cout << "Deseja fazer um pit stop? (s/n): ";
            cin >> escolha;
            
            if (escolha == 's' || escolha == 'S') {
                desejaPitStop.store(true, memory_order_relaxed); //deixa ela como verdadeira
            }
        }
    }
};