#include <vector>
#include "MetodosOrdenacao.h"
#include "NoA.h"

using namespace std;

MetodosOrdenacao::MetodosOrdenacao() {
    testedeinput();
}

MetodosOrdenacao::~MetodosOrdenacao() {}

// Seleciona N artista aleatorios
bool MetodosOrdenacao::verificaArtista (vector<Artista> vetor, Artista aux) {
    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true;
    }
    return false;
}
vector<Artista> MetodosOrdenacao::artistasaleatorios(int tam, string arq3) {
    cout << "Gerando vetor" << endl;
    
    vector<Artista> vetor; //Vetor que recebera .bin

    ifstream artBin;
    artBin.open(arq3,ios::binary);

    if  (artBin.fail()){ // excluir esse teste depois
        cout << "erro na leitura do .bin dentro de artista aleatorio" << endl;
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

// Menu para ordenacoes
void MetodosOrdenacao::ordenacoes(string arq3) {
    BlocoMerge(1, arq3);
    BlocoQuick(1, arq3);
    BlocoHeap(1, arq3);

}

void MetodosOrdenacao::moduloTeste(string arq3, string arq4) {
    escreveTesteOrd(arq3);
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
void MetodosOrdenacao::mergesortinicio(int n,int metricasmerge[], string arq3)
{

    vector<Artista> vetordeartistas;
    vetordeartistas=artistasaleatorios(n, arq3);

    Artista *A=new Artista[n];
    for(int i=0;i<n;i++)
        A[i]=vetordeartistas[i];    /// tranforma um vector em um array

    clock_t start, end;
    start=clock();
    mergesort(A,0,n-1,metricasmerge);
    end= clock();

    metricasmerge[2]=int(end-start);

    delete[] A;
}

void MetodosOrdenacao::quickSort(vector <Artista> *vet, int inicio, int fim, int metricasQuick[] ){
    if(inicio < fim){
        int p = partQuick(vet, inicio, fim, metricasQuick);
        quickSort(vet, inicio, p - 1, metricasQuick);
        quickSort(vet, p + 1, fim, metricasQuick);
    }
}
int MetodosOrdenacao::partQuick(vector <Artista> *vet, int inicio, int r, int metricasQuick[]){
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
        heapify(vet, n, i, metricasHeap);
    
    for (int i=n-1; i>=0; i--) { // Extrai elemento da heap
        // Move raiz para fim
        Artista aux = vet->at(0);
        vet->at(0) = vet->at(i);
        vet->at(i) = aux;

        metricasHeap[1]=metricasHeap[1]+1; // Contador movimento
       
        heapify(vet, i, 0, metricasHeap); // Chama max heapify
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
        
        heapify(vet, n, maior, metricasHeap); // Chama heapify para a sub-árvore correspondente.
    }
}

void MetodosOrdenacao::testedeinput() {
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
void MetodosOrdenacao::BlocoMerge(int opc, string arq3) {
    if (opc == 1) {
        cout << "=== Iniciando Teste de Merge:" << endl;
        for (int k=0;k<3;k++) {
            for(int j=0;j<5;j++) {
                int metricas[3];
                zerarmetricas(metricas);
                mergesortinicio(valores[j],metricas, arq3);
                MetricasMerge[k][j][0]=metricas[0];
                MetricasMerge[k][j][1]=metricas[1];
                MetricasMerge[k][j][2]=metricas[2];
                cout << "Concluido N=" << valores[j] << endl;
            }
            cout << "Conluido teste " << k+1 << endl; 
        } 
        cout << "=== Merge Concluido" << endl;
    }  
    else if (opc == 2) {
        zerarmetricas(MetricasTeste);
        mergesortinicio(100, MetricasTeste, arq3);
    } 
}
void MetodosOrdenacao::BlocoQuick(int opc, string arq3) {
    if (opc == 1) {
        cout << "=== Iniciando Teste de Quick:" << endl;
        for (int k=0;k<3;k++) {
            for(int j=0;j<5;j++) {
                int metricas[3];
                zerarmetricas(metricas);
                vector<Artista> vetor = artistasaleatorios(valores[j], arq3);
                clock_t start, end;
                start=clock();
                quickSort(&vetor, 0, valores[j-1], metricas);
                end=clock();
                MetricasQuick[k][j][0]=metricas[0];
                MetricasQuick[k][j][1]=metricas[1];
                MetricasQuick[k][j][2]=end-start;
                cout << "Concluido N=" << valores[j] << endl;
            }
            cout << "Conluido teste " << k+1 << endl;
        }
        cout << "=== Quick Concluido" << endl;
    }
    else if (opc == 2) {
            zerarmetricas(MetricasTeste);
            vector<Artista> vetor = artistasaleatorios(100, arq3);
            clock_t start, end;
            start=clock();
            quickSort(&vetor, 0, 99, MetricasTeste);
            end=clock();
            MetricasTeste[2]=end-start;
    }
}
void MetodosOrdenacao::BlocoHeap(int opc, string arq3) {
    if (opc == 1) {
        cout << "=== Iniciando Teste de Heap:" << endl;
        for (int k=0;k<3;k++) {
            for(int j=0;j<5;j++) {
                int metricas[3];
                zerarmetricas(metricas);
                vector<Artista> vetor = artistasaleatorios(valores[j], arq3);
                clock_t start, end;
                start=clock();
                heapSort(&vetor, valores[j], metricas);
                end=clock();
                MetricasHeap[k][j][0]=metricas[0];
                MetricasHeap[k][j][1]=metricas[1];
                MetricasHeap[k][j][2]=end-start;
                cout << "Concluido N=" << valores[j] << endl;
            }
            cout << "Conluido teste " << k+1 << endl;
        }
        cout << "=== Heap Concluido" << endl;
    }
    else if (opc == 2) {
    zerarmetricas(MetricasTeste);
    vector<Artista> vetor = artistasaleatorios(100,arq3);
    clock_t start, end;
    start=clock();
    heapSort(&vetor, 100, MetricasTeste);
    end=clock();
    MetricasTeste[2]=end-start;
    }
}


// Escreve teste.txt
void MetodosOrdenacao::escreveTesteOrd(string arq3) {
    ofstream arq("teste.txt");
    arq << "Teste de ordenação para N=100" << endl;
    arq << " " << endl;
    BlocoQuick(2, arq3);
    arq << "Resultados para QuickSort:" << endl; 
    arq << "- Comparações:" << MetricasTeste[0] << endl;
    arq << "- Movimentos:" << MetricasTeste[1] << endl;
    arq << "- Tempo:" << MetricasTeste[2] << endl;
    arq << " " << endl;
    BlocoHeap(2, arq3);
    arq << "Resultados para HeapSort:" << endl; 
    arq << "- Comparações:" << MetricasTeste[0] << endl;
    arq << "- Movimentos:" << MetricasTeste[1] << endl;
    arq << "- Tempo:" << MetricasTeste[2] << endl; 
    arq << " " << endl;
    BlocoMerge(2, arq3);
    arq << "Resultados para MergeSort:" << endl; 
    arq << "- Comparações:" << MetricasTeste[0] << endl;
    arq << "- Movimentos:" << MetricasTeste[1] << endl;
    arq << "- Tempo:" << MetricasTeste[2] << endl;
    arq << " " << endl;

}
void MetodosOrdenacao::imprimeBloco()
{
    ofstream arq("testeBlocoMerge.txt");
    for (int i=0;i<3;i++)
    {
        arq << i+1 << " execução:" << endl << endl;
        for(int j=0;j<5;j++)
        {
            arq << "teste realativos a: " << valores[j]<< endl;;
            arq << "- Comparações:" << MetricasMerge[i][j][0] << endl;
            arq << "- Movimentos:" << MetricasMerge[i][j][1] << endl;
            arq << "- Tempo:" << MetricasMerge[i][j][2] << endl;
        }
        arq << endl ;
    }
    arq.close();

    arq.open("testeBlocoquick.txt");
        for (int i=0;i<3;i++)
    {
        arq << i+1 << " execução:" << endl << endl;
        for(int j=0;j<5;j++)
        {
            arq << "teste realativos a: " << valores[j]<< endl;;
            arq << "- Comparações:" << MetricasQuick[i][j][0] << endl;
            arq << "- Movimentos:" << MetricasQuick[i][j][1] << endl;
            arq << "- Tempo:" << MetricasQuick[i][j][2] << endl;
        }
        arq << endl ;
    }
    arq.close();
    arq.open("testeBlocoHeap.txt");
    for (int i=0;i<3;i++)
    {
        arq << i+1 << " execução:" << endl << endl;
        for(int j=0;j<5;j++)
        {
            arq << "teste realativos a: " << valores[j]<< endl;;
            arq << "- Comparações:" << MetricasHeap[i][j][0] << endl;
            arq << "- Movimentos:" << MetricasHeap[i][j][1] << endl;
            arq << "- Tempo:" << MetricasHeap[i][j][2] << endl;
        }
        arq << endl ;
    }
    arq.close();
}

// -> criar um escreve resultados da tabela hash
