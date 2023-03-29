#include <iostream>
#include <cstring>
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    int cant;
    cin >> cant;

    //avl

    for (int i=0;i<cant;i++) {
        char* palabra;
        cin >> palabra;
        avl->agregar(palabra);
    }
}