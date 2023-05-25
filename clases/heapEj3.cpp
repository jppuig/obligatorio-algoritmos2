#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

class nodoHeap {
    public:
        double prom;
        int cantPas;
        string* pasajeros;

        nodoHeap(double prom, string* pasajeros, int cantPas): prom(prom), pasajeros(pasajeros), cantPas(cantPas) {}
};

class Heap {
    private:
        nodoHeap** heap;
        int tope;
        int maxElementos;

        void flotar(int pos){
            if (pos == 0 || this->heap[pos]->prom <= this->heap[(pos-1)/2]->prom) {
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
                if (this->heap[pos*2+1]->prom < this->heap[pos*2+2]->prom) {
                    hijoMax = pos*2+2;
                }
            }
            else if (hijoMax >= this->tope) {
                return;
            }

            if (this->heap[pos]->prom < this->heap[hijoMax]->prom) { // fijarse si = va arriba
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

        void encolar(double prom, string* pasajeros, int cantPas){ // &
            this->heap[this->tope] = new nodoHeap(prom, pasajeros, cantPas);
            this->flotar(this->tope++);
        }

        //Pre: !EsVacia()
        void desencolar(){
            delete this->heap[0];
            this->heap[0] = this->heap[--this->tope];
            this->hundir(0);
        }

        //Pre: !EsVacia()
        string* pasajerosMax(){
            return this->heap[0]->pasajeros;
        }

        //Pre: !EsVacia()
        double promMax(){
            return this->heap[0]->prom;
        }

        //Pre: !EsVacia()
        int cantPasMax(){
            return this->heap[0]->cantPas;
        }

        bool esVacia(){
            return this->tope == 0;
        }

        void mostrar() {
            while(!this->esVacia()) {
                double max = this->promMax();
                if (std::fmod(max, 1.0) != 0.0) {
                    cout << std::fixed << std::setprecision(2) << max << " ";
                } else {
                    cout << std::fixed << std::setprecision(0) << max << " ";
                }    
                // cout << this->promMax() << " ";
                for (int i=0;i<this->cantPasMax();i++) {
                    cout << this->pasajerosMax()[i] << " ";
                }
                cout << endl;
                this->desencolar();
            }
        }
};