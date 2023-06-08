#include <iostream>
#define INF 9999
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

bool esSolucion(int fila, int col, int& filaB, int& colB, bool& pasoBede, int& filaD, int& colD) {
    if (fila == filaB && col == colB) {
        pasoBede = true;
    }

    if (fila == filaD && col == colD && pasoBede) {
        return true;
    } else {
        return false;
    }
}

bool esAceptable(char**& matriz, int& n, int& m, int fila, int col, int solActual, int& solOptima) {
    if (fila >= 0 && fila <= m && col >=0 && col <= n && matriz[fila][col] != 'P' && solActual < solOptima) {
        return true;
    } else {
        return false;
    }

}

void backtracking(int& n, int& m, char**& matriz, int fila, int col, int& filaB, int& colB, bool pasoBede, int& filaD, int& colD, int solActual, int& solOptima) {
    if (esSolucion(fila, col, filaB, colB, pasoBede, filaD, colD)) {
        if (solActual < solOptima) {
            solOptima = solActual;
        }
    } else {
        if (esAceptable(matriz, n, m, fila-1, col, solActual+1, solOptima)) {
            //Arriba
            backtracking(n, m, matriz, fila-1, col, filaB, colB, pasoBede, filaD, colD, solActual+1, solOptima);
        }
        if (esAceptable(matriz, n, m, fila, col+1, solActual+1, solOptima)) {
            //Derecha
            backtracking(n, m, matriz, fila, col+1, filaB, colB, pasoBede, filaD, colD, solActual+1, solOptima);
        }
        if (esAceptable(matriz, n, m, fila+1, col, solActual+1, solOptima)) {
            // Abajo
            backtracking(n, m, matriz, fila+1, col, filaB, colB, pasoBede, filaD, colD, solActual+1, solOptima);
        }
        if (esAceptable(matriz, n, m, fila, col-1, solActual+1, solOptima)) {
            //Izquierda
            backtracking(n, m, matriz, fila, col-1, filaB, colB, pasoBede, filaD, colD, solActual+1, solOptima);
        }
    }
}

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio10/facu10e1.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int m, n;
    cin >> m;
    cin >> n;

    char** matriz = new char*[m];
    int bedeliasFila;
    int bedeliasCol;

    for (int i=0; i<m; i++) {
        matriz[i] = new char[n];
        for (int j=0; j<n; j++) {
            char letra;
            cin >> letra;
            
            if (matriz[i][j] == 'B') {
                bedeliasFila = i;
                bedeliasCol = j;
            }

            matriz[i][j] = letra;
        }
    }

    int casos;
    cin >> casos;

    for (int i=0; i<casos; i++) {
        int origenFila, origenCol, destinoFila, destinoCol, solActual, solOptima;
        cin >> origenCol;
        cin >> origenFila;
        cin >> destinoCol;
        cin >> destinoFila;

        solOptima = INF;
        solActual = 0;

        backtracking(n, m, matriz, origenFila, origenCol, bedeliasFila, bedeliasCol, false, destinoFila, destinoCol, solActual, solOptima);

        if (solOptima == INF) {
            cout << 0 << endl;
        } else {
            cout << solOptima << endl;
        }
    }

    for (int i=0; i<m; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}