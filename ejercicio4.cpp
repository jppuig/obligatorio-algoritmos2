#include <iostream>
#include "clases/grafo.cpp"
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio4/100000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int ciudades;
    int carreteras;
    int cantCiudadesDeshabilitadas;
    int cantCarreterasDeshabilitadas;
    int ciudadDesde;
    int ciudadHasta;

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

        if (habilitada == 1) {      // Chequeo si esta habilitada y sino agrego arista
            grafo->agregarArista(origen, destino, distancia);

            if (doble == 2) {
                grafo->agregarArista(destino, origen, distancia);
            }
        }
    }

    cin >> cantCiudadesDeshabilitadas;
    for (int i=0; i<cantCiudadesDeshabilitadas; i++) {
        int ciudad;
        cin >> ciudad;

        grafo->deshabilitarVertice(ciudad);     // Deshabilita la ciudad
    }

    cin >> cantCarreterasDeshabilitadas;
    for (int i=0; i<cantCarreterasDeshabilitadas; i++) {
        int carreteraOrigen, carreteraDestino;

        cin >> carreteraOrigen;
        cin >> carreteraDestino;

        grafo->deshabilitarArista(carreteraOrigen, carreteraDestino);   // Deshabilita la arista
    }

    cin >> ciudadDesde;     // Ciudad origen a buscar
    cin >> ciudadHasta;     // Ciudad destino a buscar

    grafo->dijkstra(ciudadDesde, ciudadHasta);

    delete grafo;

    return 0;
}