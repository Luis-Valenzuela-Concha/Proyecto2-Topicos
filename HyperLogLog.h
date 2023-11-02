#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <vector>
#include <string>

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
        void print();
};

#endif