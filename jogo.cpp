using namespace std;

#include <atomic>
#include <vector>



#include "jogo.h"
#include "carro.h"

atomic<bool> desejaPitStop(false); //declara uma região crítica atomica para o carro do usuário poder verificar se ele deve tentar entrar no PitStop ou não sem perder tempo tendo que esperar a operação de E/S
mutex semaforo; //semáforo para acessar o PitStop


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
    
    void Jogo::iniciar() {
        for (auto& carro : carros) { 
            threads.push_back(thread(&Carro::Correr, &carro)); // Iniciando threads de cada carro
        }

        for (auto& t : threads) {
            t.join(); // Espera todas as threads terminarem (neste caso, são loops infinitos)
        }
    }
};