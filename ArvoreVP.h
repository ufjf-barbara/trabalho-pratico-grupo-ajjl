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
        int comparacoes;

        vector<Artista> getAleatorios(int tam, string arq3);

        void rotacionaEsquerda(NoVP *&raiz, NoVP *&noh);
        void rotacionaDireita(NoVP *&raiz, NoVP *&noh);

        

};  

#endif // ARVOREVP_H