#ifndef METODOSORDENACAO_H
#define METODOSORDENACAO_H
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "NoA.h"
#include "NoHash.h"

class MetodosOrdenacao
{
    public:
        MetodosOrdenacao();
        virtual ~MetodosOrdenacao();
        vector<Artista> artistasaleatorios(int tam, string arq3);
        void ordenacoes(string arq3, string arq5);
        void moduloTeste(string arq3);
        void imprimeBloco();
        void DesempenhoMedio();
        void ordenaTabelaHash(NoHash **vet, int tam);


    private:
        long int MetricasMerge[3][5][3];
        long int MetricasQuick[3][5][3];
        long int MetricasHeap[3][5][3];
        long int MetricasTeste [3];
        int valores[5];
        
        void testedeinput(string arq5);

        void mergesortinicio(int n, long int metricasmerge[], string arq3);
        void mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,long int metricasmerge[]);
        void mergesort(Artista vetordeartistas[],int inicio,int fim,long int metricasmerge[]);
        void quickSort(vector <Artista> *vet, int inicio, int fim, long int metricasQuick[]);
        int partQuick(vector <Artista> *vet, int esq, int dir, long int metricasQuick[]);
        void heapSort(vector <Artista> *vet, int n, long int metricasHeap[]);
        void heapify(vector <Artista> *vet, int n, int i, long int metricasHeap[]);
        void quickSortTabelaHash(NoHash **vet, int inicio, int fim);
        int partQuickTabelaHash(NoHash **vet, int esq, int dir);

        void BlocoMerge(string arq3);
        void BlocoQuick(string arq3);
        void BlocoHeap(string arq3);
        void zerarmetricas(int long metrica[]);

        vector<Artista> moduloHeap(string arq3);
        vector<Artista> moduloQuick(string arq3); 
        void ModuloQuick(Artista A[],string arq3);
};  

#endif // METODOSORDENACAO_H
