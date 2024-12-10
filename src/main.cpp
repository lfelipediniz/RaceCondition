#include "../include/Jogo.h"
#include <iostream>
#include <cctype>

using namespace std;

int main() {
    char tipoPneuInicial;
    cout << "escolha o tipo de pneu inicial (s/m/h): ";
    cin >> tipoPneuInicial;
    tipoPneuInicial = tolower(tipoPneuInicial);

    if (tipoPneuInicial != 's' && tipoPneuInicial != 'm' && tipoPneuInicial != 'h') {
        cout << "tipo de pneu inválido. usando pneu 's' por padrão." << endl;
        tipoPneuInicial = 's';
    }

    Jogo jogo(tipoPneuInicial);
    jogo.iniciar();

    return 0;
}
