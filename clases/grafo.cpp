#include <iostream>
#include "./lista.cpp"
#include "./heapEj4.cpp"
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

        int posNoVisDeMenorCosto(int *dist, bool *vis) {  
            int posMin = -1, min = INF;
            for (int i = 1; i < tope; i++)
            {
                if (!vis[i] && dist[i] < min && this->vertices[i])
                {
                    posMin = i;
                    min = dist[i];
                }
            }
            return posMin;
        }

    public:
        Grafo(int tope) {
            this->tope = tope+1;
            this->vertices = new bool[this->tope];
            this->vertices[0] = false;
            for (int i = 1; i < this->tope; vertices[i++] = true);

            this->listaAdy = new Lista<Arista*>*[this->tope];
            for (int i = 1; i < this->tope; this->listaAdy[i++] = new Lista<Arista*>());
        }

        ~Grafo() {
            for (int i=1; i<this->tope; i++) {
                delete this->listaAdy[i];
            }
            delete[] this->listaAdy;
        }

        void agregarArista(int origen, int destino, int costo) {
            Arista* arista = new Arista(costo, origen, destino);
            this->listaAdy[origen]->insertarPpio(arista);
        }

        // Suponemos que no piden deshabilitar carreteras no existentes
        void deshabilitarArista(int origen, int destino) {
            bool deshabilite = false;

            for (IteradorLista<Arista *>* it = this->listaAdy[origen]->obtenerIterador(); it->hayElemento() && !deshabilite; it->avanzar()) {
                Arista* carretera = it->obtenerElemento();
                if (carretera->destino == destino) {
                    carretera->habilitada = false;
                    deshabilite = true;
                }
            }
        }

        void deshabilitarCiudad(int pos) {
            this->vertices[pos] = false;
        }

        void dijkstra(int origen, int destino) {
            bool *vis = new bool[tope]; // Array de visitados
            int *dist = new int[tope]; // Array de distancias
            int *ant = new int[tope]; // Array de anteriores
            Heap* heap = new Heap(tope*3); // Heap para alcanzar en O(M+NLogN)

            for (int i = 1; i < tope; i++) // Inicializo todos los arrays
            {
                vis[i] = false;
                dist[i] = INF;
                ant[i] = -1;
            }

            vis[0] = true; // No usamos pos 0 del vector
            dist[origen] = 0; // Al origen le agrego distancia 0 (costo 0)
            heap->encolar(origen, dist[origen]); // Agrego origen al heap

            while (!heap->esVacia()) {
                int proximoVertice = heap->verticeMenorDist(); // Tomo su vertice de menor costo
                heap->desencolar(); // Lo elimino del heap

                if (!vis[proximoVertice]) { // Si vertice ya esta visitado no hago nada
                    vis[proximoVertice] = true; // Marco vertice como visitado

                    for (IteradorLista<Arista*>* j = this->listaAdy[proximoVertice]->obtenerIterador(); j->hayElemento(); j->avanzar()) {
                        Arista* carretera = j->obtenerElemento(); // Tomo arista

                        if (!vis[carretera->destino] && carretera->habilitada) {// Si arista esa habilitada y vertice al que llega no esta visitado
                            int nuevaDistancia = dist[proximoVertice] + carretera->costo; // Tomo distancia actual del vertice de menor costo y le sumo la de la arista
                            
                            if (dist[carretera->destino] > nuevaDistancia) {// Si es menor a la que ya tiene el vertice del destino entonces encontre una mejor
                                dist[carretera->destino] = nuevaDistancia;
                                ant[carretera->destino] = proximoVertice;
                                heap->encolar(carretera->destino, dist[carretera->destino]);
                            }
                        }
                    }
                }

            }
            
            if (ant[destino] == -1) { // No es conexo entonces no hay camino
                cout << -1 << endl;
                cout << "[]" << endl;
            } else {
                Lista<int>* camino = new Lista<int>(); // Creo lista para agregar el camino
                camino->insertarPpio(destino);
                int prox = ant[destino];
                
                while (camino->obtenerPpio() != origen) {
                    camino->insertarPpio(prox);
                    prox = ant[prox];
                }
                
                cout << dist[destino] << endl;
                // cout << "[";
                
                while (!camino->esVacia()) {
                    cout << camino->obtenerPpio() << " "; // Eliminar espacio y descomentar lo otro para entrega
                    camino->borrarPpio();
                    // if (!camino->esVacia()) {
                    //     cout << ", ";
                    // }
                }
                
                // cout << "]" << endl;

                delete camino;
        }
    }
};