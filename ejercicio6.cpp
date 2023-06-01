#include <iostream>
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio6/100000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int largo;
    cin >> largo;

    int* numeros = new int[largo];

    for (int i=0; i<largo; i++) {
        int numero;
        cin >> numero;
        numeros[i] = numero;
    }

    bool encontre = false;
    int mitad = (largo/2);
    int desde = 0;
    int hasta = largo;

    while (!encontre) {
        if (mitad % 2 != 0) {    
            if (numeros[mitad - 1] == numeros[mitad]) {
                desde = mitad;
            } else if (numeros[mitad + 1] == numeros[mitad]) {
                hasta = mitad-1;
            } else {
                encontre = true;
                cout << numeros[mitad] << endl;
            }
        } else {
            if (numeros[mitad + 1] == numeros[mitad]) {
                desde = mitad+1;
            } else if (numeros[mitad - 1] == numeros[mitad]) {
                hasta = mitad;
            } else {
                encontre = true;
                cout << numeros[mitad] << endl;
            }
        }

        int prox = desde + ((hasta - desde)/2);
        mitad = prox == mitad ? prox+1 : prox;
    }

    delete[] numeros;

    return 0;
}