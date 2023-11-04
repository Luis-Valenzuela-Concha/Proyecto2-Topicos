#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sdsl/int_vector.hpp>

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
    vector<string> genoma1 = copiarArchivo("genomas/GCF_001522075.1_ASM152207v1_genomic.fna");
    vector<string> genoma2 = copiarArchivo("genomas/GCF_000717965.1_ASM71796v1_genomic.fna");
    
    //Inicializacion
    int p = 14;
    HyperLogLog HLL1(p);
    HyperLogLog HLL2(p);

    //Inserta kmer
    insertarKMER(&HLL1,genoma1,10);
    insertarKMER(&HLL2,genoma2,10);

    //Calculo cardinalidad
    printf("Cardinalidad HLL1: %.2Lf\n",HLL1.estimarCard());
    printf("Cardinalidad HLL2: %.2Lf\n",HLL2.estimarCard());

    //Union de HLL1 y HLL2
    printf("\nUnion HLL1 y HLL2\n");
    HLL1.Union(HLL2);
    printf("Cardinalidad HLL1: %.2Lf\n",HLL1.estimarCard());

    //HLL1.print();
    //Compresion
    wt_huff<rrr_vector<15>> comprimido = HLL1.compress_wt_huff();
    wm_int<rrr_vector<15>> comprimido2 = HLL1.compress_wm_int();
    int m = pow(2, p); 
    cout << endl << endl;
    
    for(int i = 0; i < m+10; i++){
        printf("%lu ",comprimido2[i]);
    }
    
    return 0;
}