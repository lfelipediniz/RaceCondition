# RaceCondition - Game Manual
<p align="center">
  <img src="/imgs/racecondition.png" alt="Game Cover" width="300">
</p>

## Table of Contents
1. [Introduction](#introduction)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [How to Play](#how-to-play)
5. [Game Calculations and Logic](#game-calculations-and-logic)
6. [Threads and Semaphores Implementation](#threads-and-semaphores-implementation)
7. [Class Implementation](#class-implementation)
8. [Final Considerations](#final-considerations)


## Introduction

**RaceCondition** is a Formula 1 racing simulation. The game allows the player to compete against four AI-controlled racers. The main focus of the project is the practical application of **threads** and **semaphores** to manage concurrency and synchronization between different system components.

The objective is to provide an interactive experience where the player must manage pit stop strategies, choosing appropriate tire types to win the race, while dealing with the automatic decisions of the AIs. The simulation highlights how multiple threads can operate simultaneously and how semaphores are used to control access to shared resources, such as the pit stop and the finish line.

## Requirements

- **C++ Compiler:** GCC or Clang with C++20 support.
- **Make:** Build utility to compile the project.

## Installation

### Clone the Repository

```bash
git clone https://github.com/lfelipediniz/RaceCondition.git
```

```bash
cd RaceCondition
```

### Compile and Run the Game

```bash
make
```

```bash
make run
```

## How to Play

### Starting the Race

1. **Racer Name**
    When starting the game, you will need to enter the name of your racer.

2. **Initial Tire Type Selection:**
   - Select the type of tire to start the race:
     - **s**: **SOFT** - Higher speed, higher wear.
     - **m**: **MEDIUM** - Intermediate speed, medium wear.
     - **h**: **HARD** - Lower speed, lower wear.

### During the Race

- **Monitoring:**
  - The track will be displayed in the terminal, showing each racer's position.
  - A leaderboard will be updated every second, displaying information such as tire wear, tire type, pit stop status, and current situation (racing, in pit stop, or disqualified).

- **Perform Pit Stop:**
  - When necessary, you can choose to enter the pit stop to change tires.
  - To enter the pit stop, type:
    - **s**: Switch to **SOFT** tires.
    - **m**: Switch to **MEDIUM** tires.
    - **h**: Switch to **HARD** tires.
  - The pit stop will be occupied for 3 seconds, during which no other car can use it.

- **Winning Conditions:**
  - The race ends when all racers cross the finish line or when all have been disqualified.
  - If a tire bursts (wear reaches 10), the car is disqualified from the race. When this happens, an X will appear in the racer's status to indicate they are out.

<p align="center">
  <img src="/imgs/meio_da_corrida.jpeg" alt="Mid-Race">
</p>


### End of the Race
When the race ends, a message is displayed with the final results, and you will be prompted to exit the game.

<p align="center">
  <img src="/imgs/fim_da_corrida.jpg" alt="End of the Race">
</p>


## Game Calculations and Logic

### Tire Wear

Each type of tire has a specific wear rate that increases every second of the race:

### Wear Increment by Level

| **Level** | **Code** | **Wear Increment per Second** |
|-----------|----------|--------------------------------|
| 🟢 **Soft**  | `s`      | $\mathbf{0.5}$               |
| 🟡 **Medium**| `m`      | $\mathbf{0.3}$               |
| 🔴 **Hard**  | `h`      | $\mathbf{0.1}$               |

If tire wear reaches **10**, the tire bursts and the car is eliminated from the race.

### Instantaneous Speed Calculation

The speed of each car is calculated based on the tire type and accumulated wear:

$$
\text{Speed} = \text{BaseSpeed} - (\text{Wear} \times 0.1)
$$

Where **BaseSpeed** depends on the chosen tire type:

- **SOFT:** $2.1$ units
- **MEDIUM:** $1.9$ units
- **HARD:** $1.6$ units

### Calculation Examples

1. **Car with SOFT Tire and Wear 3:**

$$
\text{Speed} = 2.1 - (3 \times 0.1) = 2.1 - 0.3 = 1.8 \text{ units}
$$

2. **Car with MEDIUM Tire and Wear 5:**

$$
\text{Speed} = 1.9 - (5 \times 0.1) = 1.9 - 0.5 = 1.4 \text{ units}
$$

3. **Car with HARD Tire and Wear 2:**

$$
\text{Speed} = 1.6 - (2 \times 0.1) = 1.6 - 0.2 = 1.4 \text{ units}
$$

### Pit Stop Strategy

The pit stop can be occupied by only one car.

- **Player**
  - The player can choose to enter the pit stop at any time to change tires, selecting between SOFT, MEDIUM, or HARD.
  - Performing a pit stop pauses the car for 3 seconds, during which the tire is changed and the wear is reset.

- **Artificial Intelligences (AI):**
  - The AIs use a random algorithm, allowing each race to be unique.

## Threads and Semaphores Implementation

### Overview

The project uses **threads** and **semaphores** to manage concurrency between multiple racers (player and AIs) and to synchronize access to shared resources, such as the pit stop and the finish line.

### Threads

**Threads** allow the simultaneous execution of different parts of the program, simulating the real concurrency of a race. The main threads implemented are:

1. **Car Thread**
   - All cars have a thread to race on the track.

2. **AI Threads**
   - Each AI car will have a thread with a controller that decides when it should enter the pit and which tire it will put on.

3. **Player Thread**
   - This is a thread that will monitor user input to check when the player wants to enter the pit stop, which type of tire they want to put on, and thus control the car regarding pit stop entry.

4. **Track Drawing Thread**
   - Updates the visualization of the track and the leaderboard in real-time.

### Semaphores

**Semaphores** are used to control access to shared resources, allowing only one thread to access the resource at a time, preventing race conditions.

- **Pit Stop Semaphore**
  - Uses `std::mutex`.
  - Ensures that only one car (player or AI) can use the pit stop at a time.
  - When a car enters the pit stop, the mutex is locked, preventing other cars from accessing the pit stop simultaneously.
  - After the pit stop is completed, the mutex is released, allowing another car to use the pit stop.

- **Finish Line Semaphore**
  - Uses `std::mutex`.
  - Ensures that only one car (player or AI) can pass the finish line at a time.
  - When a car passes the finish line, the mutex is locked, preventing other cars from passing it simultaneously.
  - After the car crosses the line, the mutex is released, allowing other cars to pass it.

### Justification for Use

- **Threads**
  - Allow simulating the race in real-time, with multiple drivers advancing simultaneously.
  - Improve the responsiveness of the game, allowing the player to interact while the race is happening.

- **Semaphores**
  - Ensure proper synchronization in accessing the pit stop and the finish line.
  - Prevent race conditions where multiple cars attempt to access the pit stop or the finish line at the same time, which could cause RaceCondition.
  - The choice of mutex semaphore was made for both cases, as there was only a need for the semaphore to assume values 0 and 1.

### Workflow

1. **Start of the Race**
   - The method (`Jogo::iniciar`) creates and starts the threads of all cars and controllers (player and AIs).

2. **Car Movement**
   - Each car thread executes `correr()`, incrementing the distance traveled and checking tire wear.

3. **Performing Pit Stops**
   - When a controller decides to perform a pit stop (player or AI), it tries to acquire the `pitstopMutex`.
   - If the mutex is successfully captured, the car enters the pit stop, changes tires, and releases the mutex after 3 seconds.
   - While the pit stop is occupied, other drivers attempting to perform a pit stop will be blocked until the mutex is released.

4. **Passing the Finish Line**
   - When a car reaches the finish line, it tries to acquire the `OrdemDeChegada` mutex.
   - If the mutex is successfully captured, the car passes the finish line, is marked as having finished the race, and releases the critical region.

5. **End of the Race**
   - The race ends when all cars reach the finish line or burst their tires.
   - All threads are joined, and the final standings are displayed.

### Class Implementation

The main classes of **RaceCondition** are `Carro`, `IA`, `Player`, and `Jogo`. Each of them has specific responsibilities in managing the race, interacting with the player, and controlling the Artificial Intelligences.

#### 1. **Carro**

Represents each car in the race, whether it is a player's car or an AI's car.

- **Attributes**
  - `Pneu *pneu`: Type and state of the tires.
  - `atomic<float> distanciaPercorrida`: Distance traveled by the car.
  - `mutex &pitstopMutex`: Reference to the pit stop mutex.
  - `string nome`: Racer's name.
  - `atomic<bool> DentroPitStop`: Indicates if the car is in the pit stop.
  - `atomic<bool> ChegouNaLargada`: Indicates if the car has reached the finish line.
  - `atomic<bool> EstourouPneu`: Indicates if the tire has burst.
  - `mutex &OrdemDeChegada`: Mutex to manage the order of arrival.
  - `atomic<int> &PosicaoDoCarro`: Car's position when it passes the finish line.

- **Methods**
  - `void fazerPitStop(char novoPneu)`: Performs the pit stop to change tires.
  - `void correr()`: Simulates the car's movement in the race.
  - `string getNomeCarro()`: Returns the car's name.

#### 2. **IA**

Controls the logic of the AIs that compete in the race.

- **Attributes**
  - `string nome`: AI's name.
  - `Carro *carro`: Pointer to the car controlled by the AI.
  - `mutex &pitstopMutex`: Reference to the pit stop mutex.
  - `mutex &OrdemDeChegada`: Reference to the finish line mutex.
  - `int ResetarPneu`: Random value to determine when to perform a pit stop.
  - `atomic<int> &PosicaoDoCarro`: Car's position when it passes the finish line.

- **Methods**
  - `void controlar()`: Manages the AI's movement and pit stop strategies.

#### 3. **Player**

Controls the player's logic in the race.

- **Attributes**
  - `string nome`: Player's name.
  - `Carro *carro`: Pointer to the car controlled by the player.
  - `mutex &pitstopMutex`: Reference to the pit stop mutex.
  - `mutex &OrdemDeChegada`: Reference to the finish line mutex.
  - `atomic<int> &PosicaoDoCarro`: Car's position when it passes the finish line.

- **Methods**
  - `void controlar()`: Monitors player inputs to perform pit stops.

#### 4. **Jogo**

Manages the overall state of the race, including creating racers, initializing threads, and updating the visualization.

- **Attributes**
  - `Player *jogador`: Pointer to the player.
  - `mutex pitstopMutex`: Mutex to control access to the pit stop.
  - `mutex OrdemDeChegada`: Mutex to manage the order of arrival.
  - `atomic<int> PosicaoDoCarro`: Current position of the car in the race.
  - `vector<thread> threads`: Vector of running threads.
  - `vector<IA*> IAs`: Vector of participating AIs.
  - `vector<Carro*> Carros`: Vector of cars in the race.

- **Methods**
  - `void iniciar()`: Starts the race and associated threads.
  - `void desenharPista(const vector<Carro*> carros)`: Updates the visualization of the track and the leaderboard.

## Final Considerations

**RaceCondition** is a game that effectively utilizes the concepts of **threads** and **semaphores** in C++. Through the simulation of a Formula 1 race, the project demonstrates how to manage concurrency and synchronization between multiple threads, consistently avoiding RaceCondition.

### Contributors

- **Enzo Tonon Morente** - 14568476
- **João Pedro Alves Notari Godoy** - 14582076
- **Letícia Barbosa Neves** - 14588659
- **Luiz Felipe Diniz Costa** - 13782032

---
**Good race! 🏎️🏁**

This project was developed as part of the **Operating Systems** course. For more info about the course, visit: [Operating Systems - USP](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SSC0140&codcur=55041&codhab=0)

A video presentation of this project is available on YouTube: [Watch the Presentation](https://www.youtube.com/watch?v=Tc_-pMtgpi4&t)

---


