#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ListaEncadeada.h"         // estrutura de dados que armazena as informacoes dos artistas
#include "ListaEncadeadaTracks.h"   // estrutura de dados que armazena as informacoes das tracks

using namespace std;

/*
Comandos para compilar via terminal: 
    g++ *.cpp *.h -o trab
    ./trab
*/

int main()
{
    ///iniciacao das variaveis relativas ao artista

    ifstream artista;

    string id,genres,name,popularity,followers,l;
    int popularity_Int;
    float followers_Float;

    ListaEncadeada ArtistsData;

    ///abertura do file para a leitura
    artista.open("artists.csv",ios::in | ios::out);

    ///verifica se ha problema na abertura do arquivo
    ///sai do programa caso haja
    if  (artista.fail())
    {
        cout << "error" << endl;
        exit(1);
    }

    ///Descarta a primeira linha que nao contem informacoes

        getline(artista,l,'\n');


    ///Loop que se repete ate que todo o arquivo tenha sido percorrido
    ///E armazena as informacoes na lista
    while(artista.good())
    {
        getline(artista,id,',');

        getline(artista ,followers,',');
        stringstream s(followers);
        s  >> followers_Float;   ///tranformando a string em um float

        getline(artista,l,'[');
        getline(artista,genres,']');
        getline(artista,l,',');


        getline(artista,name,',');

        getline(artista,popularity,'\n');
        stringstream ss(popularity);
        ss  >> popularity_Int;   ///tranformando a string em um int

        ArtistsData.NovoArtista(id,followers_Float,genres,name,popularity_Int);
    }

    //ArtistsData.ImprimeIds(); // imprime todo o conteudo da lista
    ArtistsData.escrevebin();
    //ArtistsData.Imprimebin();

    ///importa de bin
    ArtistsData.importaBin(100);


    ///fechamento do file
    artista.close();


      /// variaveis relativas as musicas
    ifstream tracks;
    ListaEncadeadaTracks TracksData;

    string nameT,popularityT,duration_ms,explicito,danceability,energy,key,loudness,idT,
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




    ///abertura do file para a leitura
    tracks.open("tracks.csv",ios::in | ios::out);


    ///verifica se ha problema na abertura do arquivo
    ///sai do programa caso haja

    if  (tracks.fail())
    {
        cout << "error" << endl;
        exit(1);
    }

    ///Descarta a primeira linha que nao contem informacoes
    getline(tracks,l,'\n');

    ///Loop que se repete ate que todo o arquivo tenha sido percorrido
    ///E armazena as informacoes na lista
    while (tracks.good())
    {
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

        TracksData.NovaTrack(idT,nameT,popularityT_int,duration_ms_int,explicito_bool,artistsT,
                                       id_artists,release_date,danceability_float,energy_float,key_float,loudness_float,
                                        mode_float,speechiness_float,acousticness_float,instrumentalness_float,liveness_float,
                                        valence_float,tempo_float,time_signature_int);
    }


    ///fechamento do file
    tracks.close();
    
    TracksData.escrevebin();
    //TracksData.Imprimebin();
    
    ///importa de bin
    TracksData.importaBin(100);


    
    //TracksData.ImprimeIds(); // imprime todo o conteudo da lista
    

    return 0;
}
