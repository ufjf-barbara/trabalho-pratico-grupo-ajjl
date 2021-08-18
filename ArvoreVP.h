#ifndef ARVOREVP_H
#define ARVOREVP_H
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

        void start(string arq3);

    private:
        NoVP* raiz;

        vector<Artista> getAleatorios(int tam, string arq3);

        void criaArvore(vector <Artista> *artista);
        void insere(Artista artista);
        NoVP* auxInsere(NoVP *raiz, NoVP *newNo);
        void balanceia(NoVP *&raiz, NoVP *&newNo); // Falta fazer

        void rotacionaEsquerda(NoVP *&raiz, NoVP *&no);
        void rotacionaDireita(NoVP *&raiz, NoVP *&no);
        void trocaCor(NoVP *no1, NoVP *no2); // Falta Fazer

        

};  

#endif // ARVOREVP_H