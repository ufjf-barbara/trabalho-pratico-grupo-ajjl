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
        vector<Artista> artistasaleatorios(int tam, string arq3);
        void ordenacoes(string arq3);
        void moduloTeste(string arq3, string arq4);
        void imprimeBloco();
        void DesenpenhoMedio();

    private:
        int MetricasMerge[3][5][3];
        int MetricasQuick[3][5][3];
        int MetricasHeap[3][5][3];
        long int MetricasTeste [3];
        int valores[5];
        
        bool verificaArtista (vector<Artista> vetor, Artista aux);
        void testedeinput();
        void escreveTesteOrd(string arq3);

        void mergesortinicio(int n, long int metricasmerge[], string arq3);
        void mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,long int metricasmerge[]);
        void mergesort(Artista vetordeartistas[],int inicio,int fim,long int metricasmerge[]);
        void quickSort(vector <Artista> *vet, int inicio, int fim, long int metricasQuick[]);
        int partQuick(vector <Artista> *vet, int inicio, int r, long int metricasQuick[]);
        void heapSort(vector <Artista> *vet, int n, long int metricasHeap[]);
        void heapify(vector <Artista> *vet, int n, int i, long int metricasHeap[]);
               
        void BlocoMerge(int opc, string arq3);
        void BlocoQuick(int opc, string arq3);
        void BlocoHeap(int opc, string arq3);
        void zerarmetricas(int long metrica[]);
        
        
        
};  

#endif // METODOSORDENACAO_H
