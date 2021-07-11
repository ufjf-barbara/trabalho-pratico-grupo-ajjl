#include "MetodosOrdenacao.h"
using namespace std;

MetodosOrdenacao::MetodosOrdenacao(){
    contadores = new Contadores();

}

MetodosOrdenacao::~MetodosOrdenacao(){

    delete contadores;
}

void MetodosOrdenacao::quickSort(vector <Artista> *vet, int inicio, int fim ){
        if(inicio < fim){
            int p = part(vet, inicio, fim);
            quickSort(vet, inicio, p - 1);
            quickSort(vet, p + 1, fim);
        }
}

int MetodosOrdenacao::part(vector <Artista> *vet, int inicio, int r){
    int pivo = vet->at(r);
    contadores->copiasRegistro++;
    int i = inicio-1;
    for(int j = inicio;j<r;j++){
        contadores->comparacoesChaves++;
        if(vet->at(j) <= pivo){
            i++;
            int aux = vet->at(i);
            vet->at(i) = vet->at(j);
            vet->at(j) = aux;
            contadores->copiasRegistro++;
        }
    }
    int aux = vet->at(i+1);
    vet->at(i+1) = vet->at(r);
    vet->at(r) = aux;
    contadores->copiasRegistro++;
    return i+1;
}