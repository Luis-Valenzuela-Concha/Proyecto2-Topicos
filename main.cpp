#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

using namespace std;

int main(){
    // Copia los valores en un arreglo
    FILE* archivo = fopen("Chicago-20080515.txt", "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }
    vector<unsigned int> file;
    unsigned int number;
    while (fscanf(archivo, "%u", &number) != EOF) {
        file.push_back(number);
    }
    fclose(archivo);
    // Fin de copia

    //Inicializacion
    HyperLogLog HLL(14);
    HyperLogLog HLL2(14);

    //insert
    //for(int i=0;i<file.size();i++) HLL.insert(file[i]);
    
    //Entrega valores distintos cada vez que se ejecuta
    HLL.insert("ACGT");
    HLL.insert("ACGT");
    HLL.insert("CGGTAC");
    HLL.insert("ATATATAT");
    HLL.insert("CGCCATTA");


    cout << "Cardinalidad: " << HLL.estimarCard() << endl;
    printf("Cardinalidad: %.2Lf\n",HLL.estimarCard());
    return 0;
}