#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

mutex pitstop_mutex;  // Mutex para sincronizar o pitstop

#define S 2
#define M 1.2
#define H 1.5

class Pneu {
public:
    float Velocidade;
    int NumeroVoltas;
    char TipoPneu;  // s para soft, m para medium, h para hard
    float Desgaste;

public:
    // Construtor
    Pneu(char TipoPneu) {
        this->TipoPneu = TipoPneu;
        this->NumeroVoltas = 0;
        this->Desgaste = 0.0f;

        // Define a velocidade com base no tipo de pneu
        if (TipoPneu == 's') {
            Velocidade = 10.0f;  // Pneus soft são mais rápidos
        } else if (TipoPneu == 'm') {
            Velocidade = 8.0f;   // Pneus medium são medianos
        } else if (TipoPneu == 'h') {
            Velocidade = 6.0f;   // Pneus hard são mais lentos
        } else {
            Velocidade = 0.0f;   // Caso um tipo inválido seja passado
        }
    }

    // Método para atualizar o desgaste do pneu
    void atualizarDesgaste() {
        // O desgaste depende do tipo do pneu
        if (TipoPneu == 's') {
            Desgaste += 0.3f;  // Pneus soft desgastam mais rápido
        } else if (TipoPneu == 'm') {
            Desgaste += 0.2f;  // Pneus medium desgastam a uma taxa média
        } else if (TipoPneu == 'h') {
            Desgaste += 0.1f;  // Pneus hard desgastam mais lentamente
        }

        // Evitar que o desgaste ultrapasse 10
        if (Desgaste > 10.0f) {
            Desgaste = 10.0f;  // Limita o desgaste no máximo
        }
    }

    // Método para trocar o pneu
    void trocarPneu() {
        Desgaste = 0.0f;  // Após a troca, o desgaste é resetado
        NumeroVoltas = 0;  // Resetar o número de voltas
    }
};

class Carro {
private:
    int id;
    float posicao;  // Posição na pista
    Pneu* pneu;     // Ponteiro para o objeto Pneu

public:
    // Construtor
    Carro(int id, Pneu* pneu) {
        this->id = id;
        this->posicao = 0.0f;
        this->pneu = pneu;
    }

    // Método para mover o carro
    void mover() {
        while (true) {
            // Simula o movimento do carro somando a posição de acordo com a velocidade do pneu
            posicao += pneu->Velocidade;

            // Atualizar o desgaste do pneu a cada volta
            pneu->atualizarDesgaste();
            if (pneu->Desgaste >= 10.0f) {
                cout << "Carro " << id << " - Pitstop necessário! Troca de pneus." << endl;
                pneu->trocarPneu();  // Troca o pneu quando o desgaste atinge 10
            }

            // Exibir o status
            cout << "Carro " << id << " - Posição: " << posicao 
                      << " - Desgaste do pneu: " << pneu->Desgaste << endl;

            // Simula o tempo de corrida (pausa)
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
};

