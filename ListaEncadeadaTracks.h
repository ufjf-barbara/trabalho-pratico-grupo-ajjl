#ifndef LISTAENCADEADATracks_H
#define LISTAENCADEADATracks_H
#include <string>
#include "NoT.h" ///no referente as tracks


class ListaEncadeadaTracks
{
public:
    ListaEncadeadaTracks();
    virtual ~ListaEncadeadaTracks();
    void NovaTrack( string id, string name,int popularity,int duration_ms,bool explicito,string artists,
                    string id_artists,string release_date,float danceability,float energy,float key,float loudness,    /// adiciona um novo no com as informacoes da track
                    float mode,float speechiness,float acousticness,float instrumentalness,float liveness,
                    float valence,float tempo,int time_signature);

    void ImprimeIds(); ///imprime todas as informacoes da lista
    void escrevebin();
    void Imprimebin(); /// imprime a pasta bin
private:
    int n;
    NoT *primeiro;
    NoT *ultimo;

};

#endif // LISTAENCADEADATRACKS_H
