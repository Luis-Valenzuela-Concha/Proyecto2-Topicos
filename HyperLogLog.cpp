#include "HyperLogLog.h"

#include <bits/stdc++.h>

#include <iostream>
#include <unordered_map>

HyperLogLog::HyperLogLog() {
    m = pow(2, p) - 1;
    M = vector<unsigned int>(m, 0);
}

HyperLogLog::~HyperLogLog() { ; }

pair<unsigned int, unsigned int> HyperLogLog::values(unsigned int element) {
    uint32_t x;
    uint32_t hash;
    MurmurHash3_x86_32(&element, sizeof(unsigned int), seedCU, &hash);  // CAMBIAR SEED
    x = hash % m;

    unsigned int j = x >> 32 - p;
    unsigned int b = x << p;

    int w = 1;
    int aux = 1 << 31;
    while ((b & aux) == 0 && aux != 0) {
        aux = aux >> 1;
        w++;
    }
    pair<unsigned int, unsigned int> values;
    values.first = j;
    values.second = w;

    return values;
}

void HyperLogLog::insert() { ; }  // FALTA HACER EL INSERTAR

unsigned int HyperLogLog::estimarFreq(unsigned int element) {
    pair<unsigned int, unsigned int> valores = values(element);
    unsigned int j = valores.first;
    unsigned int w = valores.second;

    unsigned int E;

    float a_m = 0.7213 / (1 + 1.079 / m);
    float num = a_m * m * m;
    float den = 0;
    for (int i = 0; i < m; i++) {
        den += pow(2, -M[i]);
    }
    E = (unsigned int)(num / den);

    return E;
}

void HyperLogLog::Union(HyperLogLog *h1, HyperLogLog h2) {
    for (int i = 0; i < m; i++) {
        h1->M[i] = max(h1->M[i], h2.M[i]);
    }
    // PREGUNTAR SI SE DEBE HACER UN DELETE DE H2
}