# RaceCondition

## Visão Geral

Este projeto consiste na implementação de um jogo de corrida de Fórmula 1 que simula uma competição entre o jogador e quatro corredores controlados por Inteligência Artificial (IA). O foco principal do projeto é a aplicação prática de conceitos de Sistemas Operacionais, especificamente o uso de **threads** e **semáforos** para gerenciar a concorrência e a sincronização entre diferentes partes do sistema.

## Objetivos

- **Compreender e aplicar conceitos de threads e semáforos** no contexto de um jogo/aplicativo.
- **Desenvolver um jogo de corrida** que utilize múltiplas threads para gerenciar a lógica dos corredores e a interação do jogador.
- **Implementar semáforos** para controlar o acesso a recursos compartilhados, como o pit stop.
- **Criar uma interface simples** que permita ao jogador interagir com o jogo, escolhendo estratégias de pit stop para vencer a corrida.

## Funcionalidades

### Escolha de Pneus

- **Tipos de Pneu Disponíveis:**
  - **SOFT:** Maior velocidade (8 unidades), maior desgaste (0.8/segundo).
  - **MEDIUM:** Velocidade intermediária (5 unidades), desgaste médio (0.5/segundo).
  - **HARD:** Menor velocidade (3 unidades), menor desgaste (0.3/segundo).

- **Desgaste dos Pneus:**
  - Cada tipo de pneu possui um valor de desgaste inicial de 0 e aumenta de acordo com o tipo escolhido.
  - Se o desgaste atingir 10, o pneu estoura e o carro perde a corrida imediatamente.

- **Cálculo da Velocidade Instantânea:**
  - `Velocidade = ConstanteDeVelocidade - (Desgaste * 0.1)`
- O Jogo deverá sempre esperar um tipo de pneu, então o tereminal sempre ficará aberto para que o usuario digite 's', 'm' ou 'h'. Ao digitar o tipo de pneu, se o pitstop estiver livre (só haverá 1), o jogador deverá fica nele por 3 segundos em sleep, e nenhum outro corredor poderá acessar o pitstop neste periodo.
- Caso o jogador não entre no pitstop a tempo, ele perderá a corrida ficando na ultima posição e apenas assistirá as IAS competindo

### Pit Stop

- **Interação com o Pit Stop:**
  - O jogador pode optar por entrar no pit stop quando julgar necessário para trocar os pneus.
  - Durante o pit stop, o jogador pode escolher trocar para um novo tipo de pneu ou manter o atual, com os valores de desgaste resetados.
  - O acesso ao pit stop é controlado por um semáforo para garantir que apenas um carro possa utilizá-lo por vez.

### Corrida

- **Objetivo da Corrida:**
  - Alcançar a distância de 1000 unidades primeiro para vencer a corrida.
  
- **Monitoramento da Corrida:**
  - O jogo exibe a posição atual de todos os corredores (1º, 2º, 3º, 4º, 5º) à medida que a corrida avança.

### Inteligência Artificial dos Corredores

- **Corredores Controlados por IA:**
  - **Vertapen:** Tendência a usar pneus SOFT (estilo liberal).
  - **Hamiton:** Tendência a usar pneus MEDIUM (estilo balanceado).
  - **Charles:** Tendência a usar pneus HARD (estilo conservador).
  - **Bortoleto** Comportamento aleatório

- **Estratégias de Pit Stop:**
  - Cada IA possui estratégias pré-definidas que determinam quando realizar pit stops, baseadas em fatores como desgaste dos pneus e proximidade da linha de chegada.

### Multithreading e Sincronização

- **Threads:**
  - **Thread Principal:** Gerencia a lógica principal da corrida e atualiza a posição dos corredores.
  - **Thread de Entrada do Usuário:** Monitora a entrada do jogador para realizar pit stops sem bloquear a execução das outras threads.
  - **Threads das IAs:** Cada corredor controlado por IA possui sua própria thread que gerencia sua movimentação e estratégias de pit stop.

- **Semáforos:**
  - **Semáforo do Pit Stop:** Controla o acesso ao pit stop, permitindo que apenas um carro entre por vez.

## Uso

1. **Iniciar a Corrida:**
   - Ao iniciar o jogo, o jogador deve escolher o tipo de pneu inicial (SOFT, MEDIUM, HARD).

2. **Monitorar o Desgaste e Velocidade:**
   - O jogo exibirá o desgaste e a velocidade atual do carro a cada segundo.

3. **Realizar Pit Stops:**
   - Quando julgar necessário, o jogador pode optar por entrar no pit stop para trocar os pneus.

4. **Interação com as IAs:**
   - Observe as estratégias das IAs e ajuste sua própria estratégia de pit stop para vencer a corrida.

5. **Finalizar a Corrida:**
   - A corrida termina quando um dos corredores alcança a distância de 1000 unidades ou quando um pneu estoura.

## Documentação das Threads e Semáforos

### Threads

- **Thread Principal:**
  - Responsável por atualizar a posição de todos os corredores com base em suas velocidades.
  - Executa um loop que incrementa a distância percorrida a cada segundo.

- **Thread de Entrada do Usuário:**
  - Monitora a entrada do jogador para realizar pit stops sem interromper a execução do loop principal.
  - Utiliza operações de E/S assíncronas para não bloquear a thread principal.

- **Threads das IAs:**
  - Cada IA possui sua própria thread que gerencia sua movimentação e decisões de pit stop.
  - As estratégias são pré-definidas e podem variar conforme a personalidade da IA.

### Semáforos

- **Semáforo do Pit Stop:**
  - Implementado para controlar o acesso ao pit stop, garantindo que apenas um carro possa utilizá-lo por vez.
  - Inicializado com valor 1 (disponível).
  - Quando um carro entra no pit stop, decrementa o semáforo. Ao sair, incrementa o semáforo.

### Justificativa do Uso

- **Threads:**
  - Permitem a execução concorrente das lógicas dos diferentes corredores e a interação do jogador, melhorando a responsividade e a simulação realista da corrida.

- **Semáforos:**
  - Garantem a sincronização adequada no acesso ao pit stop, evitando condições de corrida e garantindo que apenas um carro possa trocar os pneus de cada vez.

## Contribuintes

| Nome                                  | Número USP              |
|---------------------------------------|-------------------------|
| Enzo Tono Morente                     | 14568476                |
| João Pedro Alves Notare Godoy         | 14582076                |
| Letícia Barbosa Neves                 | 14588659                |
| Luiz Felipe Diniz Costa               | 13782032                |



