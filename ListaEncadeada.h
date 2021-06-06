#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include <string>
#include<NoA.h> /// No referente ao artista


class ListaEncadeada
{
public:
    ListaEncadeada();
    virtual ~ListaEncadeada();

    void NovoArtista(string id,float followers,string genres,string name,int popularity); //cria um novo nó e armazena as informações do artista
    void ImprimeIds();  ///imprime todas as informações da lista

private:
    int n;
    NoA *primeiro;
    NoA *ultimo;

};

#endif // LISTAENCADEADA_H
