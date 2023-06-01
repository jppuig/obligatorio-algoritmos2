#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

class nodoHeap5 {
    public:
        int vertice;
        int nivel;

        nodoHeap5(int vertice, int nivel): vertice(vertice), nivel(nivel) {}
};

class HeapEj5 {
    private:
        nodoHeap5** heap;
        int tope;
        int maxElementos;

        void flotar(int pos){
            if (pos == 0 || this->heap[pos]->nivel > this->heap[(pos-1)/2]->nivel ||
            (this->heap[pos]->nivel == this->heap[(pos-1)/2]->nivel && this->heap[pos]->vertice > this->heap[(pos-1)/2]->vertice)) {
                return;
            }
            else {
                nodoHeap5* temp = this->heap[(pos-1)/2];
                this->heap[(pos-1)/2] = this->heap[pos];
                this->heap[pos] = temp;

                flotar((pos-1)/2);
            }
        }

        void hundir(int pos){
            int hijoMin = pos*2+1;

            if (pos*2+2 < this->tope) {
                if (this->heap[pos*2+1]->nivel > this->heap[pos*2+2]->nivel || 
                (this->heap[pos*2+1]->nivel == this->heap[pos*2+2]->nivel && this->heap[pos*2+1]->vertice > this->heap[pos*2+2]->vertice)) {
                    hijoMin = pos*2+2;
                }
            }
            else if (hijoMin >= this->tope) {
                return;
            }

            if (this->heap[pos]->nivel > this->heap[hijoMin]->nivel || 
            (this->heap[pos]->nivel == this->heap[hijoMin]->nivel && this->heap[pos]->vertice > this->heap[hijoMin]->vertice)) {
                nodoHeap5* temp = this->heap[hijoMin];
                this->heap[hijoMin] = this->heap[pos];
                this->heap[pos] = temp;

                hundir(hijoMin);
            }
        }

    public:
        HeapEj5(int maxElementos){
            this->maxElementos = maxElementos;
            this->tope = 0;
            this->heap = new nodoHeap5*[this->maxElementos];
        }
        
        ~HeapEj5(){
            for (int i = 0; i < this->tope; delete this->heap[i++]);
            delete [] this->heap;
        }

        void encolar(int vertice, int nivel){ 
            this->heap[this->tope] = new nodoHeap5(vertice, nivel);
            this->flotar(this->tope++);
        }

        //Pre: !EsVacia()
        void desencolar(){
            delete this->heap[0];
            this->heap[0] = this->heap[--this->tope];
            this->hundir(0);
        }

        //Pre: !EsVacia()
        int nivelMin(){
            return this->heap[0]->nivel;
        }

        int verticeMenor() {
            return this->heap[0]->vertice;
        }

        bool esVacia(){
            return this->tope == 0;
        }
};