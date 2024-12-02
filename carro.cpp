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
#define DISTANCIA_TOTAL 1000  // Distância total da corrida (por exemplo, 100 metros ou 100 voltas)

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

    // Método para simular o movimento do carro
    void correr() {
        while (posicao < DISTANCIA_TOTAL) {
            // Simula o desgaste dos pneus
            pneu->atualizarDesgaste();

            // Move o carro de acordo com a velocidade do pneu
            posicao += pneu->Velocidade;

            // Se o desgaste atingir 10, o carro vai para o pitstop
            if (pneu->Desgaste >= 10.0f) {
                fazerPitstop();
            }

            cout << "Carro " << id << " - Posição: " << posicao << " - Desgaste do pneu: " << pneu->Desgaste << endl;

            // Atraso para simular o tempo de uma volta
            this_thread::sleep_for(chrono::milliseconds(500));
        }

        cout << "Carro " << id << " completou a corrida!" << endl;
    }

    // Método para simular o pitstop (onde o carro troca os pneus)
    void fazerPitstop() {
        lock_guard<mutex> lock(pitstop_mutex);  // Garantir que o pitstop é feito de forma sincronizada
        cout << "Carro " << id << " está fazendo pitstop!" << endl;
        this_thread::sleep_for(chrono::seconds(2));  // Simula o tempo do pitstop

        // Trocar os pneus
        pneu->trocarPneu();
    }
};

int main() {
    // Criando pneus para cada carro
    Pneu pneu1('s');  // Soft
    Pneu pneu2('m');  // Medium

    // Criando carros
    Carro carro1(1, &pneu1);
    Carro carro2(2, &pneu2);

    // Criando threads para os carros
    thread t1(&Carro::correr, &carro1);
    thread t2(&Carro::correr, &carro2);

    // Espera as threads terminarem
    t1.join();
    t2.join();

    return 0;
}
