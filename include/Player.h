#ifndef PLAYER_H
#define PLAYER_H

#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Player {
public:
    Player(atomic<bool>& desejaPitStop_ref,
           atomic<char>& tipoPneuEscolhido_ref,
           atomic<bool>& corridaTerminou_ref);

    void interagir();

private:
    atomic<bool>& desejaPitStop;
    atomic<char>& tipoPneuEscolhido;
    atomic<bool>& corridaTerminou;
};

#endif // PLAYER_H
