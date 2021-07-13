#include <vector>
#include "MetodosOrdenacao.h"
#include "NoA.h"
#include <bits/stdc++.h>

using namespace std;

MetodosOrdenacao::MetodosOrdenacao() {
    testedeinput(); // Obtem informação sobre input.dat
}
MetodosOrdenacao::~MetodosOrdenacao() {}


bool MetodosOrdenacao::verificaArtista (vector<Artista> vetor, Artista aux) { // Funcao para verificacao de repeticao
    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true; // Caso artista for repetido
    }
    return false; // Caso seja um novo artista
}
vector<Artista> MetodosOrdenacao::artistasaleatorios(int tam, string arq3) { // Cria vetor de N artistas aleatorios
    vector<Artista> vetor; //Vetor que recebera dados de artists.bin
    vetor.reserve (tam);  // Aloca espaco
    ifstream artBin;
    artBin.open(arq3,ios::binary); // Abre artists.bin
    
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

void MetodosOrdenacao::ordenacoes(string arq3) { // Chama as ordenacoes
    BlocoQuick(arq3);
    BlocoHeap(arq3);
    BlocoMerge(arq3);
    DesempenhoMedio(); // Cria saida.txt com os resultados obtidos
    //imprimeBloco();  // Funcao para teste individuais
}

// Metodos de Ordenacao
void MetodosOrdenacao::mergeartista(Artista vetordeartistas[],int inicio,int metade,int fim,long int metricasmerge[]) {
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
void MetodosOrdenacao::mergesort(Artista vetordeartistas[],int inicio,int fim,long int metricasmerge[])
{
    int metade;
    if(inicio<fim){
        metade=(inicio+fim)/2;
        
        mergesort(vetordeartistas,inicio,metade,metricasmerge);
        mergesort(vetordeartistas,metade+1,fim,metricasmerge);
        mergeartista(vetordeartistas,inicio,metade,fim,metricasmerge);
  }
}
void MetodosOrdenacao::mergesortinicio(int n,long int metricasmerge[], string arq3)
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

void MetodosOrdenacao::quickSort(vector <Artista> *vet, int inicio, int fim, long int metricasQuick[]){ 
    if(inicio < fim){ // Enquanto posicao de inicio nao ultrapassar final
        int p = partQuick(vet, inicio, fim, metricasQuick); // Calcula posicao do pivo
        quickSort(vet, inicio, p - 1, metricasQuick); // Recursividade da primeira metade do vetor
        quickSort(vet, p, fim, metricasQuick); // Recursividade da segunda metade do vetor
    }
}
int MetodosOrdenacao::partQuick(vector <Artista> *vet, int esq, int dir, long int metricasQuick[]){
    int p = esq + (dir - esq) / 2; // indicado do pivo recebe a metade do vetor como posicao
    Artista pivo = vet->at(p); // posiciona pivo utilizando ponteiro
    int i = esq; // Posicao percorrida pela esquerda
    int j = dir; // Posicao percorrida pela direita
    while(i<=j) { // Enquanto esquerda nao ultrapassar direita
        while(vet->at(i).followers < pivo.followers) { // Compara followers de pivo com posicao mais a esquerda
            i++;
            metricasQuick[0]=metricasQuick[0]+1; // Contador de comparacoes
        }
        while(vet->at(j).followers > pivo.followers) { // Compara followers de pivo com posicao mais a direita
            j--;
            metricasQuick[0]=metricasQuick[0]+1; // Contador de comparacoes
        }
        if(i <= j) { 
            Artista aux = vet->at(i); // auxiliar para fazer a troca
            vet->at(i) = vet->at(j);
            vet->at(j) = aux;
            metricasQuick[1]=metricasQuick[1]+1; // Contador de movimentos
            i++;
            j--;
        }
    }
    return i; // Retorna indice para o pivo
}

void MetodosOrdenacao::heapSort(vector <Artista> *vet, int n, long int metricasHeap[]) {
    for (int i = n / 2 -1; i >= 0; i--) // Constroi a heap (rearranja o array)
        heapify(vet, n, i, metricasHeap); // Chama max heapify
    
    for (int i=n-1; i>=0; i--) { // Extrai elemento da heap
        Artista aux = vet->at(0); // auxiliar para fazer a troca
        vet->at(0) = vet->at(i);// Move raiz para fim
        vet->at(i) = aux;
        metricasHeap[1]=metricasHeap[1]+1; // Contador movimento
        heapify(vet, i, 0, metricasHeap); // Chama max heapify
    }
}
void MetodosOrdenacao::heapify(vector <Artista> *vet, int n, int i, long int metricasHeap[]) {
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
        Artista aux = vet->at(maior); // auxiliar para fazer a troca
        vet->at(maior) = vet->at(i);
        vet->at(i) = aux;
        metricasHeap[1]=metricasHeap[1]+1; // Contador movimento       
        heapify(vet, n, maior, metricasHeap); // Chama heapify para a sub-árvore correspondente
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
void MetodosOrdenacao::zerarmetricas(long int metrica[]) {
    metrica[0]=0;
    metrica[1]=0;
    metrica[2]=0;
}
void MetodosOrdenacao::BlocoMerge(string arq3) {
    cout << "Iniciando ordenacao por  MergeSort: " << endl;
    for (int k=0;k<3;k++) {
        for(int j=0;j<5;j++) {
            long int metricas[3];
            zerarmetricas(metricas);
            mergesortinicio(valores[j],metricas, arq3);
            MetricasMerge[k][j][0]=metricas[0];
            MetricasMerge[k][j][1]=metricas[1];
            MetricasMerge[k][j][2]=metricas[2];
            cout << " Concluido para N=" << valores[j] << endl;
        }
        cout << "  Conluido teste: " << k+1 << endl; 
    } 
    cout << "Ordenacao por MergeSort concluido" << endl;
}
void MetodosOrdenacao::BlocoQuick(string arq3) {
    cout << "Iniciando Ordenacao por QuickSort:" << endl;
    for (int k=0;k<3;k++) {
        for(int j=0;j<5;j++) {
            long int metricas[3];
            zerarmetricas(metricas);
            vector<Artista> vetor = artistasaleatorios(valores[j], arq3);
            clock_t start, end;
            start=clock();
            quickSort(&vetor, 0, valores[j]-1, metricas);
            end=clock();
            MetricasQuick[k][j][0]=metricas[0];
            MetricasQuick[k][j][1]=metricas[1];
            MetricasQuick[k][j][2]=end-start;
            cout << "Concluido para N = " << valores[j] << endl;
        }
        cout << "  Conluido teste: " << k+1 << endl;
    }
    cout << "Ordenacao por QuickSort oncluido" << endl;
}
void MetodosOrdenacao::BlocoHeap(string arq3) {
    cout << "Iniciando ordenacao por HeapSort:" << endl;
    for (int k=0;k<3;k++) {
        for(int j=0;j<5;j++) {
            long int metricas[3];
            zerarmetricas(metricas);
            vector<Artista> vetor = artistasaleatorios(valores[j], arq3);
            clock_t start, end;
            start=clock();
            heapSort(&vetor, valores[j], metricas);
            end=clock();
            MetricasHeap[k][j][0]=metricas[0];
            MetricasHeap[k][j][1]=metricas[1];
             MetricasHeap[k][j][2]=end-start;
            cout << " Concluido para N = " << valores[j] << endl;
        }
        cout << "  Conluido teste: " << k+1 << endl;
    }
    cout << "Ordenacao por HeapSort concluido" << endl;
}

vector<Artista> MetodosOrdenacao::moduloQuick(string arq3) {
    zerarmetricas(MetricasTeste);
    vector<Artista> vetor = artistasaleatorios(100, arq3);
    clock_t start, end;
    start=clock();
    quickSort(&vetor, 0, 99, MetricasTeste);
    end=clock();
    MetricasTeste[2]=end-start;
    return vetor;
}
vector<Artista> MetodosOrdenacao::moduloHeap(string arq3) {
    zerarmetricas(MetricasTeste);
    vector<Artista> vetor = artistasaleatorios(100,arq3);
    clock_t start, end;
    start=clock();
    heapSort(&vetor, 100, MetricasTeste);
    end=clock();
    MetricasTeste[2]=end-start;
    return vetor;
}
// Escreve teste.txt
void MetodosOrdenacao::moduloTeste(string arq3) {
    vector<Artista> vetor;
    ofstream arq("teste.txt");
    arq << "Teste de ordenação para N=100" << endl;
    arq << endl;
    arq << "-> Resultados para QuickSort:" << endl; 
    vetor = moduloQuick(arq3);
    arq << "- Comparações:" << MetricasTeste[0] << endl;
    arq << "- Movimentos:" << MetricasTeste[1] << endl;
    for (int i=0; i<100; i++) {
        arq << i <<" - Follows: "<< vetor[i].followers << " - Id: " << vetor[i].id << " - Name: " << vetor[i].name << endl;
    }
    arq << endl;
    arq << "-> Resultados para HeapSort:" << endl; 
    vetor = moduloHeap(arq3);
    for (int i=0; i<100; i++) {
        arq << i <<" - Follows: "<< vetor[i].followers << " - Id: " << vetor[i].id << " - Name: " << vetor[i].name << endl;
    }
    arq << "- Comparações:" << MetricasTeste[0] << endl;
    arq << "- Movimentos:" << MetricasTeste[1] << endl;
    arq << endl;
    arq << "-> Resultados para MergeSort:" << endl; 
    //BlocoMerge(arq3);
    arq << "- Comparações:" << MetricasTeste[0] << endl;
    arq << "- Movimentos:" << MetricasTeste[1] << endl;
    arq << endl;
}
void MetodosOrdenacao::imprimeBloco() // Apenas para auxiliar nosso teste interno
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

    arq.open("testeBlocoQuick.txt");
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

///função para escrever .txt com as saidas medias do desempenho de cada metodo de ordenação
void MetodosOrdenacao::DesempenhoMedio(){

    //arquivo desaida
    ofstream arq("saida.txt");

    //variavel parar realizar os calculos das medias
    int media[5][3];

    //limpa o vetor
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            media[j][i]=0;
        }
    }

    // a variavel recebe o somatorio de todos os valores obtidos
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            media[j][0]=MetricasMerge[i][j][0]+media[j][0];
            media[j][1]=MetricasMerge[i][j][1]+media[j][1];
            media[j][2]=MetricasMerge[i][j][2]+media[j][2];
        }
    }
    // a media é calculada
    for(int j=0;j<5;j++)
    {
        media[j][0]=media[j][0]/3;
        media[j][1]=media[j][1]/3;
        media[j][2]=media[j][2]/3;
    }

    // os resultados são então escritos na saida
    arq << "Desempenho medio de merge: " << endl << endl;
    for(int j=0;j<5;j++)
        {
            arq << "media de merge realativos para " << valores[j] << " entradas:"<< endl;;
            arq << "- Comparações:" << media[j][0] << endl;
            arq << "- Movimentos:" << media[j][1] << endl;
            arq << "- Tempo:" << (float)media[j][2]/CLOCKS_PER_SEC << "sec"  << endl;
        }
    arq << endl ;
    arq << endl ;

    // o mesmo se repete para todos os estilos de ordenação
        for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            media[j][i]=0;
        }
    }
        for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            media[j][0]=MetricasQuick[i][j][0]+media[j][0];
            media[j][1]=MetricasQuick[i][j][1]+media[j][1];
            media[j][2]=MetricasQuick[i][j][2]+media[j][2];
        }
    }
    for(int j=0;j<5;j++)
    {
        media[j][0]=media[j][0]/3;
        media[j][1]=media[j][1]/3;
        media[j][2]=media[j][2]/3;
    }

    arq << "Desempenho medio de Quick: " << endl << endl;
    for(int j=0;j<5;j++)
        {
            arq << "media de Quick realativos para " << valores[j] << " entradas:"<< endl;;
            arq << "- Comparações:" << media[j][0] << endl;
            arq << "- Movimentos:" << media[j][1] << endl;
            arq << "- Tempo:" << (float)media[j][2]/CLOCKS_PER_SEC << "sec"  << endl;
        }

    arq << endl ;
    arq << endl ;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            media[j][i]=0;
        }
    }
        for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            media[j][0]=MetricasHeap[i][j][0]+media[j][0];
            media[j][1]=MetricasHeap[i][j][1]+media[j][1];
            media[j][2]=MetricasHeap[i][j][2]+media[j][2];
        }
    }
    for(int j=0;j<5;j++)
    {
        media[j][0]=media[j][0]/3;
        media[j][1]=media[j][1]/3;
        media[j][2]=media[j][2]/3;
    }


    arq << "Desempenho medio de Heap: " << endl << endl;
    for(int j=0;j<5;j++)
        {
            arq << "media de merge realativos para " << valores[j] << " entradas:"<< endl;;
            arq << "- Comparações:" << media[j][0] << endl;
            arq << "- Movimentos:" << media[j][1] << endl;
            arq << "- Tempo:" << (float)media[j][2]/CLOCKS_PER_SEC << "sec"  << endl;
        }
}

