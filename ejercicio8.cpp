#include <iostream>
#include "clases/heapEj8.cpp"
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio8/100000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    // 2 heap uno que llega y otro que se va
    // Saco del primero y agrego en el segundo solo la hora de salida, si el proximo del primero
    // es menor al primero del segundo entonces agrego, sino elimino el primero del segundo
    // y vuelvo a comparar. El numero maximo en cualquier momento de la cantidad de elementos
    // en el segundo heap es la cantidad de puertas que tengo que construir.

    int cantidadAviones;
    cin >> cantidadAviones;

    HeapEj8* heap = new HeapEj8(cantidadAviones*2);

    for (int i=0; i<cantidadAviones; i++) {
        int llegada, salida;
        cin >> llegada;
        cin >> salida;

        heap->encolar(llegada, true);
        heap->encolar(salida, false);
    }

    int actual = 0;
    int max = 0;

    for (int i=0; i<cantidadAviones*2; i++) {
        bool esLlegada = heap->esLlegadaMin();

        if (esLlegada) {
            actual++;
            if (actual > max) {
                max = actual;
            }
        } else {
            actual--;
        }

        heap->desencolar();
    }

    cout << max << endl;

    delete heap;

    return 0;
}