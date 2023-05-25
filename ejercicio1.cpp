#include <iostream>
#include <cstring>
#include <fstream>  // IMPORTANTE! BORRAR

#include "./clases/hash.cpp"
#include <cmath>

using namespace std;

int miHash(string str) {
    int largo = str.length();
    unsigned long long suma = 0;

    for (int i=0; i<largo; i++) {
        suma += int(str[i]) * static_cast<int>(pow(37, i));
    }

    return suma;
}

void mostrar(HashCerrado* hash, string* str, int cant) {
    for (int i=0; i<cant; i++) {
        cout << str[i] << " " << hash->elemento(str[i]) << endl;
    }
}

int main() {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("pruebas/Ejercicio1/1000000.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int cant;
    cin >> cant;

    HashCerrado* hash = new HashCerrado(cant, miHash);
    string* nombres = new string[cant];

    for (int i=0; i<cant; i++) {
        int cantMaterias;
        int suma = 0;
        
        cin >> nombres[i];
        cin >> cantMaterias;

        for (int j = 0; j<cantMaterias; j++) {
            int num;
            cin >> num;
            suma += num;
        }

        double promedio = round(suma / cantMaterias);
        hash->agregar(nombres[i], promedio);
    }

    mostrar(hash, nombres, cant);

    delete hash;
    
    return 0;
}