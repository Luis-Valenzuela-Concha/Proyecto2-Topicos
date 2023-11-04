#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <vector>
#include <string>
#include <sdsl/wm_int.hpp>
#include <sdsl/csa_wt.hpp>
#include <sdsl/wt_huff.hpp>

using namespace std;
using namespace sdsl;

class HyperLogLog {
   private:
          int p;
          int m;
          vector<uint8_t> M;

   public:
          HyperLogLog(int p);
          ~HyperLogLog();
          pair<unsigned int, uint8_t> values(string element);
          void insert(string element);
          long double estimarCard();
          void Union(HyperLogLog h);
          size_t sizeInBits();
          wm_int<rrr_vector<15>> compress_wm_int();
          wt_huff<rrr_vector<15>> compress_wt_huff();
          void print();
};

#endif