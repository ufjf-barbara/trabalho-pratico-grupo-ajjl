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

//Funcao para a criacao da lista com a utilizacao de ponteiros
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
        p->setAnt(NULL);

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
        p->setAnt(ultimo);
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


//Funcao para teste onde imprime todo o conteudo da lista
void ListaEncadeadaTracks::imprimeIds() {
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

//Funcao para a criacao e escrita do .bin
void ListaEncadeadaTracks::escreveBin()
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

//Funcao para teste onde imprime todo o conteudo de .bin
void ListaEncadeadaTracks::imprimeBin() ///função que imprime o arquivo binario
{
    ifstream teste;
    teste.open("tracks.bin",ios::binary);

    for(int i=0;i<n;i++)
    {
        Tracks esta;
        teste.read((char *) &(esta),sizeof(Tracks));

        cout << esta.id << endl;
        cout << esta.name<< endl;
        cout << esta.popularity<< endl;
        cout << esta.duration_ms<< endl;
        cout << esta.explicito<<endl;
        cout << esta.artists <<endl;
        cout << esta.id_artists <<endl;
        cout << esta.release_date<< endl;
        cout << esta.danceability << endl;
        cout << esta.energy << ","  << endl;
        cout << esta.key << endl;
        cout << esta.loudness << endl;
        cout << esta.mode << endl;
        cout << esta.speechiness << endl;
        cout << esta.acousticness<< endl;
        cout << esta.instrumentalness << ","  << endl;
        cout << esta.liveness << endl;
        cout << esta.valence << endl;
        cout << esta.tempo << endl;
        cout << esta.time_signature << endl;
        cout << endl;
    }
    teste.close();
}

//Funcao utilizada pelo nosso menu no console para a impressao do vetor importado de .bin
void ListaEncadeadaTracks::imprimeTestes(vector<Tracks> vetor){
    if(vetor.size()  == 10){
        cout << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
        for(int i = 0; i < 10; i++){
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
    else  if(vetor.size() == 100){
         ofstream arq("saidaTracks.txt");
         arq << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
         for(int i = 0; i < 100; i++){
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

//Funcao para verificar se existe repeticao dentro do vetor
bool verifica (vector<Tracks> vetor, Tracks aux) {
    for (int i=0; i<vetor.size(); i++){  
        if (vetor[i].id == aux.id)
            return true;        
    }
    return false;
}

//Funcao para importar de arquivo binario para vetor
vector<Tracks> ListaEncadeadaTracks::importaBin(int tam) {

    ifstream trackBin;
    trackBin.open("tracks.bin",ios::binary);

    if  (trackBin.fail()){
        cout << "erro na leitura do .bin" << endl;
        exit(1);
    }
    
    //Variavel aux do rand
    int x=n-1;

    //Vetor que recebera .bin
    vector<Tracks> vetor;
    
    for (int i=0;i<tam;i++){
        Tracks aleatoria;
    
        //Gera um numero aleatorio
        int random = rand()%n;
        //Aponta para essa posicao aleatoria em .bin
        trackBin.seekg(sizeof(Tracks)*random,trackBin.beg);

        //Le conteudo da linha selecionada de .bin
        trackBin.read((char *) &(aleatoria),sizeof(Tracks));

        //Verifica se o id ja foi importado anteriormente
        if(verifica(vetor, aleatoria))
            i--; //Caso seja repetido, o for é executado novamente com mesmo valor de i
        else
            vetor.push_back(aleatoria); //Nao havendo repeticao, o vetor recebe a linha de .bin
    }

    trackBin.close(); //Fecha .bin

    //Apos a criacao do vetor ser terminada, chama a funcao de impressao do vetor
    imprimeTestes(vetor);
    return vetor;
}
void ListaEncadeadaTracks::NovaLista(string arq2)
{
    ifstream tracks;
    string nameT,popularityT,duration_ms,explicito,danceability,energy,key,loudness,idT,l,
    mode,speechiness,acousticness,instrumentalness,liveness,valence,tempo,time_signature,artistsT,id_artists,release_date;


    bool explicito_bool;

    int popularityT_int;
    int duration_ms_int;
    int time_signature_int;

    float danceability_float;
    float energy_float;
    float key_float;
    float loudness_float;
    float mode_float;
    float speechiness_float;
    float acousticness_float;
    float instrumentalness_float;
    float liveness_float;
    float valence_float;
    float tempo_float;

    tracks.open(arq2, ios::in | ios::out);

    if  (tracks.fail()) {
        cout << "> Erro na leitura de tracks.csv" << endl;
        exit(1);
    }

    ///Descarta a primeira linha que nao contem informacoes
    getline(tracks,l,'\n');

    ///Loop que se repete ate que todo o arquivo tenha sido percorrido e armazena as informacoes na lista
     while(tracks.good()) {
        getline(tracks,idT,',');

        getline(tracks,nameT,',');

        getline(tracks,popularityT,',');
        stringstream pop(popularityT);
        pop  >> popularityT_int;

        getline(tracks,duration_ms,',');
        stringstream du(duration_ms);
        du >> duration_ms_int;

        getline(tracks,explicito,',');
        stringstream ex(explicito);
        ex >> explicito_bool;

        getline(tracks,l,'[');
        getline(tracks,artistsT,']');
        getline(tracks,l,',');


        getline(tracks,l,'[');
        getline(tracks,id_artists,']');
        getline(tracks,l,',');

        getline(tracks, release_date, ',');

        getline(tracks,danceability , ',');
        stringstream da(danceability);
        da >> danceability_float;

        getline(tracks,energy , ',');
        stringstream en(energy);
        en >> energy_float;

        getline(tracks,key , ',');
        stringstream ke(key);
        ke >> key_float;

        getline(tracks,loudness , ',');
        stringstream lo(loudness);
        lo >> loudness_float;

        getline(tracks,mode , ',');
        stringstream mo(mode);
        mo >> mode_float;

        getline(tracks,speechiness , ',');
        stringstream sp(speechiness);
        sp >> speechiness_float;

        getline(tracks,acousticness , ',');
        stringstream ac(acousticness);
        ac >> acousticness_float;

        getline(tracks,instrumentalness , ',');
        stringstream in(instrumentalness);
        in >> instrumentalness_float;

        getline(tracks,liveness, ',');
        stringstream li(liveness);
        li >> liveness_float;

        getline(tracks,valence, ',');
        stringstream va(valence);
        va >> valence_float;

        getline(tracks,tempo, ',');
        stringstream te(tempo);
        te >> tempo_float;

        getline(tracks,time_signature , '\n');
        stringstream ti(time_signature);
        ti >> time_signature_int;

        NovaTrack(idT,nameT,popularityT_int,duration_ms_int,explicito_bool,artistsT,id_artists,release_date,danceability_float,
                            energy_float,key_float,loudness_float,mode_float,speechiness_float,acousticness_float,instrumentalness_float,
                            liveness_float,valence_float,tempo_float,time_signature_int);
        }

        tracks.close();
        deletaultimo();
}
void ListaEncadeadaTracks::deletaultimo()
{
    NoT *p=ultimo->getAnt();
    delete ultimo;
    ultimo=p;
    ultimo->setProx(NULL);
    n--;
}


