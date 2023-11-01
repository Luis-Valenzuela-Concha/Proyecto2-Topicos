#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(){
    // Copia los valores en un arreglo
    ifstream archivo("GCF_001522075.1_ASM152207v1_genomic.fna");
    vector<string> vec;
    string linea;
    while (getline(archivo, linea)) {
        if(linea[0] == '>') continue;
        vec.push_back(linea);
    }
    archivo.close();
    //Fin copia

    //Inicializacion
    HyperLogLog HLL(14);
    HyperLogLog HLL2(14);

    //Inserta kmer
    int k = 10;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].size() < k) continue; //Si el kmer es mas grande que el string continua
        for(int j = 0; j < vec[i].size()-k+1; j++){
            string kmer = vec[i].substr(j,k);
            HLL.insert(kmer);
            HLL2.insert(kmer);
        }
    }
    printf("Cardinalidad HLL : %.2Lf\n",HLL.estimarCard());
    printf("Cardinalidad HLL2: %.2Lf\n",HLL2.estimarCard());
    HLL.Union(HLL2);
    printf("Cardinalidad HLL : %.2Lf\n",HLL.estimarCard());
    return 0;
}