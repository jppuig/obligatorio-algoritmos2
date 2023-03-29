#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class nodoAVL {
    public:
        char* palabra;
        int ocurrencias;
        int balance;
        nodoAVL *izq;
        nodoAVL *der;

        nodoAVL(char* palabra): palabra(palabra), ocurrencias(1), balance(0), izq(NULL), der(NULL) {} // Necesario poner en NULL

}

class avl {
    private:
        nodoAVL* raiz;
        bool vario;
        int cantElem;

        int menor(int a, int b) {
            int min = b;

            if (a < b)
                min = a;

            return min;
        }

        int cualMayor(char* str1, char* str2) {
            int largoMenor = menor(largo(str1), largo(str2));
            int res = 0;
            
            for (int i = 0; i < largoMenor + 1 && res == 0; i++) {
                if (i == largoMenor) {
                    if (str1[i] == NULL && str2[i] != NULL)
                        res = 1;
                    else if (str1[i] != NULL && str2[i] == NULL)
                        res = -1;
                }
                else {
                    if (str1[i] != str2[i]) {
                        if (str1[i] < str2[i]) {
                            res = 1;
                        }
                        else {
                            res = -1;
                        }
                    }
                }
            }
                
            return res;
        }

    public:
        avl(): raiz(NULL), vario(false) {} // A preguntar

        void insertar(nodoAVL* r, char* pal) {
            if (!r) {
                r = new nodoAVL(pal);
                this->vario = true;
            } 
            else {
                int resultado = cualMayor(r->palabra, pal);
                else if (resultado == 1) {
                    this->insertar(r->der, pal); // con this??
                    if(this->vario) /* crecio la altura subarbol derecho */
                        switch (r->balance) {
                            case -1:
                                r->balance = 0;
                                this->vario = false;
                                break;
                            case 0:
                                r->balance = 1;
                                break;
                            case 1:
                                p1 = p->der;
                                if (p1->balance == 1)
                                { /* DD */
                                p->der = p1->izq;
                                p1->izq = r;
                                r->balance = 0;
                                r = p1;
                                }
                                else
                                { /* DI */
                                p2 = p1 ->izq;
                                p1->izq = p2->der;
                                p2->der = p1;
                                r->der = p2->izq;
                                p2->izq = r;
                                p->balance = p2->balance == 1 ? -1 : 0;
                                p1->balance = p2->balance == -1 ? 1 : 0;
                                r = p2;
                                }
                                r->balance = 0;
                                this->vario = false;
                }
                else if (resultado == -1) {
                    this->insertar(r->izq, pal);
                    if (this->vario) /* crecio altura de subarbol izquierdo */
                        switch(r->balance) {
                            case 1:
                                r->balance = 0;
                                this->vario = false;
                                break;
                            case 0:
                                r->balance= -1;
                                break;
                            case -1:
                                p1 = r->izq;
                                if (r->balance == -1) {
                                    r->izq = r->der;
                                    r->der = r;
                                    r->balance = 0;
                                    r = p1;
                                }
                                else {
                                    p2 = p1->der;
                                    r->der = p2->izq;
                                    p2->izq = p1;
                                    r->izq = p2->der;
                                    p2->der = r;
                                    r->balance = r->balance == -1 ? 1 : 0;
                                    r->balance = r->balance == 1 ? -1 : 0;
                                    r = p2;
                                }
                                r->balance = 0;
                                this->vario = false;
                }
                else {
                    r->ocurrencias++;
                }
            }
            }
        }
}