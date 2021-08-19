#ifndef ARVOREB_H
#define ARVOREB_H
#include "NoB.h"
#include "NoA.h"
#include <string>
#include<vector>


using namespace std;



class ArvoreB
{
    public:
        ArvoreB(int tamanho,string arq2);
        ~ArvoreB();

        void Imprime();
        void insere(string nome_artista,int local_artista,string codigo_artista);
        bool Busca(string Nome_Buscado,int *resultado,string *codigo);
        void GerarAleatorio(int tam);



    private:
        int t;
        NoB *Raiz;
        string Arq;
        bool Buscaux(string Nome_Buscado,int *resultado,NoB *p,string *codigo);
        void insereaux(string nome_artista,int local_artista,string codigo_artista,NoB *inserido);
        vector<Artista> getAleatorios(int tam, string arq2);
        void separa(int i,NoB *separado,NoB *auxliar);
        void auximpreme(NoB *p);
        void Deletar(NoB *p);
        void iniciaNoB(NoB *p,int efolha);

};

#endif // ARVOREB_H
