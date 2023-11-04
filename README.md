# Proyecto2-Topicos
## Compilacion y ejecucion
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib hashes/*.cpp CountMinCU.cpp  HyperLogLog.cpp main.cpp -o a.out -lsdsl -ldivsufsort -ldivsufsort64 && ./a.out
