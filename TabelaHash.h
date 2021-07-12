#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include "NoHash.h"


typedef std::string string;
class TabelaHash
{
public:
    TabelaHash(int tam);
    int getTam() { return tam; }
    void insere(NoHash* n);
    void print();

private:
    int tam;
    int funct(string,int);
    NoHash **tabela;
};



#endif // HASH_H_INCLUDED