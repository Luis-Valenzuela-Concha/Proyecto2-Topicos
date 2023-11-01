#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

vector<string> copiarArchivo(string nombreArchivo){
    ifstream archivo(nombreArchivo);
    vector<string> vec;
    string linea;
    while (getline(archivo, linea)) {
        if(linea[0] == '>') continue;
        vec.push_back(linea);
    }
    archivo.close();
    return vec;
}

void insertarKMER(HyperLogLog *h, vector<string> v,int k){
    for(int i = 0; i < v.size(); i++){
        if(v[i].size() < k) continue; //Si el k es mas grande que el string continua
        for(int j = 0; j < v[i].size()-k+1; j++){
            string kmer = v[i].substr(j,k);
            h->insert(kmer);
        }
    }
}

int main(){
    vector<string> genoma1 = copiarArchivo("GCF_001522075.1_ASM152207v1_genomic.fna");
    vector<string> genoma2 = copiarArchivo("GCF_000717965.1_ASM71796v1_genomic.fna");
    
    //Inicializacion
    HyperLogLog HLL(14);
    HyperLogLog HLL2(14);

    //Inserta kmer
    insertarKMER(&HLL,genoma1,10);
    insertarKMER(&HLL2,genoma2,11);

    printf("Cardinalidad HLL : %.2Lf\n",HLL.estimarCard());
    printf("Cardinalidad HLL2: %.2Lf\n",HLL2.estimarCard());

    HLL.Union(HLL2);
    printf("Cardinalidad HLL : %.2Lf\n",HLL.estimarCard());
    return 0;
}