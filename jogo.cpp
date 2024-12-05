using namespace std;

#include <atomic>
#include <vector>

#include "jogo.hpp"
#include "carro.hpp"


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
};

int main() {
    Jogo *jogo = new Jogo(2);

    jogo->iniciar();
}


