// jogo.h
#ifndef JOGO_H
#define JOGO_H

#include "carro.h"  // Inclui a classe Carro

#include <string>  // Para usar std::string
#include <atomic>
#include <thread>
#include <mutex>

using namespace std;

atomic<bool> desejaPitStop(false);
mutex semaforo;

#endif
