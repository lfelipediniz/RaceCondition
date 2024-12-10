#include "../include/Carro.h"
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <cctype>

using namespace std;

#define S 2.0
#define M 1.5 
#define H 1.0
#define DISTANCIA_TOTAL 1000  // distância total da corrida

class Pneu {
public:
    float Velocidade;
    int NumeroVoltas;
    char TipoPneu;  // 's', 'm', 'h'
    float Desgaste;

    Pneu(char TipoPneu) {
        this->TipoPneu = TipoPneu;
        this->NumeroVoltas = 0;
        this->Desgaste = 0.0f;

        if (TipoPneu == 's') {
            Velocidade = S;
        } else if (TipoPneu == 'm') {
            Velocidade = M;
        } else if (TipoPneu == 'h') {
            Velocidade = H;
        }
    }

    float CalcularVelocidade() {
        return Velocidade - Desgaste * 0.1f;
    }

    void DesgastarPneu() {
        if (TipoPneu == 's') {
            Desgaste += 0.3f;
        } else if (TipoPneu == 'm') {
            Desgaste += 0.2f;
        } else if (TipoPneu == 'h') {
            Desgaste += 0.1f;
        }
    }
};

Carro::Carro(char tipoPneu, mutex& semaforo_ref, atomic<bool>& desejaPitStop_ref, atomic<char>& tipoPneuEscolhido_ref, atomic<bool>& corridaTerminou_ref)
    : semaforo(semaforo_ref), desejaPitStop(desejaPitStop_ref), tipoPneuEscolhido(tipoPneuEscolhido_ref), corridaTerminou(corridaTerminou_ref) {
    pneu = new Pneu(tipoPneu);
    distanciaPercorrida = 0.0f;
    velocidade = pneu->CalcularVelocidade();
}

Carro::~Carro() {
    delete pneu;
}

void Carro::FazerPitStop(char TipoPneu) {
    cout << "fazendo pit stop para trocar o pneu para " << TipoPneu << endl;
    delete pneu;
    pneu = new Pneu(TipoPneu);
    velocidade = pneu->CalcularVelocidade();
    cout << "pit stop concluído. velocidade atual: " << velocidade << endl;
}

void Carro::Correr() {
    while (distanciaPercorrida < DISTANCIA_TOTAL) {
        // simula o tempo passando
        this_thread::sleep_for(chrono::seconds(1));

        // atualiza a distância percorrida
        distanciaPercorrida += velocidade;
        cout << "distância percorrida: " << distanciaPercorrida << " / " << DISTANCIA_TOTAL << endl;

        // tem necessidade de pit stop?
        if (desejaPitStop.load(memory_order_relaxed)) {
            semaforo.lock();

            char tipo = tipoPneuEscolhido.load(memory_order_relaxed);
            // garantir que o tipo seja minúsculo
            tipo = tolower(tipo);
            if (tipo != 's' && tipo != 'm' && tipo != 'h') {
                cout << "tipo de pneu inválido. mantendo pneu atual." << endl;
                tipo = pneu->TipoPneu; // mantém o pneu atual
            }

            FazerPitStop(tipo);

            semaforo.unlock();

            desejaPitStop.store(false, memory_order_relaxed);
        }

        // atualiza a velocidade e o desgaste
        velocidade = pneu->CalcularVelocidade();
        pneu->DesgastarPneu();

        // exibe o status atual
        cout << "tipo de pneu: " << pneu->TipoPneu << ", desgaste: " << pneu->Desgaste << ", velocidade: " << velocidade << endl;

        // verifica se o pneu estourou
        if (pneu->Desgaste >= 10.0f) {
            cout << "pneu estourou! você perdeu a corrida." << endl;
            break;
        }
    }

    if (distanciaPercorrida >= DISTANCIA_TOTAL) {
        cout << "parabéns! você venceu a corrida!" << endl;
    }

    // sinaliza que a corrida terminou
    corridaTerminou.store(true);
}

FazerES::FazerES(atomic<bool>& desejaPitStop_ref, atomic<char>& tipoPneuEscolhido_ref, atomic<bool>& corridaTerminou_ref)
    : desejaPitStop(desejaPitStop_ref), tipoPneuEscolhido(tipoPneuEscolhido_ref), corridaTerminou(corridaTerminou_ref) {}

void FazerES::escolhaPitstop() {
    while (!corridaTerminou.load()) {
        char escolha;
        cout << "deseja fazer um pit stop? (s/n): ";
        cin >> escolha;

        if (escolha == 's' || escolha == 'S') {
            desejaPitStop.store(true, memory_order_relaxed);
            // pergunta o tipo de pneu
            char tipo;
            cout << "escolha o tipo de pneu para troca (s/m/h): ";
            cin >> tipo;

            // valida o tipo de pneu
            tipo = tolower(tipo);
            if (tipo != 's' && tipo != 'm' && tipo != 'h') {
                cout << "tipo de pneu inválido. mantendo pneu atual." << endl;
                // definindo um tipo padrão de pneu
            } else {
                tipoPneuEscolhido.store(tipo, memory_order_relaxed);
            }
        } 
        // previne loop intenso
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
