#ifndef COUNTMINCU_H
#define COUNTMINCU_H
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

// Definicion de la clase
class CountMinCU {
   private:
    int width;
    int depth;
    vector<vector<unsigned int>> sketch;

   public:
    CountMinCU(int w, int d);
    ~CountMinCU();
    void insert(unsigned int element);
    int estimarFreq(unsigned int element);
    void printSketch();
};
#endif