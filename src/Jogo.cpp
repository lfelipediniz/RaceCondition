#include "../include/Jogo.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

//construtor
Jogo::Jogo(string nomeJogador) {
    this->jogador = new Player(nomeJogador, 'm', pitstopMutex); // começa com pneu médio
}

// desalocando o jogador
Jogo::~Jogo() {
    if (jogador != nullptr)
    {
        delete jogador;
        jogador = nullptr;
    }
}

void Jogo::iniciar() {
    thread threadCorrida(&Carro::correr, jogador->getCarro()); // inicia a thread do carro
    thread threadControle(&Player::controlar, jogador);        // inicia a thread de controle do jogador

    while (jogador->getCarro()->distanciaPercorrida < DISTANCIA_TOTAL)
    {
        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para encerrar as threads
    }

    // aguarda a conclusão das thread corrida
    threadCorrida.join();
    // desanexa a thread controle do programa principal, assim ela consegue executar de maneira independente
    threadControle.detach();

    cout << "Fim da corrida! Parabéns, " << jogador->getNome() << "!\n";
}
    /*
    void desenharPista(vetor com os carros (ou passa todos os carros), comprimento da pista) {
        cout << "Pista:\n";

        //caso seja um vetor de carros, sera um for:
        for(int i = 0; i < 4; ++i) { // Para cada carro
            cout << carros[i].nome << ": ";
            int pos = carros[i].posicao;
            if(pos > comprimento_pista) pos = comprimento_pista;
            for(int j = 0; j < pos; ++j) {
                cout << "-";
            }
        cout << "🏎️\n"; // Emoji do carro, da pra mudar pra outra representação do carro
        }

        //caso contrario, tera q fazer um print pra cada carro separadamente, me avisem que eu faço
    }

    void mostrarTabela() {
        cout << "\nClassificação:\n";
        cout << "+---------+----------+---------------+-----------+---------+\n";
        cout << "| Posição |   Carro  | Desgaste Pneu | Tipo Pneu | Pitstop |\n";
        cout << "+---------+----------+---------------+-----------+---------+\n";

        for (int i = 0; i < classificacao.size(); ++i) {
            cout << "| " << setw(7) << (i + 1) << " | "
                    << setw(8) << classificacao[i].nome << " | "
                    << setw(13) << classificacao[i].desgaste_pneu << " | "
                    << setw(9) << "Macio" << " | "
                    << setw(7) << "Sim" << " |\n";
        }

        cout << "+---------+----------+---------------+-----------+---------+\n";
    }
    
    */