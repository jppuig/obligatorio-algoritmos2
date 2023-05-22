#include <iostream>
#define INF 99999
using namespace std;

class Arista
{
public:
    int costo, origen, destino;
    bool existe;
    Arista(int costo, int origen, int destino) : costo(costo), origen(origen), destino(destino), existe(true) {}
    Arista(int costo) : costo(costo), existe(true) {}
    Arista() : costo(0), existe(false) {}
};

int fComp(Arista* a, Arista* b){
    return a->costo - b->costo;
}
template <class T>
class Grafo
{
private:
    int tope;
    bool esDirigido;
    T **vertices;
    Lista<Arista*>** listaAdy;

    int posVertice(T origen)
    {
        for (int i = 0; i < this->tope; i++)
        {
            if (this->vertices[i] && *this->vertices[i] == origen)
            {
                return i;
            }
        }
        return -1;
    }

    void ubicarVertices(T origen, int &posOrigen, T destino, int &posDestino)
    {
        for (int i = 0; i < this->tope && (posOrigen == -1 || posDestino == -1); i++)
        {
            if (this->vertices[i] && *this->vertices[i] == origen)
            {
                posOrigen = i;
            }
            if (this->vertices[i] && *this->vertices[i] == destino)
            {
                posDestino = i;
            }
        }
    }

    int buscarElemSinIncidencias(int *cantInicidencias)
    {
        for (int i = 0; i < this->tope; i++)
        {
            if (cantInicidencias[i] == 0)
            {
                return i;
            }
        }
        return -1;
    }

    int posNoVisDeMenorCosto(int *dist, bool *vis)
    {
        int posMin = -1, min = INF;
        for (int i = 0; i < tope; i++)
        {
            if (!vis[i] && dist[i] < min)
            {
                posMin = i;
                min = dist[i];
            }
        }
        return posMin;
    }
    void dfsRec(int pos, bool *&vis)
    {
        cout << *(this->vertices[pos]) << endl; // Imprimo elemento
        vis[pos] = true; // Lo marco como visitado
        for (int i = 0; i < this->tope; i++) // Para todas las posibles aristas desde el vertice
        {
            if (this->matAdy[pos][i]->existe && !vis[i]) // Si existe y no esta visitado
            {
                dfsRec(i, vis); // Llamo a su recursiva con cada uno
            }
        }
    }

public:
    Grafo(int tope)
    {
        this->tope = tope;
        this->esDirigido = esDirigido;

        this->vertices = new T *[tope];
        for (int i = 0; i < tope; vertices[i++] = NULL)
            ;

        this->listaAdy = new Lista<Arista*>*[tope];
        for (int i = 0; i < tope; i++)
        {
            this->listaAdy[i] = NULL; 
        }
    }

    void agregarArista(T origen, T destino, int costo)
    {
        Arista<int>* arista = new Arista<int>(origen, destino, costo);
        this->listaAdy[origen]->insertarPpio();
        this->matAdy[posOrigen][posDestino]->costo = costo;
    }

    // Busqueda en profundidad
    void dfs(T origen)
    {
        int posOrigen = posVertice(origen); // Busco la posicion del elemento origen en el vector de vertices
        bool *vis = new bool[this->tope]; // Creo vector de visitados de largo de los vertices
        for (int i = 0; i < this->tope; vis[i++] = false) // Inicializo todos las posiciones de visitados en false
            ;
        dfsRec(posOrigen, vis); // Llamo a la recursiva con la posicion del elemento origen en el vector de vertices
    }

    // Busqueda en amplitud
    // Aplicacion en PPT
    void bfs(T origen)
    {
        int posOrigen = posVertice(origen); // Busco posicion del elemento origen en el vector de vertices
        bool *vis = new bool[this->tope]; // Creo vector de visitados de largo de los vertices
        for (int i = 0; i < this->tope; vis[i++] = false) // Inicializo todos las posiciones de los visitados en false
            ;
        Lista<int> *cola = new Lista<int>();
        cola->insertarFin(posOrigen); // Inserta la posicion del elemento origen en la lista
        vis[posOrigen] = true; // Lo marca como visitado
        while (!cola->esVacia()) // Mientras la cola no sea vacia
        {
            int pos = cola->obtenerPpio(); // Guarda el primero
            cola->borrar(cola->obtenerPpio()); // Lo borra de la lista
            cout << *(this->vertices[pos]) << endl; //Imprime el elemento
            for (int i = 0; i < this->tope; i++) // Para todas sus posibles aristas
            {
                if (this->matAdy[pos][i]->existe && !vis[i]) // Si existe y va a un nodo no visitado
                {
                    cola->insertarFin(i); // Inserta en la cola
                    vis[i] = true; // y lo marca como visitado
                }
            }
        }
    }
};