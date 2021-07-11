#ifndef METODOSORDENACAO_H
#define METODOSORDENACAO_H


class MetodosOrdenacao
{
    public:
        MetodosOrdenacao();
        virtual ~MetodosOrdenacao();
        void quickSort(vector <Artista> *vet, int inicio, int fim );
        void mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,int metricasmerge[]);
        void mergesort(Artista vetordeartistas[],int inicio,int fim,int metricasmerge[]);
        void heapSort(vector <Artista> *vet, int n);

    private:
        int part(vector <Artista> *vet, int inicio, int r);
        void heapify(vector <Artista> *vet, int n, int i);
       
};  

#endif // METODOSORDENACAO_H
