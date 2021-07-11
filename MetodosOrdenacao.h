#ifndef METODOSORDENACAO_H
#define METODOSORDENACAO_H
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "NoA.h"

class MetodosOrdenacao
{
    public:
        MetodosOrdenacao();
        virtual ~MetodosOrdenacao();
        vector<Artista> artistasaleatorios(int tam);
        void mergesortinicio(int n,int metricasmerge[]);
        void mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,int metricasmerge[]);
        void mergesort(Artista vetordeartistas[],int inicio,int fim,int metricasmerge[]);
        void quickSort(vector <Artista> *vet, int inicio, int fim, int metricasQuick[][][]);
        void heapSort(vector <Artista> *vet, int n, int metricasHeap[][][]);
        void testedeinput(int valores[]);
        void ordenaQuick();
        void ordenaHeap();
        void ordenaMerge();
        void BlocoMerge();
        void zerarmetricas(int metrica[]);
    private:
        int part(vector <Artista> *vet, int inicio, int r, int metricasQuick[][][]);
        void heapify(vector <Artista> *vet, int n, int i, int metricasHeap[][][]);
        bool verificaArtista (vector<Artista> vetor, Artista aux);
        int valores[5];
       
};  

#endif // METODOSORDENACAO_H
