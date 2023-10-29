#include "HyperLogLog.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int main(){
    HyperLogLog HLL;
    HyperLogLog HLL2;
    HLL.print();
    HLL.Union(HLL2);
    return 0;
}