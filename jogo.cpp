#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <chrono>

// Jogo.cpp
#include "jogo.hpp"

Jogo::Jogo(int numCarros, double radius) : radius(radius) {
    //criar uma lista de carros
    for (int i = 0; i < numCarros; ++i) {
        carros.push_back(Carro(i, radius)); // Criando carros
    }
}

void Jogo::iniciar() {
    for (auto& carro : carros) { 
        threads.push_back(std::thread(&Carro::andar, &carro)); // Iniciando threads de cada carro
    }

    for (auto& t : threads) {
        t.join(); // Espera todas as threads terminarem (neste caso, são loops infinitos)
    }
}