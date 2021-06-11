#include "ListaEncadeadaTracks.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>  

using namespace std;

ListaEncadeadaTracks::ListaEncadeadaTracks()
{
    n=0;
    primeiro=NULL;
    ultimo=NULL;
}

ListaEncadeadaTracks::~ListaEncadeadaTracks()
{
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

void ListaEncadeadaTracks::ImprimeIds() // usando a lista encadeada imprime todos os dados 
{
    NoT* p = primeiro; 
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

void ListaEncadeadaTracks::escrevebin()
{
    ofstream tracksbin;

    tracksbin.open("tracks.bin",ios::binary);

    for(NoT *p=primeiro;p!=NULL;p=p->getProx())

    {
        Tracks esta;           
        strcpy(esta.id,p->getid().c_str());
        strcpy(esta.name,p->getname().c_str());
        esta.popularity=p->getpopularity();
        esta.duration_ms=p->getduration_ms();
        esta.explicito=p->getexplicito();
        strcpy(esta.artists,p->getartists().c_str());
        strcpy(esta.id_artists,p->getid_artists().c_str());
        strcpy(esta.release_date,p->getrelease_date().c_str());
        esta.danceability=p->getdanceability();
        esta.energy=p->getenergy();
        esta.key=p->getkey();
        esta.loudness=p->getloudness();
        esta.mode=p->getmode();
        esta.speechiness=p->getspeechiness();
        esta.acousticness=p->getacousticness();
        esta.instrumentalness=p->getinstrumentalness();
        esta.liveness=p->getliveness();
        esta.valence=p->getvalence();
        esta.tempo=p->gettempo();
        esta.time_signature=p->gettime_signature();

        tracksbin.write((char *) &(esta),sizeof(Tracks));

    }

    tracksbin.close();

}

void ListaEncadeadaTracks::Imprimebin() ///função que imprime o arquivo binario
{
    ifstream teste;
    teste.open("tracks.bin",ios::binary);

    for(int i=0;i<n;i++)
    {
        Tracks esta;
        teste.read((char *) &(esta),sizeof(Tracks));

        cout << esta.id << ",";
        cout << esta.name<< ",";
        cout << esta.popularity<< ",";
        cout << esta.duration_ms<< ",";
        cout << esta.explicito<<",";
        cout << esta.artists <<",";
        cout << esta.id_artists <<",";
        cout << esta.release_date<< ",";
        cout << esta.danceability << ",";
        cout << esta.energy << "," ;
        cout << esta.key << ",";
        cout << esta.loudness << ",";
        cout << esta.mode << ",";
        cout << esta.speechiness << ",";
        cout << esta.acousticness<< ",";
        cout << esta.instrumentalness << "," ;
        cout << esta.liveness << ",";
        cout << esta.valence << ",";
        cout << esta.tempo <<",";
        cout << esta.time_signature;
        cout << endl;
    }
    teste.close();
}

void ListaEncadeadaTracks::imprimeTestes(vector<Tracks> vetor){
    if(vetor.size() <=10){
        cout << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
        for(int i = 0; i < vetor.size(); i++){
                cout << "Id: "<< vetor[i].id << endl;
                cout << "Name: " <<vetor[i].name<< endl;
                cout << "Popularity: " << vetor[i].popularity<< endl;
                cout << "Duration: " << vetor[i].duration_ms<< endl;
                cout <<"Explicito: " << vetor[i].explicito<< endl;
                cout <<"Artists: " << vetor[i].artists << endl;
                cout << "Id artists: "<< vetor[i].id_artists << endl;
                cout << "Release date: "<< vetor[i].release_date<< endl;
                cout << "Danceability: " << vetor[i].danceability << endl;
                cout <<"Energy: " << vetor[i].energy << endl;
                cout << "Key: " <<vetor[i].key << endl;
                cout <<"Loudness: "<< vetor[i].loudness << endl;
                cout <<"Mode: " << vetor[i].mode << endl;
                cout << "Speechiness: " << vetor[i].speechiness << endl;
                cout <<"Acousticness: " << vetor[i].acousticness<< endl;
                cout << "Instrumentalness: " << vetor[i].instrumentalness << endl;
                cout <<"Liveness: "<< vetor[i].liveness << endl;
                cout << "Valence: " << vetor[i].valence << endl;
                cout <<"Tempo: " << vetor[i].tempo <<endl;
                cout <<"Signature: " << vetor[i].time_signature << endl;
                cout << "===================================" <<endl;
                }
    }
    else {
         ofstream arq("saidaTracks.txt");
         arq << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
         for(int i = 0; i < vetor.size() || i <=100; i++){
                arq << "Id: "<< vetor[i].id << endl;
                arq << "Name: " <<vetor[i].name<< endl;
                arq << "Popularity: " << vetor[i].popularity<< endl;
                arq << "Duration: " << vetor[i].duration_ms<< endl;
                arq <<"Explicito: " << vetor[i].explicito<< endl;
                arq <<"Artists: " << vetor[i].artists << endl;
                arq << "Id artists: "<< vetor[i].id_artists << endl;
                arq << "Release date: "<< vetor[i].release_date<< endl;
                arq << "Danceability: " << vetor[i].danceability << endl;
                arq <<"Energy: " << vetor[i].energy << endl;
                arq << "Key: " <<vetor[i].key << endl;
                arq <<"Loudness: "<< vetor[i].loudness << endl;
                arq <<"Mode: " << vetor[i].mode << endl;
                arq << "Speechiness: " << vetor[i].speechiness << endl;
                arq <<"Acousticness: " << vetor[i].acousticness<< endl;
                arq << "Instrumentalness: " << vetor[i].instrumentalness << endl;
                arq <<"Liveness: "<< vetor[i].liveness << endl;
                arq << "Valence: " << vetor[i].valence << endl;
                arq <<"Tempo: " << vetor[i].tempo <<endl;
                arq <<"Signature: " << vetor[i].time_signature << endl;
                arq << "===================================" <<endl;
                }
                cout<< "ARQUIVO GERADO COM SUCESSO!" << endl;
    }
    }



/// funcao para verificar se existe repeticao
bool verifica (vector<Tracks> vetor, Tracks aux)
{
    for (int i=0; i<vetor.size(); i++){  
        if (vetor[i].id == aux.id)
            return true;        
    }
    return false;
}

/// Funcao para importar de arquivo binario
void ListaEncadeadaTracks::importaBin(int tam)
{    
    vector<Tracks> vetor;
    ifstream impBin;
    impBin.open("artists.bin",ios::binary);

    if  (impBin.fail())
        cout << "erro na leitura do .bin" << endl;
 
    ///Le tammanho do arquivo
    impBin.seekg(0,impBin.end);
    int length = impBin.tellg();   
    length = length/sizeof(Tracks);
    
    impBin.seekg(0,impBin.beg);

    for(int i=0;i<tam;i++)
    {
        Tracks listTracks;

        ///Pega posicao aleatoria
        int aleat = (rand()%length)*sizeof(Tracks);
        impBin.seekg(aleat);

        impBin.read((char *) &(listTracks),sizeof(Tracks));
        
        // Verificacao se existe repeticao
        if(verifica(vetor, listTracks))
            i--;
        else
            vetor.push_back(listTracks);
    }
    imprimeTestes(vetor);

    impBin.close();
}

