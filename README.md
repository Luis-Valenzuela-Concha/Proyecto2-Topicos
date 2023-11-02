# Proyecto2-Topicos
Compilacion y ejecucion
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib main.cpp HyperLogLog.cpp MurmurHash3.cpp -o a.out -lsdsl -ldivsufsort -ldivsufsort64 && ./a.out
