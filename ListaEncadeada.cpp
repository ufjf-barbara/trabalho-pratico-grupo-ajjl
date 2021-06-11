#include "ListaEncadeada.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>  

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

void ListaEncadeada::imprimeTestes(vector <Artista> vetor){
    if(vetor.size() ==10){
        cout << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
        for(int i = 0; i < 10; i++){
                cout << "Id: "<< vetor[i].id << endl;
                cout << "Followers: " << vetor[i].followers<< endl;
                cout << "Genres: " << vetor[i].genres<< endl;
                cout << "Name: " << vetor[i].name << endl;
                cout << "Popularity: "  << vetor[i].popularity<< endl;
                cout << "===================================" <<endl;
                }
    }
    else if( vetor.size() == 100){
         ofstream arq("saidaArtists.txt");
         arq << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
         for(int i = 0; i < 100; i++){
                arq << "Id: "<< vetor[i].id << endl;
                arq << "Followers: " << vetor[i].followers<< endl;
                arq << "Genres: " << vetor[i].genres<< endl;
                arq << "Name: " << vetor[i].name << endl;
                arq << "Popularity: "  << vetor[i].popularity<< endl;
                arq << "===================================" <<endl;
                }
                cout<< "ARQUIVO GERADO COM SUCESSO!" << endl;
    }
    else
        cout <<"TAMANHO DE ENTRADA INVÁLIDA! ESCOLHA N=10 OU N=100"<<endl;
}

///Funcao para verificar se existe repeticoes
bool verifica (vector<Artista> vetor, Artista aux)
{
    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true;        
    }
    return false;
}

void ListaEncadeada::importaBin(int tam)
{    
    vector<Artista> vetor;
    ifstream impBin;

    impBin.open("artists.bin",ios::binary);

    if  (impBin.fail())
        cout << "erro na leitura do .bin" << endl;

    ///Le tammanho do arquivo
    impBin.seekg(0,impBin.end);
    int length = impBin.tellg();   
    length = length/sizeof(Artista);
    
    impBin.seekg(0,impBin.beg);

    for(int i=0;i<tam;i++)
    {
        Artista listArtista;

        ///Pega posicao aleatoria
        int aleat = (rand()%length)*sizeof(Artista);
        impBin.seekg(aleat);

        impBin.read((char *) &(listArtista),sizeof(Artista));
        
        /// Verificacao se existe repeticao
        if(verifica(vetor, listArtista))
            i--;
        else
            vetor.push_back(listArtista);
    }
    imprimeTestes(vetor);

    impBin.close();
}