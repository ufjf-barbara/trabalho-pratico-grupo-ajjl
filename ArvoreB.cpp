#include "ArvoreB.h"
#include "NoB.h"
#include "iostream"
#include <string>
#include <vector>
#include <fstream>
#include "NoA.h"
using namespace std;


ArvoreB::ArvoreB(int tamanho,string arq)
{
    t=tamanho;
    Raiz=NULL;
    Arq=arq;

}

ArvoreB::~ArvoreB()
{
    //chama a função auxiliar para deletar
    Deletar(Raiz);
}

void ArvoreB::Deletar(NoB *p)
{
    // percorre toda a estrutura deletando os Nos
    int i=0;
    for(;i<p->n;i++)
    {
        if(p->folha==0)
           Deletar(p->filhos[i]);
        delete p;
    }
    if(p->folha==1)
        delete p;

}
void ArvoreB::GerarAleatorio(int tam)
{
    // pega uma quantidade tam de artistas aleatorios para colocar na estrutura
    vector<Artista>aleatorios = getAleatorios(tam,Arq);
    for(int i = 0; i < tam; i++) {

        string name = aleatorios[i].name;
        string codigo=aleatorios[i].id;
        int local=aleatorios[i].local;
        insere(name,local,codigo);
    }
}

bool ArvoreB::Busca(string Nome_Buscado,int *Local,string *codigo)
{
    //chama a função auxiliar para buscar
    return Buscaux(Nome_Buscado,Local,Raiz,codigo);
}
bool ArvoreB::Buscaux(string Nome_Buscado,int *local,NoB *p,string *codigo)
{
    int i;
    for(i=0;i<p->n && Nome_Buscado>p->chave[i];i++){    //percorre o vetor de chaves e encontra a posição que o valor deveria estar
    }

    if (p->chave[i]== Nome_Buscado){                    //se o nome for encontrado retorna seu local o codigo e o valor boll pra simbolizar se foi achado
       *local=p->local[i];
       *codigo=p->codigo[i];
       return 1;
    }
    if(p->folha == 1)                                  //caso o local que o nome deveria estar ele n seja encontrado e o no é uma folha retorna false pois não foi encontrado o nome
    {
        *local=-1;
        return 0;
    }

    return Buscaux(Nome_Buscado,local,p->filhos[i],codigo); //se o nó n for uma folha é possivel que a informação esteja no filho a função é chamada recursiva
}


void ArvoreB::Imprime()
{
    //chama a função auxiliar para imprimir
    auximpreme(Raiz);
}
void ArvoreB::auximpreme(NoB *p)
{
    int i=0;
    for(;i<p->n;i++)
    {
        if(p->folha==0)                 //caso o no n seja folha ocorre a chamada recursiva
           auximpreme(p->filhos[i]);
        cout << " |" << p->chave[i] << "| ";  //imprime todo o vetor de chaves
    }
}

void ArvoreB::iniciaNoB(NoB *p,int efolha)
{
    //inicia os valores do No para evitar lixo
    p->folha=efolha;
    p->chave = new string[2*t-1];
    p->codigo=new string[2*t-1];
    p->local = new int[2*t-1];
    p->filhos = new NoB*[2*t];
    p->n=0;

}

void ArvoreB::insere(string nome_artista,int local_artista,string codigo_artista)
{
    if(Raiz==NULL)                  //caso a estrutura esteja vazia o Primeiro no é criado e iniciado com os valores adequados
    {
        NoB *p=new NoB;
        Raiz=p;
        iniciaNoB(p,1);
        Raiz->chave[0]=nome_artista;
        Raiz->local[0]=local_artista;
        Raiz->codigo[0]=codigo_artista;
        Raiz->n=1;

    }
    else if(Raiz->n == (2*t)-1){  //caso a raiz esteja cheia é preciso realizar operação de separação e almentar a altura
            NoB *p=new NoB;
            iniciaNoB(p,0);

            p->filhos[0]= Raiz;

            separa(0,Raiz,p);  //função de separação

            int i=0;
            if (p->chave[0]<nome_artista)
                i++;

            insereaux(nome_artista,local_artista,codigo_artista,p->filhos[i]); //depois da separação os valores são inseridos no local adequado

            Raiz=p;
        }
    else{                       //caso a raiz n esteja cheia ou seja a primeira inserção os valores são inseridos normalmente
        insereaux(nome_artista,local_artista,codigo_artista,Raiz);
    }

    }

