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
        float velocidade;
        int NumeroVoltas;
        char TipoPneu; //s para soft; m para medium; h para hard

    public:
        Pneu(int id, char TipoPneu){
            this->TipoPneu = TipoPneu; //setar o tipo do pneu
            this->NumeroVoltas = 0; //setar o número de voltas do pneu
        };

        float CalcularVelocidade(){
            //retorna a velocidade do carro baseado no tipo de pneu que ele está usando
            if (this->TipoPneu == 's'){
                return S - NumeroVoltas*0.2;
            }
    
            if (this->TipoPneu == 'm'){
                return M - NumeroVoltas*0.1;
            }

            return H - NumeroVoltas*0.05;
        }

        float Aumentarvolta(){
            this->NumeroVoltas += 1;
        }
};

class Carro {
private:
    int id;
    float posicao;  // Posição na pista
    string tipo_pneu;
    float velocidade;
    float desgaste_pneu;
    int tempo_troca_pneu;

public:
    Carro(int id, string tipo_pneu)
        : id(id), posicao(0), tipo_pneu(tipo_pneu), desgaste_pneu(0), tempo_troca_pneu(0) {
        // Definir a velocidade com base no tipo de pneu
        if (tipo_pneu == "soft") {
            velocidade = 10.0f;  // Exemplo: pneus macios são mais rápidos
        } else if (tipo_pneu == "medium") {
            velocidade = 8.0f;
        } else if (tipo_pneu == "hard") {
            velocidade = 6.0f;
        }
    }

    void mover() {
        while (true) {
            // Simula o movimento do carro somando a posição de acordo com a velocidade
            posicao += velocidade;

            // A cada "tempo_troca_pneu" o desgaste aumenta
            desgaste_pneu += 0.1f;
            if (desgaste_pneu >= 10.0f) {
                // Trocar o pneu
                realizarPitstop();
                desgaste_pneu = 0.0f;  // Resetar o desgaste após o pitstop
            }

            // Exibir o status a cada iteração
            cout << "Carro " << id << " - Posição: " << posicao << " - Desgaste do pneu: " << desgaste_pneu << endl;

            // Simula o tempo de corrida
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

    void realizarPitstop() {
        // Área crítica para trocar o pneu (com mutex)
        lock_guard<mutex> lock(pitstop_mutex);
        cout << "Carro " << id << " está fazendo o pitstop para trocar os pneus!" << endl;

        // Simula o tempo de troca de pneus (exemplo: 3 segundos)
        this_thread::sleep_for(chrono::seconds(3));

        // Após o pitstop, podemos mudar o tipo de pneu, se necessário
        tipo_pneu = "medium";  // Exemplo: após o desgaste, troca para pneus médios
        cout << "Carro " << id << " trocou para pneus " << tipo_pneu << endl;
    }
};

int main() {
    vector<thread> carros_threads;
    vector<Carro> carros;

    // Criando 5 carros com diferentes tipos de pneus
    for (int i = 0; i < 5; ++i) {
        string tipo_pneu = (i % 3 == 0) ? "soft" : (i % 3 == 1) ? "medium" : "hard";
        carros.push_back(Carro(i, tipo_pneu));
        carros_threads.push_back(thread(&Carro::mover, &carros[i]));
    }

    // Esperar todas as threads terminarem (simulação contínua)
    for (auto& t : carros_threads) {
        t.join();
    }

    return 0;
}
