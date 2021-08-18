#include "ListaEncadeada.h"

using namespace std;

ListaEncadeada::ListaEncadeada() {
    n=0;
    primeiro=NULL;
    ultimo=NULL;
}

ListaEncadeada::~ListaEncadeada() {
    NoA *p=primeiro;
    while (p != NULL)
    {
        NoA *t = p->getProx();
        delete p;
        p=t;
    }
}

//Funcao para a criacao da lista com a utilizacao de ponteiros
void ListaEncadeada::NovoArtista(string id,float followers,string genres,string name,int popularity)
{
    if(n==0)
    {
        NoA* p=new NoA();
        primeiro=p;
        ultimo=p;
        p->setProx(NULL);
        p->setAnt(NULL);

        p->setid(id);
        p->setfollowers(followers);
        p->setgenres(genres);
        p->setname(name);
        p->setpopularity(popularity);

        n++;
    }
    else
    {
        NoA* p=new NoA();
        ultimo->setProx(p);
        p->setAnt(ultimo);
        ultimo=p;
        p->setProx(NULL);

        p->setid(id);
        p->setfollowers(followers);
        p->setgenres(genres);
        p->setname(name);
        p->setpopularity(popularity);

        n++;
    }
}
//Funcao para teste onde imprime todo o conteudo da lista
void ListaEncadeada::imprimeIds()
{
    NoA* p=primeiro;
    for (int i=0;i<n;i++)
    {
        cout << i+2 <<" "<<p->getid() <<"," << p->getfollowers() <<"," << p->getgenres() <<"," << p->getname() <<"," <<p->getpopularity() << endl;
        p=p->getProx();
    }

}

//Funcao para a criacao e escrita do .bin
void ListaEncadeada::escreveBin(string arq3) {
    ofstream artistasbin;


    artistasbin.open(arq3,ios::binary);
    for(NoA *p=primeiro;p!=NULL;p=p->getProx())
    {

        Artista este;
        strcpy(este.id,p->getid().c_str());
        strcpy(este.genres,p->getgenres().c_str());
        strcpy(este.name,p->getname().c_str());
        este.popularity=p->getpopularity();
        este.followers=p->getfollowers();

        artistasbin.write((char *)&(este) ,sizeof(Artista));

    }
    
    artistasbin.close();
}

//Funcao para teste onde imprime todo o conteudo de .bin
void ListaEncadeada::imprimeBin()
{

    ifstream teste;

    teste.open("artists.bin",ios::binary);

    for(int i=0;i<n;i++)
    {
        Artista este;
        teste.read((char *) &(este),sizeof(Artista));
        cout << este.id << " ; " << este.followers<<" ; " << este.genres<< " ; " << este.name << " ; " << este.popularity << endl;
    }

    teste.close();
}

//Funcao utilizada pelo nosso menu no console para a impressao do vetor importado de .bin
void ListaEncadeada::imprimeTestes(vector <Artista> vetor){
    if(vetor.size() ==10){
        cout << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
        for(int i = 0; i < 10; i++){
                cout << "Id: "<< vetor[i].id << endl;
                cout << "Followers: " << vetor[i].followers<< endl;
                cout << "Genres: " << vetor[i].genres<< endl;
                cout << "Name: " << vetor[i].name << endl;
                cout << "Popularity: "  << vetor[i].popularity<< endl;
                cout << "===================================" <<endl;
                }
    }
    else if( vetor.size() == 100){
         ofstream arq("saidaArtists.txt");
         arq << "IMPORTACAO DE REGISTROS ALEATORIOS"<< endl;
         for(int i = 0; i < 100; i++){
                arq << "Id: "<< vetor[i].id << endl;
                arq << "Followers: " << vetor[i].followers<< endl;
                arq << "Genres: " << vetor[i].genres<< endl;
                arq << "Name: " << vetor[i].name << endl;
                arq << "Popularity: "  << vetor[i].popularity<< endl;
                arq << "===================================" <<endl;
                }
                cout<< "ARQUIVO GERADO COM SUCESSO!" << endl;
    }

}

//Funcao para verificar se existe repeticao dentro do vetor
bool verifica (vector<Artista> vetor, Artista aux)
{
    for (int i=0; i<vetor.size(); i++){
        if (vetor[i].id == aux.id)
            return true;        
    }
    return false;
}

//Funcao para importar de arquivo binario para vetor
void ListaEncadeada::importaBin(int tam) {

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
        if(verifica(vetor, aleatoria))
            i--; //Caso seja repetido, o for é executado novamente no mesmo valor de i
        else
            vetor.push_back(aleatoria); //Nao havendo repeticao, o vetor recebe a linha de .bin
    }
    
    artBin.close(); //Fecha .bin
    
    //Apos a criacao do vetor ser terminada, chama a funcao de impressao do vetor
    imprimeTestes(vetor);
}

void ListaEncadeada::NovaLista(string arq1)
{
    ///iniciacao das variaveis relativas ao artista
    ifstream artista;
    string id,genres,name,popularity,followers,l;
    int popularity_Int;
    float followers_Float;

    ///Abertura do file para a leitura
    artista.open(arq1, ios::in | ios::out);

    ///Verifica se ha problema na abertura do arquivo
    if  (artista.fail()) {
        cout << "> Erro na leitura de artists.csv" << endl;
        exit(1);
    }

    ///Descarta a primeira linha que nao contem informacoes
    getline(artista,l,'\n');

    ///Loop que se repete ate que todo o arquivo tenha sido percorrido e armazena as informacoes na lista
    while(artista.good()) {
        getline(artista,id,',');

        getline(artista ,followers,',');
        stringstream s(followers);
        s  >> followers_Float;   ///Transformando a string em um float

        getline(artista,l,'[');
        getline(artista,genres,']');
        getline(artista,l,',');


        getline(artista,name,',');

        getline(artista,popularity,'\n');
        stringstream ss(popularity);
        ss  >> popularity_Int;   ///Transformando a string em um int

        //Após leitura salva em nossa struct
        NovoArtista(id,followers_Float,genres,name,popularity_Int);
    }
    ///Fechamento do file
    artista.close();
    deletaultimo();

}
void ListaEncadeada::deletaultimo()
{
    NoA *p=ultimo->getAnt();
    delete ultimo;
    ultimo=p;
    ultimo->setProx(NULL);
    n--;
}
