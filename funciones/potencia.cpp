#include <iostream>
using namespace std;

int potencia(int num, int pot) {
    int res = num;
    for (int i=pot; i>1; i--) {
        res *= num;
    }
    return res;
}
