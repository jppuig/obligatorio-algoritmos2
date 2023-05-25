#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class nodoAVL {
    public:
        string palabra;
        int ocurrencias;
        int balance;
        nodoAVL *izq;
        nodoAVL *der;

        nodoAVL(string palabra): palabra(palabra), ocurrencias(1), balance(0), izq(NULL), der(NULL) {} // Necesario poner en NULL
};

class AVL {
    private:
        nodoAVL* raiz;
        bool vario;
        int cantElem;

        void insertarRec(nodoAVL*& r, string pal) {
            if (!r) {
                r = new nodoAVL(pal);
                this->vario = true;
            } 
            else {
                int resultado = r->palabra.compare(pal);
                if (resultado < 0) {
                    this->insertarRec(r->der, pal); 
                    if(this->vario) {/* crecio la altura subarbol derecho */
                        switch (r->balance) {
                            case -1:
                                r->balance = 0;
                                this->vario = false;
                                break;
                            case 0:
                                r->balance = 1;
                                break;
                            case 1:
                                nodoAVL* p1 = r->der;
                                if (p1->balance == 1) { /* DD */
                                    r->der = p1->izq;
                                    p1->izq = r;
                                    r->balance = 0;
                                    r = p1;
                                }
                                else { /* DI */
                                    nodoAVL* p2 = p1 ->izq;
                                    p1->izq = p2->der;
                                    p2->der = p1;
                                    r->der = p2->izq;
                                    p2->izq = r;
                                    r->balance = p2->balance == 1 ? -1 : 0;
                                    p1->balance = p2->balance == -1 ? 1 : 0;
                                    r = p2;
                                }
                                r->balance = 0;
                                this->vario = false;
                        }
                    }
                }
                else if (resultado > 0) {
                    this->insertarRec(r->izq, pal);
                    if (this->vario) { /* crecio altura de subarbol izquierdo */
                        switch(r->balance) {
                            case 1:
                                r->balance = 0;
                                this->vario = false;
                                break;
                            case 0:
                                r->balance= -1;
                                break;
                            case -1:
                                nodoAVL* p1 = r->izq;
                                if (r->balance == -1) {
                                    r->izq = p1->der;
                                    p1->der = r;
                                    r->balance = 0;
                                    r = p1;
                                }
                                else {
                                    nodoAVL* p2 = p1->der;
                                    r->der = p2->izq;
                                    p2->izq = p1;
                                    r->izq = p2->der;
                                    p2->der = r;
                                    r->balance = p2->balance == -1 ? 1 : 0;
                                    p1->balance = p2->balance == 1 ? -1 : 0;
                                    r = p2;
                                }
                                r->balance = 0;
                                this->vario = false;
                        }
                    }
                }
                else {
                    r->ocurrencias++;
                }
            }
        }

        void destruir(nodoAVL* r) {
            if (!r) {
                return;
            }

            this->destruir(r->izq);
            this->destruir(r->der);
            delete r;
        }

        void mostrarRec(nodoAVL* r) {
            if (!r) {
                return;
            }

            this->mostrarRec(r->der);
            cout << r->palabra << " " << r->ocurrencias << endl;
            this->mostrarRec(r->izq);
        }

    public:
        AVL(): raiz(NULL), vario(false) {}
        
        ~AVL() {
            this->destruir(this->raiz);
        }

        void insertar(string pal) {
            this->insertarRec(this->raiz, pal);
        }

        void mostrar() {
            this->mostrarRec(this->raiz);
        }
};