#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include "hashes/MurmurHash3.h"
#include <sdsl/wm_int.hpp>
#include <sdsl/csa_wt.hpp>
#include <sdsl/wt_huff.hpp>

using namespace sdsl;

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

double HyperLogLog::cardinalidad() {
    double E;

    double a_m = 0.7213 / (1 + 1.079 / m);
    double num = a_m * m * m;
    double den = 0;

    for (int i = 0; i < m; i++) {
        den += 1 / (pow(2, M[i]));
    }
    E = num / den;
    return E;
    // Agregar correcciones
    double E_asterisco;

    if (E <= 5 / 2 * m) {
        int V = 0;
        for (int i = 0; i < m; i++) {
            if (M[i] == 0) V++;
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

wm_int<rrr_vector<15>> HyperLogLog::compress_wm_int() {
    wm_int<rrr_vector<15>> wm_int;
    construct_im(wm_int, M, 1);
    return wm_int;
}

wt_huff<rrr_vector<15>> HyperLogLog::compress_wt_huff() {
    wt_huff<rrr_vector<15>> wt_huff;
    construct_im(wt_huff, M, 1);
    return wt_huff;
}

double HyperLogLog::cardinalidad_wm_int(wm_int<rrr_vector<15>> wm_int){

    double E;

    double a_m = 0.7213 / (1 + 1.079 / m);
    double num = a_m * m * m;
    double den = 0;
    int error = 8;
    for (int i = error; i < m+error; i++) {
        den += 1 / (pow(2, wm_int[i]));
    }
    E = num / den;
    return E;
    // Agregar correcciones
    double E_asterisco;

    if (E <= 5 / 2 * m) {
        int V = 0;
        for (int i = error; i < m+error; i++) {
            if (wm_int[i] == 0) V++;
        }
        if (V != 0) E_asterisco = m * log(m / V);
        else E_asterisco = E;
    }

    if (E <= 1 / 30 * pow(2, 32)) {
        E_asterisco = E;
    }

    if (E > 1 / 30 * pow(2, 32)) {
        E_asterisco = -1 * pow(2, 32) * log(1 - E / pow(2, 32));
    }
    return E_asterisco;
}

double HyperLogLog::cardinalidad_wt_huff(wt_huff<rrr_vector<15>> wt_huff){
    double E;

    double a_m = 0.7213 / (1 + 1.079 / m);
    double num = a_m * m * m;
    double den = 0;
    int error = 8;
    for (int i = error; i < m+error; i++) {
        den += 1 / (pow(2, wt_huff[i]));
    }
    E = num / den;
    return E;
    // Agregar correcciones
    double E_asterisco;

    if (E <= 5 / 2 * m) {
        int V = 0;
        for (int i = error; i < m+error; i++) {
            if (wt_huff[i] == 0) V++;
        }
        if (V != 0) E_asterisco = m * log(m / V);
        else E_asterisco = E;
    }

    if (E <= 1 / 30 * pow(2, 32)) {
        E_asterisco = E;
    }

    if (E > 1 / 30 * pow(2, 32)) {
        E_asterisco = -1 * pow(2, 32) * log(1 - E / pow(2, 32));
    }
    return E_asterisco;
}

void HyperLogLog::union_wm_int(wm_int<rrr_vector<15>> wm_int1,wm_int<rrr_vector<15>> wm_int2){
    if (wm_int1.size() != wm_int2.size()) {
        cout << "Deben ser de mismo tamaño" << endl;
        return;
    }
    int error = 8;
    for (int i = error; i < this->m + error; i++) {
        this->M[i-error] = max(wm_int1[i], wm_int2[i]);
    }
}

void HyperLogLog::union_wt_huff(wt_huff<rrr_vector<15>> wt_huff1,wt_huff<rrr_vector<15>> wt_huff2){
    if (wt_huff1.size() != wt_huff2.size()) {
        cout << "Deben ser de mismo tamaño" << endl;
        return;
    }
    int error = 8;
    for (int i = error; i < this->m + error; i++) {
        this->M[i-error] = max(wt_huff1[i], wt_huff2[i]);
    }
}

int HyperLogLog::size_in_bytes() {
    return M.size() * sizeof(uint8_t);
}

void HyperLogLog::print() {
    for (int i = 0; i < m; i++) {
        printf("%d ", M[i]);
    }
}