#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <vector>
#include <string>
#include <sdsl/wm_int.hpp>
#include <sdsl/csa_wt.hpp>
#include <sdsl/wt_huff.hpp>

using namespace std;

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
          uint32_t compress_wm_int();
          uint32_t compress_wt_huff();
          void print();
};

#endif