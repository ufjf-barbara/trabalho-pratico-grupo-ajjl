#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "NoHash.h"
#include "ListaEncadeadaTracks.h"


typedef std::string string;
class TabelaHash
{
public:
    TabelaHash(int tam);
    int getTam() { return tam; }
    void insere(NoHash* n);
    void print();
    void insereArtists(int tam, string arq4);
    vector<Tracks> tracksAleatorias(int tam, string arq4);
    bool verificaArtista (vector<Tracks> vetor, Tracks aux);

private:
    int tam;
    int funct(string,int);
    NoHash **tabela;
};



#endif // HASH_H_INCLUDED