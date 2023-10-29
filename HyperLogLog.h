#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H
#include <vector>

using namespace std;

class HyperLogLog {
   private:
    int p = 14;
    int m;
    vector<unsigned int> M;

   public:
    HyperLogLog();
    ~HyperLogLog();
    pair<unsigned int, unsigned int> values(unsigned int element);
    void insert(unsigned int element);
    unsigned int estimarCard();
    void Union(HyperLogLog h);
    void print();
};

#endif