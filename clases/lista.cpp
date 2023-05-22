#include <iostream>
using namespace std;

template<class T>
class NodoLista {
    public:
        T dato;
        NodoLista<T> * sig, * ant;

        NodoLista(T dato) : dato(dato), sig(NULL), ant(NULL){}
        NodoLista(T dato, NodoLista<T> *ant, NodoLista<T> *sig): dato(dato), sig(sig), ant(ant){}
};

template<class T>
class Lista {
    private:
        NodoLista<T> * ppio, * fin;
        int largo;

        bool perteneceRec(T dato, NodoLista<T>* nodo){
            return nodo && (dato == nodo->dato || perteneceRec(dato, nodo->sig));
        }

        void borrarRec(T dato, NodoLista<T> *& nodo){
            if(nodo){
                if(dato == nodo->dato){
                    NodoLista<T> * aBorrar = nodo;
                    nodo = nodo->sig;
                    if(nodo){
                        nodo->ant = aBorrar->ant;
                    } else {
                        this->fin = this->fin->ant;
                        if(!this->fin){
                            this->ppio=NULL;
                        }
                    }
                    delete aBorrar;
                    this->largo--;
                } else {
                    borrarRec(dato, nodo->sig);
                }
            }
        }

        void mostrarRec(NodoLista<T> *nodo){
            if(nodo){
                cout << nodo->dato << endl;
                mostrarRec(nodo->sig);
            }
        }

        void vaciarRec(NodoLista<T>* &nodo){
            if(nodo){
                vaciarRec(nodo->sig);
                delete nodo;
                nodo=NULL;
            }
        }

    public:

        ~Lista(){
            vaciarRec(ppio);
        }

        void vaciar(){
            vaciarRec(ppio);
            largo=0;
            fin=NULL;
        }

        int cantidadElementos(){
            return this->largo;
        }

        bool esVacia() {
            return this->largo==0;
        }

        bool pertenece(T dato) {
            return perteneceRec(dato, this->ppio);
        }

        void insertarPpio(T dato){
            this->ppio = new NodoLista<T>(dato, NULL, this->ppio);
            if(!this->fin){
                this->fin = this->ppio;
            }
            else
            {
                this->ppio->sig->ant = this->ppio;
            }
            this->largo++;
        }

        void insertarFin(T dato){
            this->fin = new NodoLista<T>(dato, this->fin, NULL);
            if(!this->ppio){
                this->ppio = this->fin;
            }
            else
            {
                this->fin->ant->sig = this->fin;
            }
            this->largo++;
        }

        // Inserta de forma ordenada
        void insertarOrd(T dato, int(*fComp)(T a, T b)){
            if(!ppio || fComp(ppio->dato, dato)  >= 0){
                insertarPpio(dato);
                return;
            }
            if(fComp(dato, fin->dato) >= 0){
                insertarFin(dato);
                return;
            }
            NodoLista<T>* aux = ppio, *nuevo;
            while(fComp(aux->sig->dato, dato) < 0){
                aux = aux->sig;
            }
            nuevo = new NodoLista<T>(dato, aux, aux->sig);
            aux->sig->ant = nuevo;
            aux->sig = nuevo;
            largo++;
        }

        void borrar(T dato){
            borrarRec(dato, this->ppio);
        }

        void mostrar(){
            mostrarRec(this->ppio);
        }

        T obtenerPpio(){
            return this->ppio->dato;
        }

        T obtenerFin(){
            return this->fin->dato;
        }

        IteradorLista<T>* obtenerIterador(){
            return new IteradorLista<T>(ppio);
        }
};