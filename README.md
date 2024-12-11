# RaceCondition - Manual do Jogo
![Capa do Jogo](/imgs/racecondition.png)

## Índice
1. [Introdução](#introdução)
2. [Requisitos](#requisitos)
3. [Instalação](#instalação)
4. [Como Jogar](#como-jogar)
5. [Cálculos e Lógica do Jogo](#cálculos-e-lógica-do-jogo)
6. [Implementação de Threads e Semáforos](#implementação-de-threads-e-semaforos)
7. [Implementação das Classes](#implementação-das-classes)
8. [Considerações Finais](#considerações-finais)
9. [Anexos](#anexos)
10. [Contato](#contato)


## Introdução

**RaceCondition** é uma simulação de corrida de Fórmula 1. O jogo permite que o jogador concorra contra quatro corredores controlados por Inteligência Artificial (IA). O principal foco do projeto é a aplicação prática de conceitos de **threads** e **semaforos** para gerenciar a concorrência e sincronização entre diferentes componentes do sistema.

O objetivo é proporcionar uma experiência interativa onde o jogador deve gerenciar estratégias de pit stop, escolhendo tipos de pneus adequados para vencer a corrida, enquanto lida com as decisões automáticas das IAs. A simulação destaca como múltiplas threads podem operar simultaneamente e como semáforos são utilizados para controlar o acesso a recursos compartilhados. 

## Requisitos

- **Compilador C++:** GCC ou Clang com suporte a C++20.
- **Make:** Utilitário de construção para compilar o projeto.



## Instalação

### Clone o repositório

```bash
git clone https://github.com/lfelipediniz/RaceCondition.git
```

```bash
cd RaceCondition
```

### Compile o jogo e execute

```bash
make
```

```bash
make run
```

## Como Jogar

### Início da Corrida

1. **Nome do Corredor**
    Ao iniciar o jogo, você será deverá inserir o nome do seu corredor.


2. **Escolha do Tipo de Pneu Inicial:**
   - Selecione o tipo de pneu para iniciar a corrida:
     - **s**: **SOFT** - Maior velocidade, maior desgaste.
     - **m**: **MEDIUM** - Velocidade intermediária, desgaste médio.
     - **h**: **HARD** - Menor velocidade, menor desgaste.

### Durante a Corrida

- **Monitoramento:**
  - A pista será exibida no terminal, mostrando a posição de cada corredor.
  - Uma tabela de classificação será atualizada a cada segundo, exibindo informações como desgaste dos pneus, tipo de pneu, status de pit stop e situação atual (em corrida, no pit stop ou eliminado).

- **Realizar Pit Stop:**
  - Quando julgar necessário, você pode optar por entrar no pit stop para trocar os pneus.
  - Para entrar no pit stop, digite:
    - **s**: Trocar para pneus **SOFT**.
    - **m**: Trocar para pneus **MEDIUM**.
    - **h**: Trocar para pneus **HARD**.
  - O pit stop ficará ocupado por 3 segundos, durante os quais nenhum outro carro poderá usa-lo.

- **Condições de Vitória:**
  - A corrida termina quando um dos corredores alcança a distância total de 100 kilometros.
  - Se um pneu estourar (desgaste atingir 10), o carro é eliminado da corrida.

### Final da Corrida
Quando oa corrida acaba, uma mensagem é exibida com os resultados finais e você será convidado a finalizar o jogo.

## Cálculos e Lógica do Jogo

### Desgaste dos Pneus

Cada tipo de pneu possui uma taxa de desgaste específica que incrementa a cada segundo de corrida:

- **SOFT (s):** Desgaste incrementa em **0.5** a cada segundo.
- **MEDIUM (m):** Desgaste incrementa em **0.3** a cada segundo.
- **HARD (h):** Desgaste incrementa em **0.1** a cada segundo.

Se o desgaste de um pneu atingir **10**, o pneu estoura e o carro é eliminado da corrida.

### Cálculo da Velocidade Instantânea

A velocidade de cada carro é calculada com base no tipo de pneu e no desgaste acumulado:

$$
\text{Velocidade} = \text{VelocidadeBase} - (\text{Desgaste} \times 0.1)
$$

Onde **VelocidadeBase** depende do tipo de pneu escolhido:

- **SOFT:** 2.1 unidades
- **MEDIUM:** 1.9 unidades
- **HARD:** 1.6 unidades

### Exemplos de Cálculo

1. **Carro com Pneu SOFT e Desgaste 3:**
   ```
   Velocidade = 2.1 - (3 * 0.1) = 2.1 - 0.3 = 1.8 unidades
   ```

2. **Carro com Pneu MEDIUM e Desgaste 5:**
   ```
   Velocidade = 1.9 - (5 * 0.1) = 1.9 - 0.5 = 1.4 unidades
   ```

3. **Carro com Pneu HARD e Desgaste 2:**
   ```
   Velocidade = 1.6 - (2 * 0.1) = 1.6 - 0.2 = 1.4 unidades
   ```

### Estratégia de Pit Stop

- **Jogador:**
  - O jogador pode optar por entrar no pit stop a qualquer momento para trocar os pneus, escolhendo entre SOFT, MEDIUM ou HARD.
  - Realizar um pit stop pausa o carro por 3 segundos, durante os quais o pneu é trocado e o desgaste é resetado.

- **Inteligências Artificiais (IA):**
  - Cada IA possui uma estratégia pré-definida para realizar pit stops, baseada no desgaste atual dos pneus.
  - As IAs decidem automaticamente quando realizar pit stops, seguindo suas preferências de tipos de pneus.

---

## Implementação de Threads e Semáforos

### Visão Geral

O **RaceCondition** utiliza **threads** e **semaforos** para gerenciar a concorrência entre múltiplos corredores (jogador e IAs) e para sincronizar o acesso a recursos compartilhados, como o pit stop.

### Threads

As **threads** permitem a execução simultânea de diferentes partes do programa, simulando a concorrência real de uma corrida. As principais threads implementadas são:

1. **Thread Principal:**
   - Responsável por iniciar a corrida e gerenciar as threads dos corredores.

2. **Threads das IAs:**
   - Cada corredor controlado por IA possui sua própria thread para gerenciar sua movimentação e estratégias de pit stop.

3. **Thread do Jogador:**
   - Monitora as entradas do usuário para realizar pit stops sem bloquear a execução das threads dos corredores.

4. **Thread de Desenho da Pista:**
   - Atualiza a visualização da pista e da tabela de classificação em tempo real.

### Semáforos

Os **semaforos** são utilizados para controlar o acesso a recursos compartilhados, garantindo que apenas uma thread possa acessar o recurso por vez, evitando condições de corrida.

- **Semáforo do Pit Stop:**
  - Implementado utilizando `std::mutex`.
  - Garante que apenas um carro (jogador ou IA) possa realizar um pit stop por vez.
  - Quando um carro entra no pit stop, o mutex é bloqueado, impedindo que outros carros acessem o pit stop simultaneamente.
  - Após a conclusão do pit stop, o mutex é liberado, permitindo que outro carro utilize o pit stop.

### Justificativa do Uso

- **Threads:**
  - Permitem simular a corrida em tempo real, com múltiplos corredores avançando simultaneamente.
  - Melhoram a responsividade do jogo, permitindo que o jogador interaja enquanto a corrida ocorre.

- **Semáforos:**
  - Garantem a sincronização adequada no acesso ao pit stop.
  - Evitam condições de corrida onde múltiplos carros tentam acessar o pit stop ao mesmo tempo, o que poderia causar inconsistências no estado do jogo.

### Fluxo de Funcionamento

1. **Início da Corrida:**
   - A thread principal (`Jogo::iniciar`) cria e inicia as threads de todos os corredores (jogador e IAs).

2. **Movimentação dos Carros:**
   - Cada thread de corredor executa `correr()`, incrementando a distância percorrida e verificando o desgaste dos pneus.

3. **Realização de Pit Stops:**
   - Quando um corredor decide realizar um pit stop (jogador ou IA), tenta adquirir o `pitstopMutex`.
   - Se o mutex for adquirido com sucesso, o carro entra no pit stop, realiza a troca de pneus e libera o mutex após 3 segundos.
   - Enquanto o pit stop está ocupado, outros corredores que tentarem realizar um pit stop serão bloqueados até que o mutex seja liberado.

4. **Finalização da Corrida:**
   - A corrida termina quando um carro alcança a distância total ou estoura o pneu.
   - Todas as threads são unidas (`join`), e a classificação final é exibida.

---

## Implementação das Classes

### Carro.hpp

Define a classe `Carro`, representando cada corredor na corrida.

```cpp
#ifndef CARRO_H
#define CARRO_H

#include <iostream>
#include <string>
#include <mutex>
#include <atomic>
#include <semaphore>

// Velocidades base dos pneus
#define S 2.1
#define M 1.9
#define H 1.6
#define DISTANCIA_TOTAL 100 // Distância total da corrida (em metros ou voltas)

using namespace std;

class Pneu {
public:
    char tipo; // s (Soft), m (Medium) ou h (Hard)
    float velocidadeBase;
    float desgaste;

    Pneu(char tipo);

    float calcularVelocidade(); // Velocidade ajustada ao desgaste
    void desgastar();           // Incrementa o desgaste do pneu
};

class Carro{
public:
    Pneu *pneu;
    atomic <float> distanciaPercorrida;
    mutex &pitstopMutex;
    string nome;
    atomic<bool> DentroPitStop;
    atomic <bool> ChegouNaLargada;
    atomic <bool> EstourouPneu;
    mutex &OrdemDeChegada;
    atomic <int> &PosicaoDoCarro;

    Carro(char tipoPneu, mutex &pitstopMutex, string Nome, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro);
    ~Carro(); // Libera memória do pneu

    void fazerPitStop(char novoPneu);
    void correr();                    // Simulação do carro correndo
    string getNomeCarro();
};

#endif
```

### IA.hpp

Define a classe `IA`, responsável por controlar os corredores controlados por Inteligência Artificial.

```cpp
#ifndef IA_H
#define IA_H

#include "Carro.hpp"
#include "Player.hpp"
#include <string>
#include <atomic>

using namespace std;

class IA {
public:
    string nome;
    Carro *carro;
    mutex &pitstopMutex;
    mutex &OrdemDeChegada;
    int ResetarPneu;
    atomic <int> &PosicaoDoCarro;

    IA(string nome, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro);
    ~IA(); 

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif
```

### Jogo.hpp

Define a classe `Jogo`, que gerencia o estado geral da corrida.

```cpp
#ifndef JOGO_H
#define JOGO_H

#include "Player.hpp"
#include "IA.hpp"
#include <thread>
#include <atomic>
#include <vector>
#include <semaphore>

using namespace std;

class Jogo{

    // Atributos privados para controle do jogo (incluindo mutex e variável atômica)
    private:
        // Jogador do tipo Player
        Player *jogador;
        
        mutex pitstopMutex;
        mutex OrdemDeChegada;
        atomic <int> PosicaoDoCarro;

    // Atributos públicos e métodos
    public:
        vector<thread> threads;
        vector<IA*> IAs;
        vector<Carro*> Carros;

        Jogo(string nomeJogador, char pneuInicial);
        ~Jogo();

        void iniciar();
        void desenharPista(const vector<Carro*> carros);
};
#endif
```

### Player.hpp

Define a classe `Player`, que controla a lógica do jogador na corrida.

```cpp
#ifndef PLAYER_H
#define PLAYER_H

#include "Carro.hpp"
#include <string>
#include <atomic>

using namespace std;

class Player
{
private:
    string nome;
    Carro *carro;
    mutex &pitstopMutex;
    mutex &OrdemDeChegada;
    atomic <int> &PosicaoDoCarro;

public:
    Player(string nome, char tipoPneuInicial, mutex &Semaforo, mutex &OrdemDeChegadaSemaforo, atomic <int> &PosicaoDoCarro);
    ~Player();

    string getNome();    
    Carro *getCarro();   
    void controlar();
};

#endif
```

### Implementações dos Arquivos `.cpp`

As implementações detalhadas dos arquivos `.cpp` são fornecidas no código fonte do projeto e seguem a estrutura definida nos arquivos de cabeçalho (`.hpp`).

---

## Implementação de Threads e Semáforos

### Visão Geral

O **RaceCondition** utiliza **threads** e **semaforos** para gerenciar a concorrência entre múltiplos corredores (jogador e IAs) e para sincronizar o acesso a recursos compartilhados, como o pit stop.

### Threads

As **threads** permitem a execução simultânea de diferentes partes do programa, simulando a concorrência real de uma corrida. As principais threads implementadas são:

1. **Thread Principal:**
   - Responsável por iniciar a corrida e gerenciar as threads dos corredores.

2. **Threads das IAs:**
   - Cada corredor controlado por IA possui sua própria thread para gerenciar sua movimentação e estratégias de pit stop.

3. **Thread do Jogador:**
   - Monitora as entradas do usuário para realizar pit stops sem bloquear a execução das threads dos corredores.

4. **Thread de Desenho da Pista:**
   - Atualiza a visualização da pista e da tabela de classificação em tempo real.

### Semáforos

Os **semaforos** são utilizados para controlar o acesso a recursos compartilhados, garantindo que apenas uma thread possa acessar o recurso por vez, evitando condições de corrida.

- **Semáforo do Pit Stop:**
  - Implementado utilizando `std::mutex`.
  - Garante que apenas um carro (jogador ou IA) possa realizar um pit stop por vez.
  - Quando um carro entra no pit stop, o mutex é bloqueado, impedindo que outros carros acessem o pit stop simultaneamente.
  - Após a conclusão do pit stop, o mutex é liberado, permitindo que outro carro utilize o pit stop.

### Justificativa do Uso

- **Threads:**
  - Permitem simular a corrida em tempo real, com múltiplos corredores avançando simultaneamente.
  - Melhoram a responsividade do jogo, permitindo que o jogador interaja enquanto a corrida ocorre.

- **Semáforos:**
  - Garantem a sincronização adequada no acesso ao pit stop.
  - Evitam condições de corrida onde múltiplos carros tentam acessar o pit stop ao mesmo tempo, o que poderia causar inconsistências no estado do jogo.

### Fluxo de Funcionamento

1. **Início da Corrida:**
   - A thread principal (`Jogo::iniciar`) cria e inicia as threads de todos os corredores (jogador e IAs).

2. **Movimentação dos Carros:**
   - Cada thread de corredor executa `correr()`, incrementando a distância percorrida e verificando o desgaste dos pneus.

3. **Realização de Pit Stops:**
   - Quando um corredor decide realizar um pit stop (jogador ou IA), tenta adquirir o `pitstopMutex`.
   - Se o mutex for adquirido com sucesso, o carro entra no pit stop, realiza a troca de pneus e libera o mutex após 3 segundos.
   - Enquanto o pit stop está ocupado, outros corredores que tentarem realizar um pit stop serão bloqueados até que o mutex seja liberado.

4. **Finalização da Corrida:**
   - A corrida termina quando um carro alcança a distância total ou estoura o pneu.
   - Todas as threads são unidas (`join`), e a classificação final é exibida.

---

## Implementação das Classes

### Implementação das Classes

As classes principais do **RaceCondition** são `Carro`, `IA`, `Player` e `Jogo`. Cada uma delas possui responsabilidades específicas no gerenciamento da corrida, interação com o jogador e controle das Inteligências Artificiais.

#### 1. **Carro**

Representa cada corredor na corrida, seja o jogador ou uma IA.

- **Atributos:**
  - `Pneu *pneu`: Tipo e estado dos pneus.
  - `atomic<float> distanciaPercorrida`: Distância percorrida pelo carro.
  - `mutex &pitstopMutex`: Referência ao mutex do pit stop.
  - `string nome`: Nome do corredor.
  - `atomic<bool> DentroPitStop`: Indica se o carro está no pit stop.
  - `atomic<bool> ChegouNaLargada`: Indica se o carro alcançou a linha de chegada.
  - `atomic<bool> EstourouPneu`: Indica se o pneu estourou.
  - `mutex &OrdemDeChegada`: Mutex para gerenciar a ordem de chegada.
  - `atomic<int> &PosicaoDoCarro`: Posição atual do carro na corrida.

- **Métodos:**
  - `void fazerPitStop(char novoPneu)`: Realiza o pit stop para troca de pneus.
  - `void correr()`: Simula o movimento do carro na corrida.
  - `string getNomeCarro()`: Retorna o nome do carro.

#### 2. **IA**

Controla a lógica das IAs que competem na corrida.

- **Atributos:**
  - `string nome`: Nome da IA.
  - `Carro *carro`: Ponteiro para o carro controlado pela IA.
  - `mutex &pitstopMutex`: Referência ao mutex do pit stop.
  - `mutex &OrdemDeChegada`: Referência ao mutex da ordem de chegada.
  - `int ResetarPneu`: Valor aleatório para determinar quando realizar o pit stop.
  - `atomic<int> &PosicaoDoCarro`: Posição atual do carro na corrida.

- **Métodos:**
  - `void controlar()`: Gerencia a movimentação e estratégias de pit stop da IA.

#### 3. **Player**

Controla a lógica do jogador na corrida.

- **Atributos:**
  - `string nome`: Nome do jogador.
  - `Carro *carro`: Ponteiro para o carro controlado pelo jogador.
  - `mutex &pitstopMutex`: Referência ao mutex do pit stop.
  - `mutex &OrdemDeChegada`: Referência ao mutex da ordem de chegada.
  - `atomic<int> &PosicaoDoCarro`: Posição atual do carro na corrida.

- **Métodos:**
  - `void controlar()`: Monitora as entradas do jogador para realizar pit stops.

#### 4. **Jogo**

Gerencia o estado geral da corrida, incluindo a criação de corredores, inicialização das threads e atualização da visualização.

- **Atributos:**
  - `Player *jogador`: Ponteiro para o jogador.
  - `mutex pitstopMutex`: Mutex para controlar o acesso ao pit stop.
  - `mutex OrdemDeChegada`: Mutex para gerenciar a ordem de chegada.
  - `atomic<int> PosicaoDoCarro`: Posição atual do carro na corrida.
  - `vector<thread> threads`: Vetor de threads em execução.
  - `vector<IA*> IAs`: Vetor de IAs participantes.
  - `vector<Carro*> Carros`: Vetor de carros na corrida.

- **Métodos:**
  - `void iniciar()`: Inicia a corrida e as threads associadas.
  - `void desenharPista(const vector<Carro*> carros)`: Atualiza a visualização da pista e da tabela de classificação.

---

## Considerações Finais

O **RaceCondition** é uma aplicação prática dos conceitos de **threads** e **semaforos** em C++. Através da simulação de uma corrida de Fórmula 1, o projeto demonstra como gerenciar a concorrência e a sincronização entre múltiplas threads, garantindo que recursos compartilhados sejam acessados de forma segura e eficiente.

### Possíveis Melhorias

- **Interface Gráfica:**
  - Implementar uma interface gráfica para melhorar a experiência do usuário.
  
- **Estratégias de IA Avançadas:**
  - Desenvolver estratégias mais complexas para as IAs, considerando fatores como clima, tráfego na pista, entre outros.
  
- **Persistência de Dados:**
  - Adicionar funcionalidades para salvar e carregar estatísticas de corridas anteriores.

### Agradecimentos

Agradecemos a todos os integrantes pelo empenho e colaboração no desenvolvimento deste projeto:

- **Enzo Tonon Morente** - 14568476
- **João Pedro Alves Notari Godoy** - 14582076
- **Letícia Barbosa Neves** - 14588659
- **Luiz Felipe Diniz Costa** - 13782032

---

## Anexos

### Makefile

O `Makefile` facilita a compilação e execução do projeto. A seguir, apresenta-se o conteúdo do `Makefile` utilizado:

```makefile
# compilador
CXX := g++

# diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

# flags de compilação
CXXFLAGS := -Wall -Wextra -std=c++20 -I$(INCLUDE_DIR)

# arquivos fonte e objetos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# nome do executável
TARGET := $(BUILD_DIR)/jogo

# regra padrão
all: $(TARGET)

# regra para criar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# regra para compilar os arquivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# limpa arquivos compilados
clean:
	rm -rf $(BUILD_DIR)/*

# limpa tudo, incluindo o diretório build
cleanall:
	rm -rf $(BUILD_DIR)

# regra para rodar o programa
run: $(TARGET)
	$(TARGET)

# phony targets
.PHONY: all clean cleanall run
```

#### Comandos Úteis

- **Compilar o Projeto:**
  ```bash
  make
  ```

- **Executar o Jogo:**
  ```bash
  make run
  ```

- **Limpar Arquivos Compilados:**
  ```bash
  make clean
  ```

- **Limpar Tudo (incluindo diretório `build`):**
  ```bash
  make cleanall
  ```

---

## Contato

Para dúvidas ou sugestões relacionadas ao projeto **RaceCondition**, entre em contato com os desenvolvedores:

- **Enzo Tonon Morente** - enzo.morente@usp.br
- **João Pedro Alves Notari Godoy** - joao.godoy@usp.br
- **Letícia Barbosa Neves** - leticia.neves@usp.br
- **Luiz Felipe Diniz Costa** - luiz.costa@usp.br

---

## License

Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

---

# Agradecimentos

Agradecemos aos professores e assistentes da disciplina de Sistemas Operacionais da USP pelo suporte e orientação durante o desenvolvimento deste projeto.

---

# Screenshots

_Ainda não disponível. Em futuras versões, a documentação poderá incluir capturas de tela da interface do jogo para melhor visualização._

---

# Referências

- **Documentação C++:** [cplusplus.com](http://www.cplusplus.com/)
- **Threads em C++:** [C++ Thread Library](https://en.cppreference.com/w/cpp/thread)
- **Semáforos em C++:** [C++ Semaphore](https://en.cppreference.com/w/cpp/thread/semaphore)

---

**Boa corrida e boa sorte! 🏎️🏁**