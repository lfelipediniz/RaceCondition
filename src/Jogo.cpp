/*
Nomes dos integrantes e nUSP:

Enzo Tonon Morente - 14568476
João Pedro Alves Notari Godoy - 14582076
Letícia Barbosa Neves - 14588659
Luiz Felipe Diniz Costa - 13782032
*/

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

    // cria os 4 jogadores controlados por IA
    IAs.emplace_back(new IA("Max Verstapo",  pitstopMutex, OrdemDeChegada, PosicaoDoCarro));
    IAs.emplace_back(new IA("Leo Leclerc", pitstopMutex, OrdemDeChegada, PosicaoDoCarro));
    IAs.emplace_back(new IA("Luiz Hamilltown", pitstopMutex, OrdemDeChegada, PosicaoDoCarro));
    IAs.emplace_back(new IA("Borboleto", pitstopMutex, OrdemDeChegada, PosicaoDoCarro));

    // cria uma thread para cada um deles
    for (auto& ia:IAs){
        threads.emplace_back(&Carro::correr, ia->getCarro());
        threads.emplace_back(&IA::controlar, ia);
        Carros.emplace_back(ia->getCarro());
    }

    // cria todas as threads para o funcionamento do jogador 
    threads.emplace_back(&Carro::correr, jogador->getCarro());
    Carros.emplace_back(jogador->getCarro());
    threads.emplace_back(&Player::controlar, jogador);
    threads.emplace_back(&Jogo::desenharPista, this, Carros);
    
    // esperando todas as threads terminarem
    for (auto& t:threads){
        t.join();
    }
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
    //fixa 1 casa decimal para o float
    cout << fixed << setprecision(1);

    //print da primeira linha da tabela, que sera fixa
    cout << "\nClassificação:\n";
    cout << "+---------+----------------------+---------------+-----------+-----------+----------+\n";
    cout << "| Posição |        Carro         | Desgaste Pneu | Tipo Pneu |  Pitstop  | Situação |\n";
    cout << "+---------+----------------------+---------------+-----------+-----------+----------+\n";

    //print das linhas para cada um dos 5 carros, com todas as informacoes de cada corredor
    for (int i = 0; i < 5; ++i) {
        string situacao;
        
        //para o print da situaçao do carro, para indicar se
        if (classificacao[i]->EstourouPneu) situacao = "      ❌ ";
        else if (classificacao[i]->ChegouNaLargada) situacao = "      🏁 ";
        else situacao = "      🏎️  ";
        
        cout << "| " << setw(7) << (i + 1) << " | "
                  << classificacao[i]->getNomeCarro() << setw(23 - classificacao[i]->getNomeCarro().size()) << " | " //print do nome do corredor
                  << setw(13) << classificacao[i]->pneu->desgaste << " | " //print do nivel de desgaste atual do pneu
                  << setw(9) << classificacao[i]->pneu->tipo << " | " //print do tipo do pneu
                  << setw(9) <<(classificacao[i]->DentroPitStop.load() ? "Sim" : "Nao") << " | " //print que diz se o carro esta ou nao no pitstop no momento
                  << setw(8) << situacao << "|\n"; //print da situacao do carro
    }

    //print fim da tabela
    cout << "+---------+----------------------+---------------+-----------+-----------+----------+\n";

    cout << "Para entrar no pit stop, digite o pneu (s, m, h) para o qual deseja trocar. O pit stop precisa estar liberado 🚦\n";
}

// função que limpa o terminal de acordo com o sistemaa operacional 
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
        
        // tamanho que "falta para terminar"
        int tamanho_visivel = 50; 

        cout << "\nPista:\n";
        for (const auto &carro : carros) { 
            // exibe o nome do carro (mesmo que o nome do jogador) e exibe a bandeira da chegada
            cout << carro->getNomeCarro() << ": " << setw(20 - carro->getNomeCarro().size());
            cout << "🏁";

            // calculando a posição na pista visível (1 traço para cada 2 unidades percorridas)
            int sub = min(tamanho_visivel, static_cast<int>(floor(carro->distanciaPercorrida.load() / 2.0)));
            int pos = tamanho_visivel - sub;

            // desenha os traços restantes até a chegada
            for (int j = 0; j < pos; ++j) {
                cout << " ";
            }
            // exibe o carro e o espaço vazio entre ele e o início da corrida
            cout << "🏎️"; 
            cout << string(sub, ' ');
            cout << "  |\n";
        }

        // ordena vetor com todos os carros
        vector<Carro*> classificacao = ordenarClassificacao(carros);
        
        // exibe a tabela com a classificação atual
        exibirTabela(classificacao);       
        this_thread::sleep_for(chrono::seconds(1)); 

        // se o contador chega em 5, significa que todos os carros já chegaram ao final da pista
        if (contador >= 5){
            cout << flush << "\n\nAperte Enter para finalizar a corrida!\n" << flush;
            break;
        } 

        // inicializa o contador com 0
        contador = 0;

        for (const auto& carro: carros){
            //verificar se os 5 carros chegaram na linha ou estão fora da corrida
            if ((carro->ChegouNaLargada) || (carro->EstourouPneu)) contador ++;
        }
    }
}