#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>

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
    HyperLogLog HLL;
    HyperLogLog HLL2;

    //insert
    for(int i=0;i<file.size();i++) HLL.insert(file[i]);
    cout << "Cardinalidad: " << HLL.estimarCard() << endl;
    printf("Cardinalidad: %.2Lf\n",HLL.estimarCard());
    return 0;
}