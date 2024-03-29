#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

class nodoHeap4 {
    public:
        int vertice;
        int distancia;

        nodoHeap4(int vertice, int distancia): vertice(vertice), distancia(distancia) {}
};

class HeapEj4 {
    private:
        nodoHeap4** heap;
        int tope;
        int maxElementos;

        void flotar(int pos){
            if (pos == 0 || this->heap[pos]->distancia >= this->heap[(pos-1)/2]->distancia) {
                return;
            }
            else {
                nodoHeap4* temp = this->heap[(pos-1)/2];
                this->heap[(pos-1)/2] = this->heap[pos];
                this->heap[pos] = temp;

                flotar((pos-1)/2);
            }
        }

        void hundir(int pos){
            int hijoMin = pos*2+1;

            if (pos*2+2 < this->tope) {
                if (this->heap[pos*2+1]->distancia > this->heap[pos*2+2]->distancia) {
                    hijoMin = pos*2+2;
                }
            }
            else if (hijoMin >= this->tope) {
                return;
            }

            if (this->heap[pos]->distancia > this->heap[hijoMin]->distancia) {
                nodoHeap4* temp = this->heap[hijoMin];
                this->heap[hijoMin] = this->heap[pos];
                this->heap[pos] = temp;

                hundir(hijoMin);
            }
        }

    public:
        HeapEj4(int maxElementos){
            this->maxElementos = maxElementos;
            this->tope = 0;
            this->heap = new nodoHeap4*[this->maxElementos];
        }
        ~HeapEj4(){
            for (int i = 0; i < this->tope; delete this->heap[i++]);
            delete [] this->heap;
        }

        void encolar(int vertice, int distancia){ 
            this->heap[this->tope] = new nodoHeap4(vertice, distancia);
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