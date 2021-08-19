#ifndef ARVOREVP_H_INCLUDED
#define ARVOREVP_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include "NoA.h"
#include "NoVP.h"

#define RED 1
#define BLACK 0

using namespace std;

class ArvoreVP
{
    public:
        ArvoreVP();
        ~ArvoreVP();

        void start(int tam, string arq3);
        bool busca(string name, int *local, string *codigo);

    private:
        NoVP* raiz; // Ponteiro para a raiz da arvore

        vector<Artista> getAleatorios(int tam, string arq3); // Seleciona amostra aleatoria de artistas
        NoVP* auxBusca(NoVP *raiz, string name);

        void criaArvore(vector <Artista> *artista); 
        void insere(Artista artista);
        NoVP* auxInsere(NoVP *raiz, NoVP *newNo);

        void balanceia(NoVP *&raiz, NoVP *&newNo); 
        void rotacionaEsquerda(NoVP *&raiz, NoVP *&no);
        void rotacionaDireita(NoVP *&raiz, NoVP *&no);
        void trocaCor(NoVP *no1, NoVP *no2); 

        void geraGrafo(); // gera um grafo da arvore para testes
        void auxGeraGrafo(NoVP *no); // aux para recursividade

        

};  

#endif // ARVOREVP_H_INCLUDED