void ArvoreB::insereaux(string nome_artista,int local_artista,string codigo_artista,NoB *inserido)
{

    int deslocamento=inserido->n-1;     // o limite maximo de deslocamentos que pode ser feito pra inserir as informações
    // a inserção so pode ocorrer em nós folhas, caso seja um no folha é aberto um espaço no vetor para inserir as novas informaçõesno local adequado
    if(inserido->folha==1){
        while(deslocamento>=0 && inserido->chave[deslocamento]>nome_artista){
            inserido->chave[deslocamento+1]=inserido->chave[deslocamento];
            inserido->local[deslocamento+1]=inserido->local[deslocamento];
            inserido->codigo[deslocamento+1]=inserido->codigo[deslocamento];
            deslocamento--;
       }
       inserido->chave[deslocamento+1]=nome_artista;
       inserido->local[deslocamento+1]=local_artista;
       inserido->codigo[deslocamento+1]=codigo_artista;
       inserido->n=inserido->n+1;
    }
    if(inserido->folha==0){
        while(deslocamento>=0 && inserido->chave[deslocamento]>nome_artista)    //encontra qual dos filho devera ser percorrido
            deslocamento--;
        if(inserido->filhos[deslocamento+1]->n== 2 * t - 1){                    //caso o filho a ser inserido esteja cheio ele é separado
            separa(deslocamento+1,inserido->filhos[deslocamento+1],inserido);
            if(inserido->chave[deslocamento+1]<nome_artista)
                deslocamento++;
        }
        insereaux(nome_artista,local_artista,codigo_artista,inserido->filhos[deslocamento+1]);  //a função é chamada de forma recursiva até que uma folha com espaço seja achada
    }
}


void ArvoreB::separa(int i,NoB *separado,NoB *auxliar)
{
    NoB *p=new NoB;
    iniciaNoB(p,separado->folha);
    p->n=t-1;                           //metade do vetor sera preenchido, o tamanho do vetor é t*2

    for(int j=0;j<t-1;j++){             //coloca a primeira metade do vetor a ser separado em p
        p->chave[j]=separado->chave[j+t];
        p->local[j]=separado->local[j+t];
        p->codigo[j]=separado->codigo[j+t];
    }
    if(separado->folha == 0){          //caso o no n seja uma folha os filhos tbm são copiados
        for (int j = 0; j < t; j++)
            p->filhos[j] = separado->filhos[j + t];
    }
    separado->n=p->n;                  //separado vai ficar com metade do seu tamano original

    for (int j = auxliar->n; j >= i + 1; j--)
        auxliar->filhos[j + 1] = auxliar->filhos[j];

    auxliar->filhos[i+1]=p;         //adiciona o novo no criado a lista de filhos

    //tranfere os valores
    for (int j = auxliar->n - 1; j >= i; j--){
        auxliar->chave[j + 1] = auxliar->chave[j];
        auxliar->local[j + 1] = auxliar->local[j];
        auxliar->codigo[j + 1]=auxliar->codigo[j];
    }

    auxliar->chave[i] = separado->chave[t - 1];
    auxliar->local[i] = separado->local[t - 1];
    auxliar->codigo[i] = separado->codigo[t - 1];

    auxliar->n = auxliar->n + 1;


}

vector<Artista> ArvoreB::getAleatorios(int tam, string arq2) { // Cria vetor de N artistas aleatorios
    vector<Artista> lista; // Lista que recebera dados de artists.bin

    ifstream artBin;
    artBin.open(arq2,ios::binary); // Abre artists.bin
    //Calcula numero de linhas do .bin
    artBin.seekg(0,artBin.end); //Posiciona o ponteiro no final de .bin
    int length = artBin.tellg(); //Salva valor da posicao
    length = length/sizeof(Artista); //Calcula numero de linhas apartir dos bytes
    artBin.seekg(0,artBin.beg); //Retorna ponteiro para posicao inical de .bin
    length --; // ignora ultima linha
    for(int i=0;i<20000;i++) {
        Artista aux;
        int pos = i*(sizeof(Artista)-4); //pega posicao i
        artBin.seekg(pos); // Posiciona o ponteiro em .bin
        artBin.read((char *) &(aux),sizeof(Artista)); //Le conteudo da linha em .bin
        aux.local = pos; // Posicao apontada, para pegar a linha tem que mudar para "i".
        lista.push_back(aux); //Salva Artista na lista

    }
    artBin.close(); //Fecha .bin

    vector<Artista> random; // Vetor para a coleta da amostra aleatoria
    for(int i=0;i<tam;i++) {
        int limit = lista.size()-1; //Define o limite para o r
        int r = rand()%limit; // gera posicao aleatoria
        random.push_back(lista[r]); //Salva em nosso vetor random um elemento aleatorio da lista
        auto remove = lista.begin() + r; // ponteiro para artista da lista
        lista.erase(remove); // remove artista da lista
    }

    return random;
}


