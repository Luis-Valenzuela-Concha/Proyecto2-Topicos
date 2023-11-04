#ifndef COUNTMINCU_H
#define COUNTMINCU_H
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <sdsl/wm_int.hpp>
#include <sdsl/csa_wt.hpp>
#include <sdsl/wt_huff.hpp>

using namespace std;
using namespace sdsl;

// Definicion de la clase
class CountMinCU {
   private:
    int width;
    int depth;
    //vector<vector<unsigned int>> sketch;
    vector<unsigned int> sketch;

   public:
    CountMinCU(int w, int d);
    ~CountMinCU();
    void insert(unsigned int element);
    int estimarFreq(unsigned int element);
    wm_int<rrr_vector<15>> compress_wm_int();
    int estimarFreq_wm_int(wm_int<rrr_vector<15>> wm_int,unsigned int element);
    void printSketch();
    int size_in_bytes();
};
#endif