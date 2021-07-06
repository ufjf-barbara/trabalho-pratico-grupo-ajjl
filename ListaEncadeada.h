#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include <string>
#include <vector>  
#include "NoA.h" /// No referente ao artista


class ListaEncadeada
{
public:
    ListaEncadeada();
    virtual ~ListaEncadeada();

    void NovoArtista(string id,float followers,string genres,string name,int popularity); //cria um novo no e armazena as informacoes do artista
    void imprimeIds(); 
    void escreveBin();
    void imprimeBin();
    void importaBin(int tam);
    void imprimeTestes(vector <Artista>);
    void NovaLista(string arq1);
    void deletaultimo()


private:
    int n;
    NoA *primeiro;
    NoA *ultimo;
    
};

#endif // LISTAENCADEADA_H
