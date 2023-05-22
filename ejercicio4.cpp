#include <iostream>
#include <cstring>
#include "clases/grafo.cpp"
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio4/100.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int ciudades;
    int carreteras;

    cin >> ciudades;
    cin >> carreteras;

    Grafo<int>* grafo = new Grafo<int>(ciudades);

    for (int i=0; i<carreteras; i++) {
        int origen, destino, distancia, doble, habilitada;
        cin >> origen;
        cin >> destino; 
        cin >> distancia;
        cin >> doble;
        cin >> habilitada;

        bool hab = habilitada == 1;
        bool dobleCar = doble == 2;

        if (habilitada) {
            grafo->agregarArista(origen-1, destino-1, distancia);

            if (dobleCar) {
                grafo->agregarArista(destino-1, origen-1, distancia);
            }
        }
    }

}