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
    vector<string> genoma1 = copiarArchivo("datasets/GCF_001522075.1_ASM152207v1_genomic.fna");
    vector<string> genoma2 = copiarArchivo("datasets/GCF_000717965.1_ASM71796v1_genomic.fna");
    
    //Inicializacion
    int p = 14;
    HyperLogLog HLL1(p);
    HyperLogLog HLL2(p);

    //Inserta kmer
    insertarKMER(&HLL1,genoma1,10);
    insertarKMER(&HLL2,genoma2,10);

    //Comprimir sketches
    wm_int<rrr_vector<15>> HLL1_compressed_wm_int = HLL1.compress_wm_int();
    wt_huff<rrr_vector<15>> HLL1_compressed_wt_huff = HLL1.compress_wt_huff();
    wm_int<rrr_vector<15>> HLL2_compressed_wm_int = HLL2.compress_wm_int();
    wt_huff<rrr_vector<15>> HLL2_compressed_wt_huff = HLL2.compress_wt_huff();

    //Calculo cardinalidad
    printf("\nCardinalidad:\n");
    printf("HLL1: %.2f\n",HLL1.cardinalidad());
    printf("HLL2: %.2f\n",HLL2.cardinalidad());
    printf("\nCardinalidad comprimida:\n");
    printf("HLL1_wm_int: %.2f\n",HLL1.cardinalidad_wm_int(HLL1_compressed_wm_int));
    printf("HLL1_wt_huff: %.2f\n",HLL1.cardinalidad_wt_huff(HLL1_compressed_wt_huff));
    printf("HLL2_wm_int: %.2f\n",HLL2.cardinalidad_wm_int(HLL2_compressed_wm_int));
    printf("HLL2_wt_huff: %.2f\n",HLL2.cardinalidad_wt_huff(HLL2_compressed_wt_huff));
    
    //Union de HLL1 y HLL2
    printf("\nUnion HLL1 y HLL2\n");
    HLL1.Union(HLL2); 
    printf("HLL1: %.2f\n",HLL1.cardinalidad());
    HLL1.union_wm_int(HLL1_compressed_wm_int,HLL2_compressed_wm_int);
    HLL1.union_wt_huff(HLL1_compressed_wt_huff,HLL2_compressed_wt_huff);
    printf("HLL1: %.2f\n",HLL1.cardinalidad());


    //Calculo de tiempo
    /*auto start = chrono::high_resolution_clock::now();  
    auto finish = chrono::high_resolution_clock::now();
    auto d = chrono::duration_cast<chrono::nanoseconds> (finish1 - start1).count();
    printf("Tiempo de union: %ld\n",d);*/
    return 0;
}