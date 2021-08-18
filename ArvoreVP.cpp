#include "ArvoreVP.h"

using namespace std;

ArvoreVP::ArvoreVP() { raiz = nullptr; }

ArvoreVP::~ArvoreVP() {}

void ArvoreVP::start(string arq2){
    vector<Artista> vet;
    vet = getAleatorios(10, arq2);
    
    for(int i=0;i<10;i++) // para imprimir amostra
        cout << vet[i].name << endl;

    criaArvore(&vet);
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

bool ArvoreVP::calculaNome(Artista art1, Artista art2){}

void ArvoreVP::criaArvore(vector<Artista> *artista){
    for(auto i = artista->begin(); i != artista->end(); i++) {
        Artista no = *i;
        insere(no);
    }
}

void ArvoreVP::insere(Artista artista){

    NoVP *newNo = new NoVP(artista);

    raiz = auxInsere(raiz, newNo);

    balanceia(raiz, newNo);
}

NoVP* ArvoreVP::auxInsere(NoVP *no, NoVP* newNo){

    if(no == nullptr)
        no = newNo;
    else if(newNo->getArtista().name  <  no->getArtista().name) {
        no->setEsquerdo(auxInsere(no->getEsquerdo(), newNo));
        no->getEsquerdo()->setPai(no);
    }
    else if (newNo->getArtista().name  > no->getArtista().name) { 

        no->setDireito(auxInsere(no->getDireito(), newNo));
        no->getDireito()->setPai(no);
    }
    return no;
}



void ArvoreVP::balanceia(NoVP *&raiz, NoVP *&no){
    //pai e avô do novo nó inserido
    NoVP *pai = nullptr;
    NoVP *avo = nullptr;

    while ((no != raiz) && (no->getCor()) && (no->getPai()->getCor())) {

        pai = no->getPai();
        avo = no->getPai()->getPai();

        
        if (pai == avo->getEsquerdo()) {//pai do nó é filho a esquerda do avô do nó

            NoVP *tio = avo->getDireito();
            
            if (tio != nullptr && tio->getCor()) { //tio vermelho, apenas recoloração               
                avo->setCor(RED);
                pai->setCor(BLACK);
                tio->setCor(BLACK);
                no = avo;
            }
            else {  // nó nao tem tio ou tio preto           
                if (no == pai->getDireito()) {  // rotação dupla
                    rotacionaEsquerda(raiz, pai);
                    no = pai;
                    pai = no->getPai();
                }

                rotacionaDireita(raiz, avo);
                trocaCor(pai, avo);
                no = pai;
            }
        }
        else { //pai do nó é filho a direita do avô do nó

            NoVP *tio = avo->getEsquerdo();
 
            if ((tio != nullptr) && (tio->getCor())) {  //tio vermelho, apenas recoloração   
                avo->setCor(RED);
                pai->setCor(BLACK);
                tio->setCor(BLACK);
                no = avo;
            }
            else { // nó nao tem tio ou tio preto 
                if (no == pai->getEsquerdo()) {     // rotação dupla
                    rotacionaDireita(raiz, pai);
                    no = pai;
                    pai = no->getPai();
                }
                rotacionaEsquerda(raiz, avo);
                trocaCor(pai, avo);
                no = pai;
            }
        }
    }
    raiz->setCor(BLACK);
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

void ArvoreVP::trocaCor(NoVP *no1, NoVP *no2){
    bool cor = no1->getCor();
    no1->setCor(no2->getCor());
    no2->setCor(cor);
} 




