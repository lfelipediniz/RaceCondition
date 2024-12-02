// Carro.hpp
#ifndef CARRO_HPP
#define CARRO_HPP

#include <cmath> // Para funções trigonométricas

class Carro {
public:
    Carro(int id, double radius);
    void andar();

private:
    int id;
    double radius;
    double angle; // O ângulo que define a posição do carro no círculo
};

#endif // CARRO_HPP
