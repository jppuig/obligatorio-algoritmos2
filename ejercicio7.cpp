#include <iostream>
#include "./clases/nodoDP.cpp"

#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int max(int a, int b) {
    if (a < b) {
        return b;
    } else {
        return a;
    }
}

int entregaDP(NodoDP** &archivos, int cantArchivos, int cantMaxMB, int cantMaxCodigo) {
    int*** mat3d = new int**[cantArchivos];
    
    for (int i=0;i<cantArchivos; i++) {
        mat3d[i] = new int*[cantMaxMB+1];
    
        for (int j=0; j<=cantMaxMB; j++) {
            mat3d[i][j] = new int[cantMaxCodigo+1];
        }
    }

    for (int j=0; j<=cantMaxMB; j++) {
        for (int k=0; k<=cantMaxCodigo; k++) {
            bool entraTam = (j / archivos[0]->tamano) > 0;
            bool entraLin = (k / archivos[0]->lineas) > 0;

            mat3d[0][j][k] = entraTam && entraLin ? archivos[0]->puntaje : 0;
        }
    }

    for (int i=1;i<cantArchivos; i++) {
        for (int j=0; j<=cantMaxMB; j++) {
            for (int k=0; k<=cantMaxCodigo; k++) {
                bool entraTam = j >= archivos[i]->tamano;
                bool entraLin = k >= archivos[i]->lineas;

                int arriba = mat3d[i-1][j][k];

                mat3d[i][j][k] = entraTam && entraLin ?
                    max(arriba, archivos[i]->puntaje + mat3d[i-1][j-archivos[i]->tamano][k-archivos[i]->lineas]) : arriba;
                                // es i-1 pq es si comparo en i uso mas de una vez el elemento
            }
        }
    }

    int res = mat3d[cantArchivos-1][cantMaxMB][cantMaxCodigo];

    for (int i=0;i<cantArchivos; i++) {
        for (int j=0; j<=cantMaxMB; j++) {
                delete[] mat3d[i][j];
        }
        delete[] mat3d[i];
    }
    delete[] mat3d;

    return res;
}

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio7/10000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cantArchivos;
    int cantMaxMB;
    int cantMaxCodigo;

    cin >> cantArchivos;
    cin >> cantMaxMB;
    cin >> cantMaxCodigo;

    NodoDP** archivos = new NodoDP*[cantArchivos];

    for (int i=0; i<cantArchivos; i++) {
        int tamano, lineas, puntaje;
        
        cin >> tamano;
        cin >> lineas;
        cin >> puntaje;

        archivos[i] = new NodoDP(tamano, lineas, puntaje);
    }

    int puntaje = entregaDP(archivos, cantArchivos, cantMaxMB, cantMaxCodigo);

    cout << puntaje << endl;

    delete[] archivos;

    return 0;
}