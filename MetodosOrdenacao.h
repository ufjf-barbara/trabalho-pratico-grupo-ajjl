#ifndef METODOSORDENACAO_H
#define METODOSORDENACAO_H
#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "NoA.h"

class Contadores
{
	public:
		int comparacoes; 
		int movimentos;
		clock_t tempo; //tempo gasto em Clocks, é preciso converter para segundos depois usando (CLOCKS_PER_SEC)

        Contadores(){
			comparacoes =0;
			movimentos =0;
			tempo = clock();
		};

		~Contadores(){};
		void limparContadores(){
			comparacoes = 0;
			movimentos = 0;
			tempo =  clock();
		}	
};


class MetodosOrdenacao
{
    public:
        MetodosOrdenacao();
        virtual ~MetodosOrdenacao();
        void testeContadores();
        void quickSort(vector <Artista> *vet, int inicio, int fim );
        void mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,int metricasmerge[]);
        void mergesort(Artista vetordeartistas[],int inicio,int fim,int metricasmerge[]);
        void heapSort(vector <Artista> *vet, int n);
        Contadores *contadores;

    private:
        int part(vector <Artista> *vet, int inicio, int r);
        void heapify(vector <Artista> *vet, int n, int i);
       
};  

#endif // METODOSORDENACAO_H
