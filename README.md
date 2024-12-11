# RaceCondition - Manual do Jogo
<p align="center">
  <img src="/imgs/racecondition.png" alt="Capa do jogo" width="300">
</p>

## Índice
1. [Introdução](#introdução)
2. [Requisitos](#requisitos)
3. [Instalação](#instalação)
4. [Como Jogar](#como-jogar)
5. [Cálculos e Lógica do Jogo](#cálculos-e-lógica-do-jogo)
6. [Implementação de Threads e Semáforos](#implementação-de-threads-e-semaforos)
7. [Implementação das Classes](#implementação-das-classes)
8. [Considerações Finais](#considerações-finais)


## Introdução

**RaceCondition** é uma simulação de corrida de Fórmula 1. O jogo permite que o jogador concorra contra quatro corredores controlados por Inteligência Artificial (IA). O principal foco do projeto é a aplicação prática de conceitos de **threads** e **semáforos** para gerenciar a concorrência e sincronização entre diferentes componentes do sistema.

O objetivo é proporcionar uma experiência interativa onde o jogador deve gerenciar estratégias de pit stop, escolhendo tipos de pneus adequados para vencer a corrida, enquanto lida com as decisões automáticas das IAs. A simulação destaca como múltiplas threads podem operar simultaneamente e como semáforos são utilizados para controlar o acesso a recursos compartilhados, como pit stop e linha de chegada. 

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
    Ao iniciar o jogo, você deverá inserir o nome do seu corredor.


2. **Escolha do Tipo de Pneu Inicial:**
   - Selecione o tipo de pneu para iniciar a corrida:
     - **s**: **SOFT** - Maior velocidade, maior desgaste.
     - **m**: **MEDIUM** - Velocidade intermediária, desgaste médio.
     - **h**: **HARD** - Menor velocidade, menor desgaste.

### Durante a Corrida

- **Monitoramento:**
  - A pista será exibida no terminal, mostrando a posição de cada corredor.
  - Uma tabela de classificação será atualizada a cada segundo, exibindo informações como desgaste dos pneus, tipo de pneu, status de pit stop e situação atual (em corrida, no pit stop ou desclassificado).

- **Realizar Pit Stop:**
  - Quando julgar necessário, você pode optar por entrar no pit stop para trocar os pneus.
  - Para entrar no pit stop, digite:
    - **s**: Trocar para pneus **SOFT**.
    - **m**: Trocar para pneus **MEDIUM**.
    - **h**: Trocar para pneus **HARD**.
  - O pit stop ficará ocupado por 3 segundos, durante os quais nenhum outro carro poderá usá-lo.

- **Condições de Vitória:**
  - A corrida termina quando todos os corredores passarem pela linha de chegada ou quando todos tenham sido desclassificados.
  - Se um pneu estourar (desgaste atingir 10), o carro é desclassificado da corrida. Quando isso acontece, um X irá aparecer na situação do piloto para indicar que ele está fora.

<p align="center">
  <img src="/imgs/meio_da_corrida.jpeg" alt="Meio da corrida">
</p>


### Final da Corrida
Quando a corrida acaba, uma mensagem é exibida com os resultados finais e você será convidado a finalizar o jogo.

<p align="center">
  <img src="/imgs/fim_da_corrida.jpg" alt="Fim da corrida">
</p>


## Cálculos e Lógica do Jogo

### Desgaste dos Pneus

Cada tipo de pneu possui uma taxa de desgaste específica que incrementa a cada segundo de corrida:

### Incremento de Desgaste por Nível

| **Nível** | **Código** | **Incremento de Desgaste por Segundo** |
|-----------|------------|----------------------------------------|
| 🟢 **Soft**  | `s`        | $\mathbf{0.5}$                         |
| 🟡 **Medium**| `m`        | $\mathbf{0.3}$                         |
| 🔴 **Hard**  | `h`        | $\mathbf{0.1}$                         |


Se o desgaste de um pneu atingir **10**, o pneu estoura e o carro é eliminado da corrida.

### Cálculo da Velocidade Instantânea

A velocidade de cada carro é calculada com base no tipo de pneu e no desgaste acumulado:

$$
\text{Velocidade} = \text{VelocidadeBase} - (\text{Desgaste} \times 0.1)
$$

Onde **VelocidadeBase** depende do tipo de pneu escolhido:

- **SOFT:** $2.1$ unidades
- **MEDIUM:** $1.9$ unidades
- **HARD:** $1.6$ unidades

### Exemplos de Cálculo

1. **Carro com Pneu SOFT e Desgaste 3:**

$$
\text{Velocidade} = 2.1 - (3 \times 0.1) = 2.1 - 0.3 = 1.8 \text{ unidades}
$$

2. **Carro com Pneu MEDIUM e Desgaste 5:**

$$
\text{Velocidade} = 1.9 - (5 \times 0.1) = 1.9 - 0.5 = 1.4 \text{ unidades}
$$

3. **Carro com Pneu HARD e Desgaste 2:**

$$
\text{Velocidade} = 1.6 - (2 \times 0.1) = 1.6 - 0.2 = 1.4 \text{ unidades}
$$


### Estratégia de Pit Stop

O pit stop só pode ser ocupado por apenas um carro.

- **Jogador**
  - O jogador pode optar por entrar no pit stop a qualquer momento para trocar os pneus, escolhendo entre SOFT, MEDIUM ou HARD.
  - Realizar um pit stop pausa o carro por 3 segundos, durante os quais o pneu é trocado e o desgaste é resetado.

- **Inteligências Artificiais (IA):**
  - As IAs utilizam de um algoritmo estocástico, permitindo que cada corrida seja única.


## Implementação de Threads e Semáforos

### Visão Geral

O projeto usa **threads** e **semáforos** para gerenciar a concorrência entre múltiplos corredores (jogador e IAs) e para sincronizar o acesso a recursos compartilhados, como o pit stop e linha de chegada.

### Threads

As **threads** permitem a execução simultânea de diferentes partes do programa, simulando a concorrência real de uma corrida. As principais threads implementadas são:

1. **Thread Carro**
   - Todos os carros possuem uma thread para correr na pista.

2. **Threads das IAs**
   - Cada carro das IAs vai ter uma thread com um controlador que vai decidir quando ele deve entrar no pit e qual pneu ele vai colocar.

3. **Thread do Jogador**
   - É uma thread que irá monitorar a entrada do usuário para verificar quando o jogador quer entrar no pit stop, qual tipo de pneu quer colocar e dessa forma controlar o carro em relação a entrada no pit stop.

4. **Thread de Desenho da Pista**
   - Atualiza a visualização da pista e da tabela de classificação em tempo real.

### Semáforos

Os **semáforos** são usados para controlar o acesso a recursos compartilhados, permitindo que apenas uma thread possa acessar o recurso por vez, evitando condições de corrida.

- **Semáforo do Pit Stop**
  - Usa o `std::mutex`.
  - Garante que apenas um carro (jogador ou IA) possa usar o pit stop por vez.
  - Quando um carro entra no pit stop, o mutex é bloqueado, impedindo que outros carros acessem o pit stop simultaneamente.
  - Após a conclusão do pit stop, o mutex é liberado, assim permitido que outro carro utilize o pit stop.

- **Semáforo do Linha de Chegada**
  - Usa o `std::mutex`.
  - Garante que apenas um carro (jogador ou IA) possa passar pela linha de chegada por vez.
  - Quando um carro passa pela linha de chegada, o mutex é bloqueado, impedindo que outros carros passem por ela simultaneamente.
  - Após o carro ultrapassar a linha, o mutex é liberado, assim possibilitando que outros carros passem por ela.

### Justificativa do Uso

- **Threads**
  - Permitem simular a corrida em tempo real, com múltiplos pilotos avançando simultaneamente.
  - Melhoram a responsividade do jogo, permitindo que o jogador interaja enquanto a corrida acontece.

- **Semáforos**
  - Garantem a sincronização adequada no acesso ao pit stop e da linha de chegada.
  - Evitam condições de corrida onde múltiplos carros tentam acessar o pit stop ou a linha de chegada ao mesmo tempo, o que poderia causar RaceCondition.
  - A escolha do semáforo mutex foi feita para ambos os casos, pois só existia a necessidade do semáforo assumir valores 0 e 1.

### Fluxo de Funcionamento

1. **Início da Corrida**
   - O método (`Jogo::iniciar`) cria e inicia as threads de todos os carros e controladores (jogador e IAs).

2. **Movimentação dos Carros**
   - Cada thread do carro executa `correr()`, incrementando a distância percorrida e verificando o desgaste dos pneus.

3. **Realização de Pit Stops**
   - Quando um controlador decide realizar um pit stop (jogador ou IA), ele tenta pegar o `pitstopMutex`.
   - Se o mutex for capturado com sucesso, o carro entra no pit stop, realiza a troca de pneus e libera o mutex após 3 segundos.
   - Enquanto o pit stop está ocupado, outros pilotos que tentarem realizar um pit stop serão bloqueados até que o mutex seja liberado.

4. **Passagem pela Linha de Chegada**
   - Quando um carro chega na linha de chegada o mesmo tenta pegar o mutex `OrdemDeChegada`.
   - Se o mutex for capturado com sucesso, o carro entra passa pela linha de chegada, é marcado que finalizou a corrida e libera a região crítica.

5. **Finalização da Corrida**
   - A corrida termina quando todos os carros atingem a linha de chegada ou estouram os pneus.
   - Todas as threads são unidas (`join`), e a classificação final é exibida.

### Implementação das Classes

As classes principais do **RaceCondition** são `Carro`, `IA`, `Player` e `Jogo`. Cada uma delas possui responsabilidades específicas no gerenciamento da corrida, interação com o jogador e controle das Inteligências Artificiais.

#### 1. **Carro**

Representa cada carro na corrida, seja ele de um jogador ou de uma IA.

- **Atributos**
  - `Pneu *pneu`: Tipo e estado dos pneus.
  - `atomic<float> distanciaPercorrida`: Distância percorrida pelo carro.
  - `mutex &pitstopMutex`: Referência ao mutex do pit stop.
  - `string nome`: Nome do corredor.
  - `atomic<bool> DentroPitStop`: Indica se o carro está no pit stop.
  - `atomic<bool> ChegouNaLargada`: Indica se o carro alcançou a linha de chegada.
  - `atomic<bool> EstourouPneu`: Indica se o pneu estourou.
  - `mutex &OrdemDeChegada`: Mutex para gerenciar a ordem de chegada.
  - `atomic<int> &PosicaoDoCarro`: Posição do carro quando ele passa a linha de chegada.

- **Métodos**
  - `void fazerPitStop(char novoPneu)`: Realiza o pit stop para troca de pneus.
  - `void correr()`: Simula o movimento do carro na corrida.
  - `string getNomeCarro()`: Retorna o nome do carro.

#### 2. **IA**

Controla a lógica das IAs que competem na corrida.

- **Atributos**
  - `string nome`: Nome da IA.
  - `Carro *carro`: Ponteiro para o carro controlado pela IA.
  - `mutex &pitstopMutex`: Referência ao mutex do pit stop.
  - `mutex &OrdemDeChegada`: Referência ao mutex da ordem de chegada.
  - `int ResetarPneu`: Valor aleatório para determinar quando realizar o pit stop.
  - `atomic<int> &PosicaoDoCarro`: Posição do carro quando ele passa pela linha de chegada.

- **Métodos**
  - `void controlar()`: Gerencia a movimentação e estratégias de pit stop da IA.

#### 3. **Player**

Controla a lógica do jogador na corrida.

- **Atributos**
  - `string nome`: Nome do jogador.
  - `Carro *carro`: Ponteiro para o carro controlado pelo jogador.
  - `mutex &pitstopMutex`: Referência ao mutex do pit stop.
  - `mutex &OrdemDeChegada`: Referência ao mutex da ordem de chegada.
  - `atomic<int> &PosicaoDoCarro`: Posição do carro quando ele passa pela linha de chegada.

- **Métodos**
  - `void controlar()`: Monitora as entradas do jogador para realizar pit stops.

#### 4. **Jogo**

Gerencia o estado geral da corrida, incluindo a criação de corredores, inicialização das threads e atualização da visualização.

- **Atributos**
  - `Player *jogador`: Ponteiro para o jogador.
  - `mutex pitstopMutex`: Mutex para controlar o acesso ao pit stop.
  - `mutex OrdemDeChegada`: Mutex para gerenciar a ordem de chegada.
  - `atomic<int> PosicaoDoCarro`: Posição atual do carro na corrida.
  - `vector<thread> threads`: Vetor de threads em execução.
  - `vector<IA*> IAs`: Vetor de IAs participantes.
  - `vector<Carro*> Carros`: Vetor de carros na corrida.

- **Métodos**
  - `void iniciar()`: Inicia a corrida e as threads associadas.
  - `void desenharPista(const vector<Carro*> carros)`: Atualiza a visualização da pista e da tabela de classificação.


## Considerações Finais

O **RaceCondition** é um jogo que utiliza muito bem os conceitos de **threads** e **semáforos** em C++. Através da simulação de uma corrida de Fórmula 1, o projeto demonstra como gerenciar a concorrência e a sincronização entre múltiplas threads, evitando sempre a RaceCondition.

### Colaboradores

- **Enzo Tonon Morente** - 14568476
- **João Pedro Alves Notari Godoy** - 14582076
- **Letícia Barbosa Neves** - 14588659
- **Luiz Felipe Diniz Costa** - 13782032

---
**Boa corrida! 🏎️🏁**
