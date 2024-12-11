#include "../include/Jogo.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iomanip>

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
    IAs.emplace_back(new IA("Max Verstapo", 's', pitstopMutex));
    IAs.emplace_back(new IA("Leo Leclerc", 'm', pitstopMutex));
    IAs.emplace_back(new IA("Luiz Hamilltown", 'h', pitstopMutex));

    for (auto& ia:IAs){
        threads.emplace_back(&Carro::correr, ia->getCarro());
        threads.emplace_back(&IA::controlar, ia);
        Carros.emplace_back(ia->getCarro());
    }

    threads.emplace_back(&Carro::correr, jogador->getCarro());
    Carros.emplace_back(jogador->getCarro());

    threads.emplace_back(&Player::controlar, jogador);

    threads.emplace_back(&Jogo::desenharPista, this, Carros);
    

    //se ta dando errado pode ser esse while aqui que eu não sei para q serve
    /*while (jogador->getCarro()->distanciaPercorrida < DISTANCIA_TOTAL)
    {
        this_thread::sleep_for(chrono::seconds(1)); // espera 1 segundo para encerrar as threads
    }*/ 

    for (auto& t:threads){
        t.join();
    }

    cout << "Fim da corrida! Parabéns, " << jogador->getNome() << "!\n";
}

// printando a tabela de classificação dos carrinhos
void exibirTabela(const vector<Carro*> carros) {
    cout << "\nClassificação:\n";
    cout << "+---------+----------------------+---------------+-----------+-----------+\n";
    cout << "| Posição |        Carro         | Desgaste Pneu | Tipo Pneu |  Pitstop  |\n";
    cout << "+---------+----------------------+---------------+-----------+-----------+\n";

    

    for (const auto &carro : carros) {
        cout << "| " << setw(7) << (i + 1) << " | "
            << setw(20) << carro->GetNome() << " | "
            << setw(13) << carro->pneu->desgaste << " | "
            << setw(9) << carro->pneu->tipo << " | "
            << setw(9) << (carro->DentroPitStop.load() ? "Sim" : "Nao") << " |\n";
    }

    cout << "+---------+----------------------+---------------+-----------+-----------+\n";
}

// Função para limpar o terminal
void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// printando a pista com os carrinhos em suas posições
void Jogo::desenharPista(const vector<Carro*> carros) {
    while (true){
        limparTerminal();
        
        int tamanho_visivel = 50; // Comprimento visível da pista

        cout << "\nPista:\n";
        for (const auto &carro : carros) {
            cout << setw(20) << carro->GetNome() << ": ";

            // Calcula a posição na pista visível (1 traço para cada 2 unidades percorridas)
            int sub = min(tamanho_visivel, static_cast<int>(floor(carro->distanciaPercorrida / 20.0)));
            int pos = tamanho_visivel - sub;

            // Desenha os traços restantes até a chegada
            for (int j = 0; j < pos; ++j) {
                cout << " ";
            }
            cout << "🏎️"; // Emoji do carro
            cout << string(sub, ' ');
            cout << "#\n";
        }

        exibirTabela(carros);
        this_thread::sleep_for(chrono::seconds(1)); 
    }

}

