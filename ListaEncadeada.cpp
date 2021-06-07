#include "ListaEncadeada.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


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
