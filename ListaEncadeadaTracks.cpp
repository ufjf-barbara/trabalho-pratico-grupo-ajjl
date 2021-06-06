#include "ListaEncadeadaTracks.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

ListaEncadeadaTracks::ListaEncadeadaTracks()
{
    cout << "criando o objeto"<< endl;
    n=0;
    primeiro=NULL;
    ultimo=NULL;
}

ListaEncadeadaTracks::~ListaEncadeadaTracks()
{
    cout << "apagando o objeto"<< endl;
    NoT *p=primeiro;
    while (p != NULL)
    {
        NoT *t = p->getProx();
        delete p;
        p=t;
    }
}
void ListaEncadeadaTracks::NovaTrack(string id, string name,int popularity,int duration_ms,bool explicito,string artists,
                                        string id_artists,string release_date,float danceability,float energy,float key,float loudness,
                                        float mode,float speechiness,float acousticness,float instrumentalness,float liveness,
                                        float valence,float tempo,int time_signature)
{
    if(n==0)
    {
        NoT* p=new NoT();
        primeiro=p;
        ultimo=p;
        p->setProx(NULL);

        p->setid(id);
        p->setname(name);
        p->setpopularity(popularity);
        p->setduration_ms(duration_ms);
        p->setexplicito(explicito);
        p->setartists(artists);
        p->setid_artists(id_artists);
        p->setrelease_date(release_date);
        p->setdanceability(danceability);
        p->setenergy(energy);
        p->setkey(key);
        p->setloudness(loudness);
        p->setmode(mode);
        p->setspeechiness(speechiness);
        p->setacousticness(acousticness);
        p->setinstrumentalness(instrumentalness);
        p->setliveness(liveness);
        p->setvalence(valence);
        p->settempo(tempo);
        p->settime_signature(time_signature);

        n++;
    }
    else
    {
        NoT* p=new NoT();
        ultimo->setProx(p);
        ultimo=p;
        p->setProx(NULL);

        p->setid(id);
        p->setname(name);
        p->setpopularity(popularity);
        p->setduration_ms(duration_ms);
        p->setexplicito(explicito);
        p->setartists(artists);
        p->setid_artists(id_artists);
        p->setrelease_date(release_date);
        p->setdanceability(danceability);
        p->setenergy(energy);
        p->setkey(key);
        p->setloudness(loudness);
        p->setmode(mode);
        p->setspeechiness(speechiness);
        p->setacousticness(acousticness);
        p->setinstrumentalness(instrumentalness);
        p->setliveness(liveness);
        p->setvalence(valence);
        p->settempo(tempo);
        p->settime_signature(time_signature);

        n++;
    }

}
void ListaEncadeadaTracks::ImprimeIds()
{
    NoT* p=primeiro;
    for (int i=0;i<n;i++)
    {
        cout << p->getid() << "," <<p->getname()<< "," << p->getpopularity()<< "," << p->getduration_ms()<< "," << p->getexplicito()<<",";
        cout << p->getartists() <<"," << p->getid_artists() <<"," << p->getrelease_date()<< "," <<p->getdanceability() << ","<< p->getenergy() << "," ;
        cout << p->getkey() << "," << p->getloudness() << "," << p->getmode() << "," << p->getspeechiness() << p->getacousticness()<< ",";
        cout << p->getinstrumentalness() << "," << p->getliveness() << "," << p->getvalence() << "," <<p->gettempo() <<"," << p->gettime_signature();
        cout << endl;
        p=p->getProx();
    }
}





