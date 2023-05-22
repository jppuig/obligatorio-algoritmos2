#include <iostream>
#include <cstring>
#include "clases/heap.cpp"
#include <cmath>

#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio3/100.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cant;
    cin >> cant;

    Heap* heap = new Heap(cant);

    for (int i=0;i<cant;i++) {
        int cantPas;
        double prom;
        double suma = 0;
        cin >> cantPas;

        string* pasajeros = new string[cantPas];

        for (int j=0;j<cantPas;j++) {
            string pas;
            double vuelos;

            cin >> pas;
            cin >> vuelos;

            pasajeros[j] = pas;
            suma += vuelos;
        }
        
        prom = round((suma / cantPas) * 100) / 100;
        heap->encolar(prom, pasajeros, cantPas);
    }

    heap->mostrar();
    
    heap->~Heap();
    
    return 0;
}