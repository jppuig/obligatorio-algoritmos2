#include <iostream>
#include <cstring>
#include <fstream>  // IMPORTANTE! BORRAR

#include "./clases/hash.cpp"
#include "./funciones/potencia.cpp"
#include <cmath> //BORRAR

using namespace std;

//int potencia(int num, int pot);

int miHash(char* str) {
    // IMPORTANTE! BORRAR O COMENTAR LAS SIGUIENTES LINEAS  EN TODOS LOS EJERCICIOS DEL OBLIGATORIO. NO PUEDEN ESTAR EN NINGUNA ENTREGA!
    ifstream myFile("prueba1.in.txt");
    cin.rdbuf(myFile.rdbuf());
    // Si desean tirar la salida a un archivo, usen las siguientes líneas (si no, sáquenlas):
    ofstream myFile2("prueba1.out.txt");
    cout.rdbuf(myFile2.rdbuf());

    int largo = strlen(str);
    int suma = 0;

    for (int i=0; i<largo; i++) {
        suma += int(str[i]) * pow(37, i); //(potencia(37, i)); //Preguntar com hacerlo
    }

    return suma;
}

void mostrar(HashCerrado<int>* hash, char** str, int cant) {
    for (int i=0; i<cant; i++) {
        cout << str[i] << " " << hash->elemento(str[i]);
    }
}

int main() {
    int cant;
    cin >> cant;

    HashCerrado<int>* hash = new HashCerrado<int>(cant, miHash);
    char** nombres = new char*[cant];

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

        int promedio = suma / cantMaterias;
        hash->agregar(nombres[i], promedio);
    }

    mostrar(hash, nombres, cant);
    
    return 0;
}