// Jogo.hpp
#ifndef JOGO_HPP
#define JOGO_HPP

#include <vector>
#include <thread>
#include "carro.hpp" // Importa a classe Carro

class Jogo {
public:
    Jogo(int numCarros, double radius);
    void iniciar();

private:
    double radius;
    std::vector<Carro> carros;
    std::vector<std::thread> threads;
};

#endif // JOGO_HPP
