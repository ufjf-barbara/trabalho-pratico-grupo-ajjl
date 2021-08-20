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
        int comparacoes = 0; // Contador de comparações

        void start(int tam, string arq3); // Inicializa as operações
        bool busca(string name, int *local, string *codigo); // Realiza a busca pela arvore apartir da raiz
        void insere(Artista artista);
        void geraGrafo(); // gera um grafo da arvore para testes


    private:
        NoVP* raiz; // Ponteiro para a raiz da arvore

        void getAleatorios(int tam, string arq3); // Seleciona amostra aleatoria de artistas
        
        NoVP *auxBusca(NoVP *raiz, string name); // Responsável pela recursividade na operação de busca

        void criaArvore(vector <Artista> *artista);  // Cria e inicializa nó com o Artista selecionado

        NoVP* auxInsere(NoVP *raiz, NoVP *newNo);   // Responsável pela recursividade na operação de inserção

        void balanceia(NoVP *&raiz, NoVP *&newNo);  // Responsável pela analise de balanceamento e chama as operações abaixo se necessário
        void rotacionaEsquerda(NoVP *&raiz, NoVP *&no); 
        void rotacionaDireita(NoVP *&raiz, NoVP *&no);
        void trocaCor(NoVP *no1, NoVP *no2); 

        void auxGeraGrafo(NoVP *no); // aux para recursividade na geração do grafo

        

};  

#endif // ARVOREVP_H_INCLUDED