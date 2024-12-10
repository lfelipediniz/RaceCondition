#include "../include/Player.h"
#include <iostream>
#include <cctype>
#include <thread>
#include <chrono>

using namespace std;

Player::Player(atomic<bool>& desejaPitStop_ref,
               atomic<char>& tipoPneuEscolhido_ref,
               atomic<bool>& corridaTerminou_ref)
    : desejaPitStop(desejaPitStop_ref),
      tipoPneuEscolhido(tipoPneuEscolhido_ref),
      corridaTerminou(corridaTerminou_ref) {}

void Player::interagir() {
    while (!corridaTerminou.load()) {
        char escolha;
        
        // solicita entrada do usuário (s ou n)
        do {
            cout << "deseja fazer um pit stop? (s/n): ";
            cin >> escolha;
            escolha = tolower(escolha);
        } while (escolha != 's' && escolha != 'n');

        if (escolha == 's') {
            desejaPitStop.store(true, memory_order_relaxed);

            char tipo;
            do {
                cout << "escolha o tipo de pneu para troca (s - soft, m - medium, h - hard): ";
                cin >> tipo;
                tipo = tolower(tipo);

                if (tipo != 's' && tipo != 'm' && tipo != 'h') {
                    cout << "tipo de pneu inválido. tente novamente." << endl;
                }
            } while (tipo != 's' && tipo != 'm' && tipo != 'h');

            tipoPneuEscolhido.store(tipo, memory_order_relaxed);
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
