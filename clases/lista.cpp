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

template <class T>
class IteradorLista {
    private:
        NodoLista<T> *actual, *ppio;

    public:
        IteradorLista(NodoLista<T>* ppio){
            this->actual = this->ppio = ppio;
        }

        void eliminarLista() {
            this->actual = this->ppio = ppio;
            while (this->hayElemento()) {
                this->avanzar();
                delete this->ppio;
                this->ppio = this->actual;
            }
        }

        bool hayElemento() {
            return actual != NULL;
        }

        T obtenerElemento() {
            return actual->dato;
        }

        void avanzar(){
            actual = actual->sig;
        }

        void reiniciar(){
            actual = ppio;
        }
};

template<class T>
class Lista {
    private:
        NodoLista<T> * ppio, * fin;
        int largo;

        void vaciarRec(NodoLista<T>* &nodo){
            if(nodo){
                vaciarRec(nodo->sig);
                delete nodo;
                nodo=NULL;
            }
        }

    public:
        Lista() {
            this->ppio = this->fin = NULL;
            this->largo = 0;
        }

        ~Lista(){
            vaciarRec(ppio);
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

        T obtenerPpio(){
            return this->ppio->dato;
        }

        IteradorLista<T>* obtenerIterador(){
            return new IteradorLista<T>(ppio);
        }
};