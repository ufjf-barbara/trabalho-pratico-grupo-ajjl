#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector> 
#include <string> 
#include "NoA.h" /// No referente ao artista


class ListaEncadeada
{
public:
    ListaEncadeada();
    virtual ~ListaEncadeada();

    void NovoArtista(string id,float followers,string genres,string name,int popularity); //cria um novo no e armazena as informacoes do artista
    void imprimeIds(); 
    void escreveBin(string arq3);
    void imprimeBin();
    void importaBin(int tam);
    void imprimeTestes(vector <Artista>);
    void NovaLista(string arq1);
    void deletaultimo();
    vector<Artista> getAll(string arq2);
    vector<Artista> getAleatorios(int tam, string arq2);

private:
    int n;
    NoA *primeiro;
    NoA *ultimo;
    
};

#endif // LISTAENCADEADA_H
