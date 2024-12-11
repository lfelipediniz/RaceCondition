#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib> // Para rand() e srand()
#include <iomanip> // Para formatação da tabela
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Definição da Classe Carro
class Carro {
public:
    std::string nome;
    int posicao;
    int desgaste_pneu;

    Carro(std::string n) : nome(n), posicao(0), desgaste_pneu(0) {}
};

// Função para limpar o terminal
void limparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para atualizar a posição dos carros
void atualizarPosicoes(std::vector<Carro> &carros, int comprimento_pista) {
    for(auto &carro : carros) {
        // Incrementa a posição aleatoriamente
        carro.posicao += rand() % 100 + 1; // Avança entre 1 e 10 unidades
        // Incrementa o desgaste do pneu
        carro.desgaste_pneu += rand() % 5; // Desgaste entre 0 e 4
        // Verifica se ultrapassou o comprimento da pista
        if(carro.posicao > comprimento_pista) {
            carro.posicao = comprimento_pista;
        }
    }
}

// Função para ordenar os carros com base na posição
std::vector<Carro> ordenarClassificacao(std::vector<Carro> carros) {
    std::vector<Carro> classificacao = carros;
    std::sort(classificacao.begin(), classificacao.end(), [](const Carro &a, const Carro &b) {
        return a.posicao > b.posicao;
    });
    return classificacao;
}

// // Função para desenhar a pista e os carros
// void desenharPista(const std::vector<Carro> &carros, int comprimento_pista) {
//     // Representação da pista
//     std::cout << "Pista:\n";
//     for(int i = 0; i < 4; ++i) { // Para cada carro
//         std::cout << carros[i].nome << ": ";
//         int pos = carros[i].posicao;
//         if(pos > comprimento_pista) pos = comprimento_pista;
//         for(int j = 0; j < pos; ++j) {
//             std::cout << "-";
//         }
//         std::cout << "🏎️\n"; // Emoji do carro
//     }
// }


void desenharPista(const std::vector<Carro> &carros, int comprimento_pista) {
    int tamanho_visivel = 50; // Comprimento visível da pista

    std::cout << "\nPista:\n";
    for (const auto &carro : carros) {
        std::cout << carro.nome << ": ";

        // Calcula a posição na pista visível (1 traço para cada 2 unidades percorridas)
        int sub = std::min(tamanho_visivel, static_cast<int>(std::floor(carro.posicao / 20.0)));
        int pos = tamanho_visivel - sub;

        // Desenha os traços restantes até a chegada
        for (int j = 0; j < pos; ++j) {
            std::cout << " ";
        }
        std::cout << "🏎️"; // Emoji do carro
        std::cout << std::string(sub, ' ');
        std::cout << "#\n";
    }
}

// Função para exibir a tabela de classificação
void exibirTabela(const std::vector<Carro> &classificacao) {
    std::cout << "\nClassificação:\n";
    std::cout << "+---------+----------+---------------+-----------+---------+\n";
    std::cout << "| Posição |   Carro  | Desgaste Pneu | Tipo Pneu | Pitstop |\n";
    std::cout << "+---------+----------+---------------+-----------+---------+\n";

    for (int i = 0; i < classificacao.size(); ++i) {
        std::cout << "| " << std::setw(7) << (i + 1) << " | "
                  << std::setw(8) << classificacao[i].nome << " | "
                  << std::setw(13) << classificacao[i].desgaste_pneu << " | "
                  << std::setw(9) << "Macio" << " | "
                  << std::setw(7) << "Sim" << " |\n";
    }

    std::cout << "+---------+----------+---------------+-----------+---------+\n";
}

int main() {
    srand(time(0)); // Semente para geração aleatória

    int comprimento_pista = 1000; // Comprimento total da pista

    // Inicializa os carros
    std::vector<Carro> carros;
    carros.emplace_back("Carro 1");
    carros.emplace_back("Carro 2");
    carros.emplace_back("Carro 3");
    carros.emplace_back("Carro 4");

    bool corrida_ativa = true;

    while(corrida_ativa) {
        limparTerminal();
        atualizarPosicoes(carros, comprimento_pista);
        desenharPista(carros, comprimento_pista);
        std::vector<Carro> classificacao = ordenarClassificacao(carros);
        exibirTabela(classificacao);

        // Verifica se algum carro terminou a corrida
        for(auto &carro : carros) {
            if(carro.posicao >= comprimento_pista) {
                corrida_ativa = false;
                std::cout << "\n" << carro.nome << " venceu a corrida!\n";
                break;
            }
        }

        // Aguarda um pouco antes da próxima atualização
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
