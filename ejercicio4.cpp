#include <iostream>
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

    Grafo* grafo = new Grafo(ciudades);

    for (int i=0; i<carreteras; i++) {
        int origen, destino, distancia, doble, habilitada;
        cin >> origen;
        cin >> destino; 
        cin >> distancia;
        cin >> doble;
        cin >> habilitada;

        if (habilitada == 1) {
            grafo->agregarArista(origen, destino, distancia);

            if (doble == 2) {
                grafo->agregarArista(destino, origen, distancia);
            }
        }


    }

}