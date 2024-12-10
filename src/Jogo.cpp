using namespace std;

#include <atomic>
#include <vector>

#include "../include/Jogo.hpp"
#include "../include/Carro.hpp"


class Jogo {
private:
    vector<Carro> carros;
    vector<thread> threads;

public:
    Jogo(int numCarros){
        //criar uma lista de carros
        for (int i = 0; i < 1; ++i) {
            carros.push_back(Carro('s')); // Criando carros
        }
    }
    
    void iniciar() {
        for (auto& carro : carros) { 
            threads.push_back(thread(&Carro::Correr, &carro)); // Iniciando threads de cada carro
        }

        for (auto& t : threads) {
            t.join(); // Espera todas as threads terminarem (neste caso, são loops infinitos)
        }
    }
    void exibirStatusCorrida() {
        
    while (true) {
        limparTela(); // Limpa o terminal para atualizar o status
        // Ordena os corredores pela distância percorrida (em ordem decrescente)
        std::sort(corredores.begin(), corredores.end(), [](const Corredor &a, const Corredor &b) {
            return a.distancia > b.distancia;
        });
        std::cout << "===== Status da Corrida =====\n\n";
        // Exibe a colocação dos corredores
        for (size_t i = 0; i < corredores.size(); ++i) {
            std::cout << i + 1 << "º Lugar: " << corredores[i].nome 
                      << " - Distância: " << corredores[i].distancia << " unidades";
            if (corredores[i].noPitStop) {
                std::cout << " (No Pit Stop)";
            }
            std::cout << "\n";
        }
        // Exibe quem está no pit stop
        std::cout << "\n--- Pit Stop ---\n";
        bool alguemNoPitStop = false;
        for (const auto &corredor : corredores) {
            if (corredor.noPitStop) {
                std::cout << corredor.nome << " está no pit stop.\n";
                alguemNoPitStop = true;
            }
        }
        if (!alguemNoPitStop) {
            std::cout << "Ninguém está no pit stop.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Atualiza a cada segundo
    }
    }
};

int main() {
    Jogo *jogo = new Jogo(2);

    jogo->iniciar();
}