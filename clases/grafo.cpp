#include <iostream>
#include "./lista.cpp"
#define INF 99999
using namespace std;

class Arista {
    public:
        int costo, origen, destino;
        Arista(int costo, int origen, int destino) : costo(costo), origen(origen), destino(destino) {}
};

class Grafo {
    private:
        int tope;
        int* vertices;
        Lista<Arista*>** listaAdy;

    public:
        Grafo(int tope) {
            this->tope = tope;
            this->vertices = new int[tope];
            for (int i = 0; i < tope; vertices[i++] = NULL);

            this->listaAdy = new Lista<Arista*>*[tope];
            for (int i = 0; i < tope; this->listaAdy[i++] = NULL);
        }

        void agregarArista(int origen, int destino, int costo) {
            Arista* arista = new Arista(origen, destino, costo);
            this->listaAdy[origen-1]->insertarPpio(arista);
        }
};