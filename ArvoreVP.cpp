#include "ArvoreVP.h"

using namespace std;

ArvoreVP::ArvoreVP() { raiz = nullptr; }

ArvoreVP::~ArvoreVP() {}

void ArvoreVP::start(int tam, string arq2) {
    getAleatorios(tam, arq2);
    //geraGrafo();
}


void ArvoreVP::getAleatorios(int tam, string arq2) { // Cria vetor de N artistas aleatorios
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

    clock_t t;  // Usado para pegar posicao aleatoria a cada execucao
    t = clock(); // Usado para pegar posicao aleatoria a cada execucao
    for(int i=0;i<tam;i++) {
        Artista aux; // Cria um artista aux
        int limit = length-i; //Define o limite para o r
        srand(t); // Usado para pegar posicao aleatoria a cada execucao
        int r = rand()%limit; // gera posicao aleatoria
        aux = lista[r]; // aux recebe artista da lista na posicao r
        insere(aux); //Insere artista
        auto remove = lista.begin() + r; // ponteiro para artista da lista
        lista.erase(remove); // remove artista da lista
    }

}

bool ArvoreVP::busca(string name, int *local, string *codigo){
    NoVP *buscado = auxBusca(raiz, name);
    if(buscado == nullptr){
        comparacoes++;
        return false;
    }
    *local = buscado->getArtista().local;
    *codigo = buscado->getArtista().id; 
    return true;
}

NoVP* ArvoreVP::auxBusca(NoVP *no, string nome){
    if(no == nullptr || no->getArtista().name == nome) {
        comparacoes++;
        return no;
    }

    string noName = no->getArtista().name;
    string name = nome;
    // tornando minusculo para comparar
    transform(name.begin(), name.end(), name.begin(), ::tolower); 
    transform(noName.begin(), noName.end(), noName.begin(), ::tolower);
    
    if(noName < name){
        comparacoes++;
        return auxBusca(no->getDireito(), nome);
    }
    return auxBusca(no->getEsquerdo(), nome);
}


void ArvoreVP::insere(Artista artista){
    NoVP *newNo = new NoVP(artista);
    raiz = auxInsere(raiz, newNo);
    balanceia(raiz, newNo);
}

NoVP* ArvoreVP::auxInsere(NoVP *no, NoVP* newNo){
    string name1;
    string name2;

    if(!(no == nullptr)){    
        name1 = newNo->getArtista().name;
        name2 = no->getArtista().name;
        transform(name1.begin(), name1.end(), name1.begin(), ::tolower);
        transform(name2.begin(), name2.end(), name2.begin(), ::tolower);
    }

    if(no == nullptr)
        no = newNo;
    else if(name1 <  name2) {
        no->setEsquerdo(auxInsere(no->getEsquerdo(), newNo));
        no->getEsquerdo()->setPai(no);
    }
    else if (name1 > name2) { 

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


void ArvoreVP::geraGrafo(){ // gera um grafo da arvore para testes
    ofstream arq("grafo.txt", ios::app);  // Lembrar que ao finalizar é preciso abrir o .txt e ajustar para o formato do codigo
    arq << "digraph{"<< endl;
    auxGeraGrafo(this->raiz);
    arq << "}"<< endl;
    arq.close();
}

void ArvoreVP::auxGeraGrafo(NoVP* no){  // gera no formato para visualizar
    if(no == nullptr)
        return;

    ofstream arq("grafo.txt", ios::app);
    string cor;
    if (no->getCor())
        cor = "#ff6666";
    else
        cor = "#9c9c9c";
        
    arq << no->getArtista().name << "[shape=\"ellipse\"style=\"filled\"fillcolor=\""<< cor << "\"]" << endl;
    
    NoVP *esq = no->getEsquerdo();
    if(!(esq == nullptr)){
        arq << no->getArtista().name << "->" << esq->getArtista().name << endl;
        auxGeraGrafo(esq);
    }

    NoVP *dir = no->getDireito();
    if(!(dir == nullptr)){
        arq << no->getArtista().name << "->" << dir->getArtista().name << endl;
        auxGeraGrafo(dir);
    }

    arq.close();
}




