#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class nodoHash {
    public:
        int prom;
        string nombre;

        nodoHash(int prom, string nombre): prom(prom), nombre(nombre) {}
};

class HashCerrado {
    private:
        nodoHash** hash;
        int largo;
        int maxElementos;
        int (*fHash)(string);

        bool esPrimo(int num){
            if(num<=1)
            {
                return false;
            } else {
                for (int i = 2; i <= num/2; i++)
                {
                    if(num%i==0)
                    {
                        return false;
                    }
                }
                return true;
            }
        }

        int primoSup(int num){
            while(!esPrimo(++num));
            return num;
        }

    public:
        HashCerrado(int maxElementos, int (*fHash)(string)){
            this->maxElementos = primoSup(maxElementos);
            this->largo = 0;
            this->hash = new nodoHash*[this->maxElementos];
            for (int i = 0; i < this->maxElementos; i++)
            {
                this->hash[i]=NULL;
            }
            
            this->fHash=fHash;
        }

        ~HashCerrado() {
            for (int i = 0; i < this->maxElementos; delete this->hash[i++]);
            delete [] this->hash;
        }

        void agregar(string str,int num){
            int primera = this->fHash(str) % this->maxElementos;
            int pos = primera;
            int contador = 0;
            while(this->hash[pos]){
                pos = (primera + static_cast<int>(pow(++contador, 2))) % this->maxElementos;
            }
            this->hash[pos] = new nodoHash(num, str);
        }

        int elemento(string str) {
            int primera = this->fHash(str) % this->maxElementos;
            int pos = primera;
            int contador = 0;
            while(this->hash[pos]->nombre != str){ // != string
                pos = (primera + static_cast<int>(pow(++contador, 2))) % this->maxElementos;
            }
            return this->hash[pos]->prom; 
        }
};
