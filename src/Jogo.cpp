#include "../include/Jogo.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

//construtor
Jogo::Jogo(string nomeJogador, char pneuInicial) : PosicaoDoCarro(1) {
    this->jogador = new Player(nomeJogador, pneuInicial, pitstopMutex, OrdemDeChegada, PosicaoDoCarro); // começa com pneu médio
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

    IAs.emplace_back(new IA("Max Verstapo",  pitstopMutex, OrdemDeChegada, PosicaoDoCarro));
    IAs.emplace_back(new IA("Leo Leclerc", pitstopMutex, OrdemDeChegada, PosicaoDoCarro));
    IAs.emplace_back(new IA("Luiz Hamilltown", pitstopMutex, OrdemDeChegada, PosicaoDoCarro));
    IAs.emplace_back(new IA("Borboleto", pitstopMutex, OrdemDeChegada, PosicaoDoCarro));

    for (auto& ia:IAs){
        threads.emplace_back(&Carro::correr, ia->getCarro());
        threads.emplace_back(&IA::controlar, ia);
        Carros.emplace_back(ia->getCarro());
    }

    threads.emplace_back(&Carro::correr, jogador->getCarro());
    Carros.emplace_back(jogador->getCarro());
    threads.emplace_back(&Player::controlar, jogador);
    threads.emplace_back(&Jogo::desenharPista, this, Carros);
    
    // esperando todas as threads terminarem
    for (auto& t:threads){
        t.join();
    }

    cout << "Fim da corrida! Parabéns, " << jogador->getNome() << "!\n";
}


// ordenando os carros pela distância percorrida
vector<Carro*> ordenarClassificacao(vector<Carro*> carros) {
    vector<Carro*> classificacao = carros;
    sort(classificacao.begin(), classificacao.end(),  [](const Carro *a, const Carro *b) {
        return a->distanciaPercorrida >= b->distanciaPercorrida;
   });
    return classificacao;
}

// printando a tabela de classificação dos carrinhos
void exibirTabela(const vector<Carro*> classificacao) {
    cout << fixed << setprecision(1);

    cout << "\nClassificação:\n";
    cout << "+---------+----------------------+---------------+-----------+-----------+----------+\n";
    cout << "| Posição |        Carro         | Desgaste Pneu | Tipo Pneu |  Pitstop  | Situação |\n";
    cout << "+---------+----------------------+---------------+-----------+-----------+----------+\n";

    
    for (int i = 0; i < 5; ++i) {
        string situacao;
        
        if (classificacao[i]->EstourouPneu) situacao = "    ❌ ";
        else if (classificacao[i]->ChegouNaLargada) situacao = "      🏁 ";
        else situacao = "      🏎️  ";

        cout << "| " << setw(7) << (i + 1) << " | "
                  << classificacao[i]->getNomeCarro() << setw(23 - classificacao[i]->getNomeCarro().size()) << " | "
                  << setw(13) << classificacao[i]->pneu->desgaste << " | "
                  << setw(9) << classificacao[i]->pneu->tipo << " | "
                  << setw(9) <<(classificacao[i]->DentroPitStop.load() ? "Sim" : "Nao") << " | "
                  << setw(8) << situacao << "|\n";
    }
    cout << "+---------+----------------------+---------------+-----------+-----------+----------+\n";

    cout << "Para entrar no pit stop, digite o pneu (s, m, h) para o qual deseja trocar. O pit stop precisa estar liberado 🚦\n";

}

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// printando a pista com os carrinhos em suas posições
void Jogo::desenharPista(const vector<Carro*> carros) {
    int contador = 0;

    while (true) {
        limparTerminal();
        
        int tamanho_visivel = 50; 

        cout << "\nPista:\n";
        for (const auto &carro : carros) { //isso daqui GERA race condition
            cout << carro->getNomeCarro() << ": " << setw(20 - carro->getNomeCarro().size());
            cout << "🏁";

            // calculadno a posição na pista visível (1 traço para cada 2 unidades percorridas)
            int sub = min(tamanho_visivel, static_cast<int>(floor(carro->distanciaPercorrida.load() / 2.0)));
            int pos = tamanho_visivel - sub;

            // desenha os traços restantes até a chegada
            for (int j = 0; j < pos; ++j) {
                cout << " ";
            }
            cout << "🏎️"; 
            cout << string(sub, ' ');
            cout << "  |\n";
        }

        vector<Carro*> classificacao = ordenarClassificacao(carros);

        exibirTabela(classificacao);       
        this_thread::sleep_for(chrono::seconds(1)); 

        if (contador >= 5){
            cout << flush << "Aberte Enter para finalizar a corrida!\n" << flush;
            break;
        } 

        contador = 0;

        for (const auto& carro: carros){
            //verificar se os 5 carros chegaram na linha ou estão fora da corrida
            if ((carro->ChegouNaLargada) || (carro->EstourouPneu)) contador ++;
        }
    }
}