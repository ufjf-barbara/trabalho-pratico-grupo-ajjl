#ifndef METODOSORDENACAO_H
#define METODOSORDENACAO_H


class MetodosOrdenacao
{
    public:
        MetodosOrdenacao();
        virtual ~MetodosOrdenacao();
        int part(vector <Artista> *vet, int inicio, int r);
        void quickSort(vector <Artista> *vet, int inicio, int fim );
        void mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,int metricasmerge[]);
        void mergesort(Artista vetordeartistas[],int inicio,int fim,int metricasmerge[]);
    private:
        
        
};  

#endif // METODOSORDENACAO_H
