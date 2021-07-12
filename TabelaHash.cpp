#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include "TabelaHash.h"

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

