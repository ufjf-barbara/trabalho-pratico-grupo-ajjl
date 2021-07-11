#include "MetodosOrdenacao.h"
using namespace std;

MetodosOrdenacao::MetodosOrdenacao(){
    contadores = new Contadores();

}

MetodosOrdenacao::~MetodosOrdenacao(){

    delete contadores;
}

void MetodosOrdenacao::quickSort(vector <Artista> *vet, int inicio, int fim ){
        if(inicio < fim){
            int p = part(vet, inicio, fim);
            quickSort(vet, inicio, p - 1);
            quickSort(vet, p + 1, fim);
        }
}

int MetodosOrdenacao::part(vector <Artista> *vet, int inicio, int r){
    int pivo = vet->at(r);
    contadores->copiasRegistro++;
    int i = inicio-1;
    for(int j = inicio;j<r;j++){
        contadores->comparacoesChaves++;
        if(vet->at(j) <= pivo){
            i++;
            int aux = vet->at(i);
            vet->at(i) = vet->at(j);
            vet->at(j) = aux;
            contadores->copiasRegistro++;
        }
    }
    int aux = vet->at(i+1);
    vet->at(i+1) = vet->at(r);
    vet->at(r) = aux;
    contadores->copiasRegistro++;
    return i+1;
}
bool verificaArtista (vector<Artista> vetor, Artista aux){

    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true;
    }
    return false;
}

vector<Artista> MetodosOrdenacao::artistasaleatorios(int tam){
    //Vetor que recebera .bin
    vector<Artista> vetor;

    ifstream artBin;
    artBin.open("artists.bin",ios::binary);

    if  (artBin.fail()){
        cout << "erro na leitura do .bin" << endl;
        exit(1);
    }

    //Calcula numero de linhas do .bin
    artBin.seekg(0,artBin.end); //Posiciona o ponteiro no final de .bin
    int length = artBin.tellg(); //Salva valor da posicao

    length = length/sizeof(Artista); //Calcula numero de linhas apartir dos bytes

    artBin.seekg(0,artBin.beg); //Retorna ponteiro para posicao inical de .bin

    for(int i=0;i<tam;i++) {
        Artista aleatoria;
        //Gera posicao aleatoria e posiciona o ponteiro em .bin

        int aleat = (rand()%length)*sizeof(Artista);
        artBin.seekg(aleat);

        //Le conteudo da linha em .bin
        artBin.read((char *) &(aleatoria),sizeof(Artista));

        //Verificacao se existe repeticao de id com o vetor
        if(verificaArtista(vetor, aleatoria))
            i--; //Caso seja repetido, o for é executado novamente no meosm valor de i
        else
            vetor.push_back(aleatoria); //Nao havendo repeticao, o vetor recebe a linha de .bin
    }

    artBin.close(); //Fecha .bin

    return vetor;
}

int MetodosOrdenacao::part(vector <Artista> *vet, int inicio, int r){

}

void MetodosOrdenacao::mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,int metricasmerge[])
{

   int esquerda= inicio;
   int direita = metade+1;
   int tamanho = fim-inicio+1;

   vector<Artista> temporario;

   while(esquerda<=metade && direita<=fim)
   {
       metricasmerge[0]=metricasmerge[0]+1;//contador de comparações
       if(vetordeartistas[esquerda].followers<=vetordeartistas[direita].followers)
       {
            temporario.push_back(vetordeartistas[esquerda]);
            metricasmerge[0]=metricasmerge[0]+1; //contador de comparações
            esquerda++;
       }
       else
       {
           metricasmerge[0]=metricasmerge[0]+1; //contador de comparações
           temporario.push_back(vetordeartistas[direita]);
           direita++;
       }
   }
    while(esquerda<=metade)
    {
        metricasmerge[0]=metricasmerge[0]+1;//contador de comparações
        temporario.push_back(vetordeartistas[esquerda]);
        esquerda++;
    }
    while(direita<=fim)
    {
        metricasmerge[0]=metricasmerge[0]+1;//contador de comparações
        temporario.push_back(vetordeartistas[direita]);
        direita++;
    }
    int j=0;
    for(int i=inicio;j<tamanho;i++,j++)
    {
        metricasmerge[1]=metricasmerge[1]+1;//contador de movimentações
        metricasmerge[0]=metricasmerge[0]+1;//contador de comparações
        vetordeartistas[i]=temporario[j];
    }
}

void MetodosOrdenacao::mergesort(Artista vetordeartistas[],int inicio,int fim,int metricasmerge[])
{
    int metade;
    if(inicio<fim){
        metade=(inicio+fim)/2;
        mergesort(vetordeartistas,inicio,metade,metricasmerge);
        mergesort(vetordeartistas,metade+1,fim,metricasmerge);
        mergeartista(vetordeartistas,inicio,metade,fim,metricasmerge);
  }
}


void MetodosOrdenacao::mergesortinicio(int n,int metricasmerge[])
{

    vector<Artista> vetordeartistas;
    vetordeartistas=artistasaleatorios(n);

    Artista *A=new Artista[n];
    for(int i=0;i<n;i++)
        A[i]=vetordeartistas[i];

    mergesort(A,0,n-1,metricasmerge);
    //for(int i=0;i<n;i++)
    //{
    //    cout <<i<<"-"<< A[i].id <<"-"<< A[i].name << endl;
    //}

    delete[] A;
}



