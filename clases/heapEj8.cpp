#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

class nodoHeap8 {
    public:
        int hora;
        bool esLlegada;

        nodoHeap8(int hora, int esLlegada): hora(hora), esLlegada(esLlegada) {}
};

class HeapEj8 {
    private:
        nodoHeap8** heap;
        int tope;
        int maxElementos;

        void flotar(int pos){
            if (pos == 0 || this->heap[pos]->hora > this->heap[(pos-1)/2]->hora
            || (this->heap[pos]->hora == this->heap[(pos-1)/2]->hora && !this->heap[(pos-1)/2]->esLlegada)) {
                return;
            }
            else {
                nodoHeap8* temp = this->heap[(pos-1)/2];
                this->heap[(pos-1)/2] = this->heap[pos];
                this->heap[pos] = temp;

                flotar((pos-1)/2);
            }
        }

        void hundir(int pos){
            int hijoMin = pos*2+1;

            if (pos*2+2 < this->tope) {
                if (this->heap[pos*2+1]->hora > this->heap[pos*2+2]->hora
                || (this->heap[pos*2+1]->hora == this->heap[pos*2+2]->hora && !this->heap[pos*2+2]->esLlegada)) {
                    hijoMin = pos*2+2;
                }
            }
            else if (hijoMin >= this->tope) {
                return;
            }

            if (this->heap[pos]->hora > this->heap[hijoMin]->hora ||
            (this->heap[pos]->hora == this->heap[hijoMin]->hora && !this->heap[hijoMin]->esLlegada)) {
                nodoHeap8* temp = this->heap[hijoMin];
                this->heap[hijoMin] = this->heap[pos];
                this->heap[pos] = temp;

                hundir(hijoMin);
            }
        }

    public:
        HeapEj8(int maxElementos){
            this->maxElementos = maxElementos;
            this->tope = 0;
            this->heap = new nodoHeap8*[this->maxElementos];
        }
        
        ~HeapEj8(){
            for (int i = 0; i < this->tope; delete this->heap[i++]);
            delete [] this->heap;
        }

        void encolar(int hora, bool esLlegada){ 
            this->heap[this->tope] = new nodoHeap8(hora, esLlegada);
            this->flotar(this->tope++);
        }

        //Pre: !EsVacia()
        void desencolar(){
            delete this->heap[0];
            this->heap[0] = this->heap[--this->tope];
            this->hundir(0);
        }

        //Pre: !EsVacia()
        bool esLlegadaMin(){
            return this->heap[0]->esLlegada;
        }

        int horaMin() {
            return this->heap[0]->hora;
        }

        bool esVacia(){
            return this->tope == 0;
        }
};