#include <iostream>
#include "clases/heapEj8.cpp"
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio9/coef10e3.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int n, p;
    cin >> n;
    cin >> p;

    long long* pascal = new long long[n];
    int j = 0;
    pascal[0] = 1;

    for (int i=0; i<p; i++) {
        int fila, col;
        cin >> fila;
        cin >> col;

        if (fila > j) {
            pascal[++j] = 1;
            if (i > 1) {
                for (int k=j-1; k>0; k--) {
                    pascal[k] += pascal[k-1];
                }
            }
        }
        

        if (fila == j) {
            cout << pascal[col] << endl;
        }
    }

    delete pascal;

    return 0;
}