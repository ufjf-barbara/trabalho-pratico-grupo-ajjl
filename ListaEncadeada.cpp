#include "ListaEncadeada.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>


using namespace std;

ListaEncadeada::ListaEncadeada()
{
    cout << "criando o objeto"<< endl;
    n=0;
    primeiro=NULL;
    ultimo=NULL;
}

ListaEncadeada::~ListaEncadeada()
{
    cout << "apagando o objeto"<< endl;
    NoA *p=primeiro;
    while (p != NULL)
    {
        NoA *t = p->getProx();
        delete p;
        p=t;
    }
}

void ListaEncadeada::NovoArtista(string id,float followers,string genres,string name,int popularity)
{
    if(n==0)
    {
        NoA* p=new NoA();
        primeiro=p;
        ultimo=p;
        p->setProx(NULL);

        p->setid(id);
        p->setfollowers(followers);
        p->setgenres(genres);
        p->setname(name);
        p->setpopularity(popularity);

        n++;
    }
    else
    {
        NoA* p=new NoA();
        ultimo->setProx(p);
        ultimo=p;
        p->setProx(NULL);

        p->setid(id);
        p->setfollowers(followers);
        p->setgenres(genres);
        p->setname(name);
        p->setpopularity(popularity);

        n++;
    }

}

void ListaEncadeada::ImprimeIds()
{
    NoA* p=primeiro;
    for (int i=0;i<n;i++)
    {
        cout << i+2 <<" "<<p->getid() <<"," << p->getfollowers() <<"," << p->getgenres() <<"," << p->getname() <<"," <<p->getpopularity() << endl;
        p=p->getProx();
    }

}
void ListaEncadeada::escrevebin()

{
    ofstream artistasbin;


    artistasbin.open("artists.bin",ios::binary);

    for(NoA *p=primeiro;p!=NULL;p=p->getProx())
    {

        Artista este;
        strcpy(este.id,p->getid().c_str());
        strcpy(este.genres,p->getgenres().c_str());
        strcpy(este.name,p->getname().c_str());
        este.popularity=p->getpopularity();
        este.followers=p->getfollowers();

        artistasbin.write((char *)&(este) ,sizeof(Artista));

    }
    artistasbin.close();
}

void ListaEncadeada::Imprimebin()
{

    ifstream teste;

    teste.open("artists.bin",ios::binary);

    for(int i=0;i<n;i++)
    {
        Artista este;
        teste.read((char *) &(este),sizeof(Artista));
        cout << este.id << " ; " << este.followers<<" ; " << este.genres<< " ; " << este.name << " ; " << este.popularity << endl;
    }

    teste.close();
}
