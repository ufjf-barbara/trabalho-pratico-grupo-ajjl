#include "ArvoreVP.h"

using namespace std;

ArvoreVP::ArvoreVP() {
    raiz = nullptr;
    comparacoes = 0;
}

ArvoreVP::~ArvoreVP() {}

void ArvoreVP::start(string arq2){
    vector<Artista> vet;
    vet = getAleatorios(10, arq2);
    for(int i=0;i<10;i++)
        cout << vet[i].name << endl;

    return;
}

vector<Artista> ArvoreVP::getAleatorios(int tam, string arq2) { // Cria vetor de N artistas aleatorios
    vector<Artista> lista; // Lista que recebera dados de artists.bin

    ifstream artBin;
    artBin.open(arq2,ios::binary); // Abre artists.bin
    //Calcula numero de linhas do .bin
    artBin.seekg(0,artBin.end); //Posiciona o ponteiro no final de .bin
    int length = artBin.tellg(); //Salva valor da posicao
    length = length/sizeof(Artista); //Calcula numero de linhas apartir dos bytes
    artBin.seekg(0,artBin.beg); //Retorna ponteiro para posicao inical de .bin
    length --; // ignora ultima linha
    for(int i=0;i<length;i++) {
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
        int limit = length-i; //Define o limite para o r
        int r = rand()%limit; // gera posicao aleatoria
        random.push_back(lista[r]); //Salva em nosso vetor random um elemento aleatorio da lista
        auto remove = lista.begin() + r; // ponteiro para artista da lista
        lista.erase(remove); // remove artista da lista
    }

    return random;
}




void ArvoreVP::rotacionaEsquerda(NoVP *&raiz, NoVP *&no){

    NoVP *noDireito = no->getDireito();

    no->setDireito(noDireito->getEsquerdo());

    if (no->getDireito() != nullptr)
        no->getDireito()->setPai(no);

    noDireito->setPai(no->getPai());

    if (no->getPai() == nullptr) 
            raiz = noDireito;
    else if (no == no->getPai()->getEsquerdo())
        no->getPai()->setEsquerdo(noDireito);
    else
        no->getPai()->setDireito(noDireito);

    noDireito->setEsquerdo(no);
    no->setPai(noDireito);
}

void ArvoreVP::rotacionaDireita(NoVP *&raiz, NoVP *&no){

    NoVP *noEsquerdo = no->getEsquerdo();

    no->setEsquerdo(noEsquerdo->getDireito());

    if (no->getEsquerdo() != nullptr)
        no->getEsquerdo()->setPai(no);

    noEsquerdo->setPai(no->getPai());

    if (no->getPai() == nullptr)
        raiz = noEsquerdo;
    else if (no == no->getPai()->getEsquerdo())
        no->getPai()->setEsquerdo(noEsquerdo);
    else
        no->getPai()->setDireito(noEsquerdo);

    noEsquerdo->setDireito(no);
    no->setPai(noEsquerdo);
}




