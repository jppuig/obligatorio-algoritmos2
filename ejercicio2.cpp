#include <iostream>
#include <cstring>
#include "clases/avl.cpp"
#include <fstream>  // IMPORTANTE! BORRAR

using namespace std;

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio2/162793.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cant;
    cin >> cant;

    AVL* avl = new AVL();

    // ERROR EN LAS ULTIMAS DOS PRUEBAS

    for (int i=0;i<cant;i++) {
        string palabra;
        cin >> palabra;
        avl->insertar(palabra);
    }

    avl->mostrar();

    avl->~AVL();
    
    return 0;
}