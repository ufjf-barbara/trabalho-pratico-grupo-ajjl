#include <vector>
#include "MetodosOrdenacao.h"
#include "NoA.h"

using namespace std;

MetodosOrdenacao::MetodosOrdenacao() {}

MetodosOrdenacao::~MetodosOrdenacao() {}

// Seleciona N artista aleatorios
vector<Artista> MetodosOrdenacao::artistasaleatorios(int tam) {
    vector<Artista> vetor; //Vetor que recebera .bin

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
        
        int aleat = (rand()%length)*sizeof(Artista); //Gera posicao aleatoria
        artBin.seekg(aleat); // Posiciona o ponteiro em .bin

        artBin.read((char *) &(aleatoria),sizeof(Artista)); //Le conteudo da linha em .bin

        
        if(verificaArtista(vetor, aleatoria)) //Verificacao se existe repeticao de id com o vetor
            i--; //Caso seja repetido, o for é executado novamente no mesmo valor de i
        else
            vetor.push_back(aleatoria); //Nao havendo repeticao, o vetor recebe a linha de .bin
    }

    artBin.close(); //Fecha .bin

    return vetor;
}
bool verificaArtista (vector<Artista> vetor, Artista aux) {
    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true;
    }
    return false;
}


// Menu para ordenacoes
void MetodosOrdenacao::ordenaQuick() {
    BlocoQuick();

    // chama quick
}

void MetodosOrdenacao::ordenaMerge() {
    BlocoMerge();

    
}

void MetodosOrdenacao::ordenaHeap() {
    BlocoHeap();

    
}

void MetodosOrdenacao::ModuloTeste() {
    vector<Artista> teste = artistasaleatorios(100);
    quickSort(&teste, 0, 99, metricasQuick);
    escreveTeste(metricasQuick);
    mergesortinicio(100, metricasmerge);
    escreveTeste(metricasmerge);
    heapSort(&teste, 100, metricasHeap);
    escreveTeste(metricasHeap);
}

// Metodos de Ordenacao
void MetodosOrdenacao::mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,int metricasmerge[]) {

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
        A[i]=vetordeartistas[i];    /// tranforma um vector em um array

    mergesort(A,0,n-1,metricasmerge);
    //for(int i=0;i<n;i++)
    //{
    //    cout <<i<<"-"<< A[i].id <<"-"<< A[i].name << endl;       ///imprime o array depois da ordenação
    //}

    delete[] A;
}

void MetodosOrdenacao::quickSort(vector <Artista> *vet, int inicio, int fim, int metricasQuick[] ){
        if(inicio < fim){
            int p = part(vet, inicio, fim);
            quickSort(vet, inicio, p - 1);
            quickSort(vet, p + 1, fim);
        }
}
int MetodosOrdenacao::part(vector <Artista> *vet, int inicio, int r, int metricasQuick[]){
    Artista pivo = vet->at(r);
    metricasQuick[1]=metricasQuick[1]+1;
    int i = inicio-1;
    for(int j = inicio;j<r;j++){
        metricasQuick[0]=metricasQuick[0]+1;
        if(vet->at(j).followers <= pivo.followers){
            i++;
            Artista aux = vet->at(i);
            vet->at(i) = vet->at(j);
            vet->at(j) = aux;
            metricasQuick[1]=metricasQuick[1]+1;
        }
    }
    Artista aux = vet->at(i+1);
    vet->at(i+1) = vet->at(r);
    vet->at(r) = aux;
    metricasQuick[1]=metricasQuick[1]+1;
    return i+1;
}

void MetodosOrdenacao::heapSort(vector <Artista> *vet, int n, int metricasHeap[]) {
    for (int i = n / 2 -1; i >= 0; i--) // Constroi a heap (rearranja o array)
        heapify(vet, n, i);
    
    for (int i=n-1; i>=0; i--) { // Extrai elemento da heap
        // Move raiz para fim
        Artista aux = vet->at(0);
        vet->at(0) = vet->at(i);
        vet->at(i) = aux;

        metricasHeap[1]=metricasHeap[1]+1; // Contador movimento
       
        heapify(vet, i, 0); // Chama max heapify
    }
}
void MetodosOrdenacao::heapify(vector <Artista> *vet, int n, int i, int metricasHeap[]) {
    int maior = i; // Inicializa maior elemento como raiz
    int esq = 2 * i + 1; // filho esquerdo = 2*i + 1
    int dir = 2 * i + 2; // filho direito = 2*i + 2
    
    metricasHeap[0]=metricasHeap[0]+1;
    if (esq < n && vet->at(esq).followers > vet->at(maior).followers)   // Se o filho esquerdo é maior que pai (raiz)
        maior = esq;
    
    metricasHeap[0]=metricasHeap[0]+1;
    if (dir < n && vet->at(dir).followers > vet->at(maior).followers)   // Se o filho direito é maior que o maior até agora
        maior = dir;
    
    if (maior != i) {   //Se o maior não é a raiz
        Artista aux = vet->at(maior);
        vet->at(maior) = vet->at(i);
        vet->at(i) = aux;

        metricasHeap[1]=metricasHeap[1]+1; // Contador movimento
        
        heapify(vet, n, maior); // Chama heapify para a sub-árvore correspondente.
    }
}

void MetodosOrdenacao::testedeinput()
{
    ifstream inputexiste;
    inputexiste.open("input.dat");
    if(!inputexiste)
    {
        inputexiste.close();
        ofstream output;
        output.open("input.dat");
        int informacao[5];
        informacao[0]=10000;
        informacao[1]=50000;
        informacao[2]=100000;
        informacao[3]=500000;
        informacao[4]=800000;
        for(int i=0;i<5;i++)
            output<<informacao[i]<<'\n';
        output.close();
        inputexiste.open("input.dat");
    }
    inputexiste >>valores[0]>>valores[1]>>valores[2]>>valores[3]>>valores[4];
}

// Contadores
void MetodosOrdenacao::zerarmetricas(int metrica[]) {
    metrica[0]=0;
    metrica[1]=0;
    metrica[2]=0;
}
void MetodosOrdenacao::BlocoMerge() {
    int MetricasMerge[3][5][3];
    for (int k=0;k<3;k++) {
        for(int j=0;j<5;j++) {
            int metricas[3];
            zerarmetricas(metricas);
            mergesortinicio(valores[j],metricas);
            MetricasMerge[k][j][0]=metricas[0];
            MetricasMerge[k][j][1]=metricas[1];
            MetricasMerge[k][j][2]=metricas[2];
        }
    } 
}
void MetodosOrdenacao::BlocoQuick() {   
    int MetricasQuick[3][5][3];
    for (int k=0;k<3;k++) {
        for(int j=0;j<5;j++) {
            int metricas[3];
            zerarmetricas(metricas);
            vector<Artista> vetor = artistasaleatorios(valores[j]);
            quickSort(&vetor, 0, valores[j-1], metricas);
            MetricasQuick[k][j][0]=metricas[0];
            MetricasQuick[k][j][1]=metricas[1];
            MetricasQuick[k][j][2]=metricas[2];
        }
    } 
}
void MetodosOrdenacao::BlocoHeap() {   
    int MetricasHeap[3][5][3];
    for (int k=0;k<3;k++) {
        for(int j=0;j<5;j++) {
            int metricas[3];
            zerarmetricas(metricas);
            vector<Artista> vetor = artistasaleatorios(valores[j]);
            heapSort(&vetor, valores[j], metricas);
            MetricasHeap[k][j][0]=metricas[0];
            MetricasHeap[k][j][1]=metricas[1];
            MetricasHeap[k][j][2]=metricas[2];
        }
    } 
}

