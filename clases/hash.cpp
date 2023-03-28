#include <iostream>
#include <cstring>
//#include "./funciones/potencia.cpp"
#include <cmath> //BORRAR

using namespace std;

//int potencia(int num, int pot);

template<class T>
class HashCerrado {
    private:
        T** hash;
        int largo;
        int maxElementos;
        int (*fHash)(char*);

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
        HashCerrado(int maxElementos, int (*fHash)(char*)){
            this->maxElementos = primoSup(maxElementos);
            this->largo = 0;
            this->hash = new T*[this->maxElementos];
            for (int i = 0; i < this->maxElementos; i++)
            {
                this->hash[i]=NULL;
            }
            
            this->fHash=fHash;
        }

        void agregar(char* str,T dato){
            int pos = this->fHash(str) % this->maxElementos;
            int contador = 0;
            while(this->hash[pos]){
                pos=(pos + pow(++contador, 2)) % this->maxElementos; //potencia(++contador, 2)
                // Se suma al original o se lleva la suma
            }
            this->hash[pos] = &dato;
        }

        T elemento(char* str) {
            int pos = this->fHash(str) % this->maxElementos;
            // Como se que llego al mio y no al de otro con cuadratica
            return this->hash[pos][0]; // A preguntar 
        }
};
