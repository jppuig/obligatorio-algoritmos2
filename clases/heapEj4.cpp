#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

class nodoHeap {
    public:
        int vertice;
        int distancia;

        nodoHeap(int vertice, int distancia): vertice(vertice), distancia(distancia) {}
};

class Heap {
    private:
        nodoHeap** heap;
        int tope;
        int maxElementos;

        void flotar(int pos){
            if (pos == 0 || this->heap[pos]->distancia >= this->heap[(pos-1)/2]->distancia) {
                return;
            }
            else {
                nodoHeap* temp = this->heap[(pos-1)/2];
                this->heap[(pos-1)/2] = this->heap[pos];
                this->heap[pos] = temp;

                flotar((pos-1)/2);
            }
        }

        void hundir(int pos){
            int hijoMax = pos*2+1;

            if (pos*2+2 < this->tope) {
                if (this->heap[pos*2+1]->distancia > this->heap[pos*2+2]->distancia) {
                    hijoMax = pos*2+2;
                }
            }
            else if (hijoMax >= this->tope) {
                return;
            }

            if (this->heap[pos]->distancia > this->heap[hijoMax]->distancia) {
                nodoHeap* temp = this->heap[hijoMax];
                this->heap[hijoMax] = this->heap[pos];
                this->heap[pos] = temp;

                hundir(hijoMax);
            }
        }

    public:
        Heap(int maxElementos){
            this->maxElementos = maxElementos;
            this->tope = 0;
            this->heap = new nodoHeap*[this->maxElementos];
        }
        ~Heap(){
            for (int i = 0; i < this->tope; delete this->heap[i++]);
            delete [] this->heap;
        }

        void encolar(int vertice, int distancia){ 
            this->heap[this->tope] = new nodoHeap(vertice, distancia);
            this->flotar(this->tope++);
        }

        //Pre: !EsVacia()
        void desencolar(){
            delete this->heap[0];
            this->heap[0] = this->heap[--this->tope];
            this->hundir(0);
        }

        //Pre: !EsVacia()
        int distanciaMin(){
            return this->heap[0]->distancia;
        }

        int verticeMenorDist() {
            return this->heap[0]->vertice;
        }

        bool esVacia(){
            return this->tope == 0;
        }
};