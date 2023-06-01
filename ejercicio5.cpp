#include <iostream>
#include "clases/grafo.cpp"
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio5/tops1.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int vertices;
    int aristas;

    cin >> vertices;
    cin >> aristas;

    Grafo* grafo = new Grafo(vertices);
    int* incidencias = new int[vertices+1];
    for (int i=0; i<=vertices; incidencias[i++]=0);

    for (int i=0; i<aristas; i++) {
        int origen, destino;
        cin >> origen;
        cin >> destino;

        incidencias[destino]++;

        grafo->agregarArista(origen, destino, 1);
    }

    grafo->ordenTopologico(incidencias);

    delete[] incidencias;

    delete grafo;

    return 0;
}