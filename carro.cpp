#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

mutex pitstop_mutex;  // Mutex para sincronizar o pitstop
mutex user_input_mutex; // Mutex para controlar o input do usuário

#define S 2
#define M 1.5 
#define H 1.2
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
    bool fazendoPitStop;
    bool fezPitStop;

    Carro(string nome, char tipoPneu) {
        Nome = nome;
        pneu = new Pneu(tipoPneu);
        distanciaPercorrida = 0.0f;
        fazendoPitStop = false;

        this->fezPitStop = false;
    }

    void FazerPitStop(char TipoPneu) {
        delete this->pneu;

        this->pneu = new Pneu(TipoPneu); //trocar o pneu para o novo escolhido

        fazendoPitStop = false; //marcar que saiu do pistop
        }

    void Correr() {
        while (distanciaPercorrida < DISTANCIA_TOTAL) {
            if (fazendoPitStop){
                
            }
            if (!fazendoPitStop) {
                float velocidade = pneu->CalcularVelocidade(); //calcular qual que vai ser a velocide

                if (fezPitStop == 1){
                    velocidade -= 0.3 ; //tempo que o carro perdeu durante a volta por ter feito um pitstop
                }

                pneu->DesgastarPneu(); //desgastar o pneu

                distanciaPercorrida += velocidade; //aumentar a distância percorrida
            }
        }
    }
};