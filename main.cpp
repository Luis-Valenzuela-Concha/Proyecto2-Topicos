#include "HyperLogLog.h"
#include "CountMinCU.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sdsl/int_vector.hpp>

using namespace std;
vector<unsigned int> copiarArchivoUINT(string nombreArchivo){
    const char* aux = nombreArchivo.data();
    FILE* archivo = fopen(aux, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    vector<unsigned int> file;
    unsigned int number;
    while (fscanf(archivo, "%u", &number) != EOF) {
        file.push_back(number);
    }
    fclose(archivo);
    return file;
}

vector<string> copiarArchivoString(string nombreArchivo){
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
    printf("Proyecto 2 - Topicos en Manejo de Grandes Volumenes de Datos\n");
    printf("Integrantes:\n");
    printf(" - Bruno Arce R.\n");
    printf(" - Luis Valenzuela C.\n\n");

    printf("Pregunta a)\n");
    //Se extraen los genomas
    vector<string> genoma1 = copiarArchivoString("datasets/GCF_001522075.1_ASM152207v1_genomic.fna");
    vector<string> genoma2 = copiarArchivoString("datasets/GCF_000717965.1_ASM71796v1_genomic.fna");

    //Inicializacion
    int p = 14;
    printf("Se inicializa sketch HLL1 y HLL2 con p = %d.\n",p);
    HyperLogLog HLL1(p);
    HyperLogLog HLL2(p);

    //Inserta kmer
    printf("Insertando k-mers en los sketches...\n");
    insertarKMER(&HLL1,genoma1,10);
    insertarKMER(&HLL2,genoma2,10);
    printf("Insertado finalizado.\n\n");

    //Estimacion de cardinalidad
    printf("Estimacion de cardinalidad:\n");
    printf("HLL1: %.2f\n",HLL1.cardinalidad());
    printf("HLL2: %.2f\n\n",HLL2.cardinalidad());

    //Copia HLL1 antes de union
    HyperLogLog HLL3 = HLL1;
    HyperLogLog HLL4 = HLL1;
    HyperLogLog HLL5 = HLL1;
    HyperLogLog HLL6 = HLL1;
    HyperLogLog HLL7 = HLL1;

    //Union
    printf("Union de HLL1 y HLL2:\n");
    HLL1.Union(HLL2); 
    printf("Cardinalidad union: %.2f\n\n",HLL1.cardinalidad());

    printf("Pregunta b)\n");
    //Comprimir sketches
    printf("Comprimiendo sketches...\n");
    wm_int<rrr_vector<15>> HLL3_compressed_wm_int = HLL3.compress_wm_int();
    wt_huff<rrr_vector<15>> HLL3_compressed_wt_huff = HLL3.compress_wt_huff();
    wm_int<rrr_vector<15>> HLL2_compressed_wm_int = HLL2.compress_wm_int();
    wt_huff<rrr_vector<15>> HLL2_compressed_wt_huff = HLL2.compress_wt_huff();
    printf("Compresion finalizada.\n\n");

    //Estimacion de cardinalidad
    printf("Estimacion de cardinalidad de sketches comprimidos:\n");
    printf("HLL1_wm_int:  %.2f\n",HLL3.cardinalidad_wm_int(HLL3_compressed_wm_int));
    printf("HLL1_wt_huff: %.2f\n",HLL3.cardinalidad_wt_huff(HLL3_compressed_wt_huff));
    printf("HLL2_wm_int:  %.2f\n",HLL2.cardinalidad_wm_int(HLL2_compressed_wm_int));
    printf("HLL2_wt_huff: %.2f\n\n",HLL2.cardinalidad_wt_huff(HLL2_compressed_wt_huff));
    
    printf("Uniendo sketches comprimidos...\n");
    HLL3.union_wm_int(HLL3_compressed_wm_int,HLL2_compressed_wm_int);
    HLL4.union_wt_huff(HLL4.compress_wt_huff(),HLL2_compressed_wt_huff);
    printf("Union finalizada.\n\n");

    printf("Cardinalidad union:\n");
    printf("Sin compresion: %.2f\n",HLL1.cardinalidad());
    printf("Union wm_int:   %.2f\n",HLL3.cardinalidad());
    printf("Union wt_huff:  %.2f\n\n",HLL4.cardinalidad());

    printf("Pregunta c)\n");
    //Se extrae traza
    vector<unsigned int> traza = copiarArchivoUINT("datasets/Chicago-20080515.txt");

    //Inicializacion
    printf("Se inicializa sketch CountMinCU con w = 5000 y d = 4.\n");
    CountMinCU sketchCU(50000, 4);
    //Inserta traza
    unordered_map<unsigned int,int> freq;
    printf("Insertando elementos en el sketch...\n");
    for(int i = 0; i < traza.size(); i++){
        unsigned int number = traza[i];
        sketchCU.insert(number);
        if(freq.find(number) == freq.end()) freq[number] = 1;
        else freq[number]++;
    }
    printf("Insertado finalizado.\n\n");
    
    printf("Se comprime el sketch...\n");
    wm_int<rrr_vector<15>> sketchCU_compressed_wm_int = sketchCU.compress_wm_int();
    wt_huff<rrr_vector<15>> sketchCU_compressed_wt_huff = sketchCU.compress_wt_huff();
    printf("Compresion finalizada.\n\n");

    printf("Se estima la frecuencia de traza[0]=%d\n",traza[0]);
    printf("Real: %d\n",freq[traza[0]]);
    printf("Estimada: %d\n",sketchCU.estimarFreq(traza[0]));
    printf("Estimada con compresion wm_int: %d\n\n",sketchCU.estimarFreq_wm_int(sketchCU_compressed_wm_int,traza[0]));
    //No entrega el valor correcto
    //printf("Estimada con compresion wt_huff: %d\n\n",sketchCU.estimarFreq_wt_huff(sketchCU_compressed_wt_huff,traza[0]));

    printf("Pregunta d)\n");
    printf("Razon de compresion:\n");
    printf("HLL1 wm_int:  %.2f\n",(float)size_in_bytes(HLL5.compress_wm_int())/HLL5.size_in_bytes());
    printf("HLL1 wt_huff: %.2f\n",(float)size_in_bytes(HLL5.compress_wt_huff())/HLL5.size_in_bytes());
    printf("HLL2 wm_int:  %.2f\n",(float)size_in_bytes(HLL2_compressed_wm_int)/HLL2.size_in_bytes());
    printf("HLL2 wt_huff: %.2f\n",(float)size_in_bytes(HLL2_compressed_wm_int)/HLL2.size_in_bytes());
    printf("CCU  wm_int:  %.2f\n\n",(float)size_in_bytes(sketchCU_compressed_wt_huff)/sketchCU.size_in_bytes());

    printf("Analisis de tiempo:\n");
    printf("Union HLL1 y HLL2:\n");
    auto start = chrono::high_resolution_clock::now();
    HLL5.Union(HLL2);
    auto finish = chrono::high_resolution_clock::now();
    auto d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    printf("Sin compresion: %ld [ns]\n",d);

    start = chrono::high_resolution_clock::now();
    HLL6.union_wm_int(HLL6.compress_wm_int(),HLL2_compressed_wm_int);
    finish = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    printf("Union wm_int:   %ld [ns]\n",d);

    start = chrono::high_resolution_clock::now();
    HLL7.union_wt_huff(HLL6.compress_wt_huff(),HLL2_compressed_wt_huff);
    finish = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    printf("Union wt_huff:  %ld [ns]\n\n",d);

    printf("Estimacion de frecuencia:\n");
    start = chrono::high_resolution_clock::now();
    sketchCU.estimarFreq(traza[0]);
    finish = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    printf("Sin compresion: %ld [ns]\n",d);

    start = chrono::high_resolution_clock::now();
    sketchCU.estimarFreq_wm_int(sketchCU_compressed_wm_int,traza[0]);
    finish = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    printf("Estimacion wm_int: %ld [ns]\n",d);
    return 0;
}