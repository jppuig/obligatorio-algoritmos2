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

        int posNoVisDeMenorCosto(int *dist, bool *vis) {  
            int posMin = -1, min = INF;
            for (int i = 0; i < tope; i++)
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
            this->vertices = new bool[tope];
            this->vertices[0] = false;
            for (int i = 1; i < this->tope; vertices[i++] = true);

            this->listaAdy = new Lista<Arista*>*[tope];
            for (int i = 1; i < this->tope; this->listaAdy[i++] = new Lista<Arista*>());
        }

        ~Grafo() {
            for (int i=1; i<this->tope; i++) {
                delete this->listaAdy[i];
            }
            delete[] this->listaAdy;
        }

        void agregarArista(int origen, int destino, int costo) {
            Arista* arista = new Arista(origen, destino, costo);
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

        for (int i = 0; i < tope; i++) // Inicializo todos los arrays
        {
            vis[i] = false;
            dist[i] = INF;
            ant[i] = -1;
        }

        dist[origen] = 0; // Al origen le agrego distancia 0 (costo 0)

        for (int i = 0; i < this->tope; i++) {
            int proximoVertice = posNoVisDeMenorCosto(dist, vis); // Tomo su arista de menor costo

            if (proximoVertice == -1) // Si es -1 entonces no encontro arista por lo que salgo, no es conexo
            {
                break;
            }

            for (IteradorLista<Arista*>* j = this->listaAdy[proximoVertice]->obtenerIterador(); j->hayElemento(); j->avanzar()) // Para todas las posibles aristas del proximo vertice 
            {
                Arista* carretera = j->obtenerElemento();
                if (!vis[carretera->destino] && carretera->habilitada) // Si existe y no esta visitada
                {
                    int nuevaDistancia = dist[proximoVertice] + carretera->costo; // Tomo distancia anterior y le sumo actual
                    if (dist[carretera->destino] > nuevaDistancia) // Si esta es menor a la que ya tengo
                    {
                        dist[carretera->destino] = nuevaDistancia; // Actualizo distancia
                        ant[carretera->destino] = proximoVertice; // Actualizo anterior
                    }
                }
            }
            vis[proximoVertice] = true; // Marco vertice como visitado
        }
        
        if (ant[destino] == -1) {
            cout << -1 << endl;
            cout << "[]" << endl;
        } else {
            cout << dist[destino] << endl;
            cout << "[";
            
            int prox = destino;
            Lista<int>* camino = new Lista<int>();
            
            while (ant[prox] == 0) {
                camino->insertarPpio(prox);
                prox = ant[prox];
            }
            
            while (!camino->esVacia()) {
                cout << camino->obtenerPpio();
                camino->borrarPpio();
                if (!camino->esVacia()) {
                    cout << ", ";
                }
            }
            
            cout << "]" << endl;

            delete camino;
        }
    }
};