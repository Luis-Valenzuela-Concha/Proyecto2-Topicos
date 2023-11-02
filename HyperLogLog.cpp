#include "HyperLogLog.h"

#include <bits/stdc++.h>

#include <iostream>
#include <unordered_map>

#include "MurmurHash3.h"

int seed = 1;

HyperLogLog::HyperLogLog(int p) {
    this->p = p;
    m = pow(2, p);  // Tamaño de vector M
    M = vector<uint8_t>(m, 0);
}

HyperLogLog::~HyperLogLog() { ; }

// Trasforma elemento en j y w
pair<unsigned int, uint8_t> HyperLogLog::values(string element) {
    uint32_t x;
    MurmurHash3_x86_32(element.c_str(), element.size(), seed, &x);
    unsigned int j = x >> 32 - p;
    unsigned int b = x << p;

    uint8_t w = 1;
    unsigned int aux = 1 << 31;
    while ((b & aux) == 0 && aux != 0) {
        aux = aux >> 1;
        w++;
    }
    pair<unsigned int, uint8_t> values;
    values.first = j;   // posicion
    values.second = w;  // valor

    return values;
}

void HyperLogLog::insert(string element) {
    pair<unsigned int, uint8_t> valores = values(element);
    unsigned int j = valores.first;   // posicion
    uint8_t w = valores.second;  // valor
    M[j] = max(M[j], w);
}

long double HyperLogLog::estimarCard() {
    long double E;

    long double a_m = 0.7213 / (1 + 1.079 / m);
    long double num = a_m * m * m;
    long double den = 0;

    for (int i = 0; i < m; i++) {
        den += 1 / (pow(2, M[0]));
    }
    E = num / den;
    // Agregar correcciones
    long double E_asterisco;

    if (E <= 5 / 2 * m) {
        int V = 0;
        for (int i = 0; i < m; i++) {
            if (M[i] == 0) {
                V++;
            }
        }
        if (V != 0) {
            E_asterisco = m * log(m / V);
        } else {
            E_asterisco = E;
        }
    }

    if (E <= 1 / 30 * pow(2, 32)) {
        E_asterisco = E;
    }

    if (E > 1 / 30 * pow(2, 32)) {
        E_asterisco = -1 * pow(2, 32) * log(1 - E / pow(2, 32));
    }
    return E_asterisco;
}

void HyperLogLog::Union(HyperLogLog h) {  // Se une con otro sketch
    if (this->m != h.m) {
        cout << "Deben ser de mismo tamaño << endl";
        return;
    }
    for (int i = 0; i < this->m; i++) {
        this->M[i] = max(this->M[i], h.M[i]);
    }
}

void HyperLogLog::print() {
    for (int i = 0; i < m; i++) {
        cout << M[i] << " ";
    }
}