#include <iostream>
#include "./lista.cpp"
#define INF 99999
using namespace std;

class Arista {
    public:
        int costo, origen, destino;
        bool habilitada;
        Arista(int costo, int origen, int destino) : costo(costo), origen(origen), destino(destino), habilitada(true) {}
};

class Grafo {
    private:
        int tope;
        bool* vertices;
        Lista<Arista*>** listaAdy;

    public:
        Grafo(int tope) {
            this->tope = tope;
            this->vertices = new bool[tope];
            for (int i = 0; i < tope; vertices[i++] = true);

            this->listaAdy = new Lista<Arista*>*[tope];
            for (int i = 0; i < tope; this->listaAdy[i++] = new Lista<Arista*>());
        }

        void agregarArista(int origen, int destino, int costo) {
            Arista* arista = new Arista(origen, destino, costo);
            this->listaAdy[origen-1]->insertarPpio(arista);
        }

        // Suponemos que no piden deshabilitar carreteras no existentes
        void deshabilitarArista(int origen, int destino) {
            bool deshabilite = false;

            for (IteradorLista<Arista *>* it = this->listaAdy[origen-1]->obtenerIterador(); it->hayElemento() && !deshabilite; it->avanzar()) {
                Arista* carretera = it->obtenerElemento();
                if (carretera->destino == destino) {
                    carretera->habilitada = false;
                    deshabilite = true;
                }
            }
        }

        void deshabilitarCiudad(int pos) {
            this->vertices[pos-1] = false;
        }
};