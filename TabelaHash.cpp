#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include "TabelaHash.h"
#include "ListaEncadeadaTracks.h"
#include "MetodosOrdenacao.h"
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

TabelaHash::TabelaHash(int tam){
    this->tam=tam;
    tabela= (NoHash**) malloc(sizeof(NoHash*)*tam);
    for(int i=0;i<tam;i++)
    {
        tabela[i]=NULL;
    }
}


int converteId(string id){
    int soma = 0;
    for(int i = 0; i < id.length();i++){
        soma+= id[i];
    }
    return soma;
}

int TabelaHash::funct(string id,int j){

    int intId = converteId(id);
    long long k = (intId + j*j);
    int key = k % tam;

        return key;
}

void TabelaHash::insere(NoHash *item){

    int i; int j = 0;
    do{
        i=funct(item->id,j++);
        if(tabela[i] != NULL && tabela[i]->id == item->id){
            tabela[i]->frequencia++;
            if(item->popularity > tabela[i]->popularity){
                tabela[i]->musicaPopular = item->musicaPopular;
                tabela[i]->popularity = item->popularity;
            }
         return;
        }
    }
    while(tabela[i]!=NULL);

    tabela[i]=&(*item);
}


void TabelaHash::print(){

    cout<<"TABELA HASH TAMANHO "<<tam<<endl;
    for(int i=0;i<tam;i++)
    {
        if(tabela[i]!=NULL){
            cout<< "id: " << tabela[i]->id << " nome: " << tabela[i]->nome << " freq: " << tabela[i]->frequencia 
            << " musicaPopular: " << tabela[i]->musicaPopular << " popularity: " << tabela[i]->popularity << endl;
        }
}
}

// Seleciona N artista aleatorios
bool TabelaHash::verificaArtista (vector<Tracks> vetor, Tracks aux) {
    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true;
    }
    return false;
}
vector<Tracks> TabelaHash::tracksAleatorias(int tam, string arq4) {
    cout << "Gerando vetor" << endl;
    
    vector<Tracks> vetor; //Vetor que recebera .bin

    ifstream artBin;
    artBin.open(arq4,ios::binary);

    if  (artBin.fail()){ // excluir esse teste depois
        cout << "erro na leitura do .bin dentro de artista aleatorio" << endl;
        exit(1);
    }

    //Calcula numero de linhas do .bin
    artBin.seekg(0,artBin.end); //Posiciona o ponteiro no final de .bin
    int length = artBin.tellg(); //Salva valor da posicao

    length = length/sizeof(Tracks); //Calcula numero de linhas apartir dos bytes

    artBin.seekg(0,artBin.beg); //Retorna ponteiro para posicao inical de .bin

    for(int i=0;i<tam;i++) {
        Tracks aleatoria;
        
        int aleat = (rand()%length)*sizeof(Tracks); //Gera posicao aleatoria
        artBin.seekg(aleat); // Posiciona o ponteiro em .bin

        artBin.read((char *) &(aleatoria),sizeof(Tracks)); //Le conteudo da linha em .bin

        
        if(verificaArtista(vetor, aleatoria)) //Verificacao se existe repeticao de id com o vetor
            i--; //Caso seja repetido, o for é executado novamente no mesmo valor de i
        else
            vetor.push_back(aleatoria); //Nao havendo repeticao, o vetor recebe a linha de .bin
    }

    artBin.close(); //Fecha .bin
    return vetor;
}


vector<string> divideString(string tokenString){
    vector<string> tokens;

    // stream de strings de input inicializado com a string a ser separada
    istringstream tokenizer{tokenString};
    string token;

    // separa as sub-strings por vírgula e coloca no vetor destino
    while (getline(tokenizer, token, ','))
        tokens.push_back(token);

    return tokens;
}

NoHash** TabelaHash::copiaTabelaSemNull(){
    NoHash **copia = (NoHash**) malloc(sizeof(NoHash*)*tam);
    int j = 0;
    for (int i = 0; i < tam; i++)
    {
        if(tabela[i]!=NULL){
            copia[j] = &(*tabela[i]);
            j++;
        }
    }
    this->ocupacao = j;
    return copia;
}

void TabelaHash::maisFrequentes(NoHash** copia, int M, int op){
    if(op == 1){
        cout << "ARTISTAS MAIS FREQUENTES" << endl;
        for (int i = 0; i < M; i++)
        {
            cout << i + 1 << "° artista: " << copia[i]->nome << ", Musica mais popular: " << copia[i]->musicaPopular << ", Frequencia: " << copia[i]->frequencia << " vezes."<< endl;
        } 
    }
    else if(op == 2){
        ofstream arq("teste.txt");
        arq << "ARTISTAS MAIS FREQUENTES" << endl;
        for (int i = 0; i < M; i++)
        {
            arq << i + 1 << "° artista: " << copia[i]->nome << ", Musica mais popular: " << copia[i]->musicaPopular << ", Frequencia: " << copia[i]->frequencia << " vezes."<< endl;
        } 
    }
}

void TabelaHash::insereArtists(int tam, string arq4, int M, int op){

    vector<Tracks> tracksRandom = tracksAleatorias(tam,arq4);
    for (int i = 0; i < tracksRandom.size(); i++)
    {
        vector<string> artists = divideString(tracksRandom[i].artists);
        vector<string> idArtists = divideString(tracksRandom[i].id_artists);
        if(artists.size() > 1){
            for(int j = 0; j < artists.size(); j++){
                NoHash *novoArtista = new NoHash(idArtists[j], artists[j], 1, tracksRandom[i].name, tracksRandom[i].popularity);
                insere(novoArtista);
            }
        }
        else{
            NoHash *novoArtista = new NoHash(tracksRandom[i].id_artists, tracksRandom[i].artists, 1, tracksRandom[i].name, tracksRandom[i].popularity);
            insere(novoArtista);
        }
    }
    MetodosOrdenacao quick;
    NoHash **copia = copiaTabelaSemNull();
    quick.ordenaTabelaHash(copia, ocupacao);
    maisFrequentes(copia, M, op);
}