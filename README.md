# Proyecto 2 - Topicos

Se presentan los detalles y resultados de la implementación del sketch de estimación de
cardinalidad HyperLogLog junto con la compresión del mismo y del sketch de estimación de frecuencia
CountMin-CU mediante el uso de la biblioteca sdsl-lite. Se abordará el detalle de la implementación del
sketch HLL y también los resultados obtenidos antes y luego de la compresión.

## Tabla de Contenidos

- [Compilación y ejecución](#compilación-y-ejecución)
- [Integrantes](#integrantes)

## Compilación y ejecución:
```
g++ -std=c++11 -O3 -DNDEBUG -I ~/include -L ~/lib hashes/*.cpp CountMinCU.cpp  main.cpp HyperLogLog.cpp -o a.out -lsdsl -ldivsufsort -ldivsufsort64 && ./a.out
```
## Integrantes
Bruno Arce R. y Luis Valenzuela C.
