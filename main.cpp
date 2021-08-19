#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ListaEncadeada.h"         // estrutura de dados que armazena as informacoes dos artistas
#include "ArvoreVP.h"
#include "ArvoreB.h"
using namespace std;

/*
Comandos para compilar via terminal: 
    g++ *.c* -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/

void analiseVermelhoPreto(string arq2){
    ListaEncadeada nova;
    vector<Artista> lista = nova.getAll(arq2);
    vector<Artista> aleatorios = nova.getAleatorios(100, arq2);
    ArvoreVP arvoreVP;

    ofstream arq("saida.txt");
    clock_t start, end;
    float tempo;

    start = clock();
    for (int i = 0; i < lista.size(); i++){ // percorrendo a lista de artistas
        arvoreVP.insere(lista[i]);
    }
    end = clock();
    tempo = (float)(end - start) / CLOCKS_PER_SEC;
    arq << "Tempo de inserção na árvore vermelho e preto: " << tempo << " seg" << endl;

    arq << "--------- ARVORE VERMELHO E PRETO ----------" << endl;

    float somaVP = 0;
    int comparacoesVP = 0;
    for (int i = 0; i < aleatorios.size(); i++){ // realizando a busca com 100 artistas aleatorios
        int local = -100;
        string codigo;

        start = clock();
        arvoreVP.busca(aleatorios[i].name, &local, &codigo);
        end = clock();        
        tempo = (float)(end - start) / CLOCKS_PER_SEC;

        somaVP += tempo;
        arq << i+1 << "°)" <<" busca em " << tempo << " seg, com " << arvoreVP.comparacoes  << " comparações."<< endl;
        comparacoesVP += arvoreVP.comparacoes;
        arvoreVP.comparacoes = 0;
    }
    arq << "Média do tempo de busca na árvore vermelho e preto: " << (somaVP/aleatorios.size())
    << " seg, com " << comparacoesVP << " comparações." << endl;
    arq << "----------------------------------------------------- \n\n" << endl;
}

void analiseArvoreB(string arq2) {
    ListaEncadeada nova;
    vector<Artista> lista = nova.getAll(arq2);
    vector<Artista> aleatorios = nova.getAleatorios(100, arq2);

    ArvoreB arvoreBmenor(20, arq2);
    ArvoreB arvoreBmaior(200, arq2);

    ofstream arq("saida.txt");
    clock_t start, end;
    float tempo;

    start = clock();
    for (int i = 0; i < lista.size(); i++){ // percorrendo a lista de artistas
        arvoreBmenor.insere(lista[i].name, lista[i].local, lista[i].id);
    }
    end = clock();
    tempo = (float)(end - start) / CLOCKS_PER_SEC;
    arq << "Tempo de inserção na árvore B(20): " << tempo << " seg" << endl;

    start = clock();
    for (int i = 0; i < lista.size(); i++){ // percorrendo a lista de artistas
        arvoreBmaior.insere(lista[i].name, lista[i].local, lista[i].id);
    }
    end = clock();
    tempo = (float)(end - start) / CLOCKS_PER_SEC;
    arq << "Tempo de inserção na árvore B(200): " << tempo << " seg" << endl;
    arq << "------------------------------------------------ \n\n" << endl;

    float somaBmenor = 0;
    int comparacoesBmenor = 0;
    for (int i = 0; i < aleatorios.size(); i++){ // realizando a busca com 100 artistas aleatorios
        int local = -100;
        string codigo;

        start = clock();
        arvoreBmenor.Busca(aleatorios[i].name, &local, &codigo);
        end = clock();
        tempo = (float)(end - start) / CLOCKS_PER_SEC;

        somaBmenor += tempo;
        arq << i+1 << "°)" <<" busca na árvore B(20): " << tempo << " seg, com " << arvoreBmenor.comparacoes  << " comparações."<< endl;
        comparacoesBmenor += arvoreBmenor.comparacoes;
        arvoreBmenor.comparacoes = 0;
    }
    arq << "Média do tempo de busca na árvore B(20): " << (somaBmenor/aleatorios.size()) << " seg, com " << comparacoesBmenor << " comparações." << endl;
    arq << "------------------------------------------------ \n\n" << endl;


    float somaBmaior = 0;
    int comparacoesBmaior = 0;
    for (int i = 0; i < aleatorios.size(); i++){ // realizando a busca com 100 artistas aleatorios
        int local = -100;
        string codigo;

        start = clock();
        arvoreBmaior.Busca(aleatorios[i].name, &local, &codigo);
        end = clock();
        tempo = (float)(end - start) / CLOCKS_PER_SEC;

        somaBmaior += tempo;
        arq << i+1 << "°)" <<" busca na árvore B(200): " << tempo << " seg, com " << arvoreBmaior.comparacoes  << " comparações."<< endl;
        comparacoesBmaior += arvoreBmaior.comparacoes;
        arvoreBmaior.comparacoes = 0;
    }
    arq << "Média do tempo de busca na árvore B(200): " << (somaBmaior/aleatorios.size()) << " seg, com " << comparacoesBmaior << " comparações." << endl;
    arq << "------------------------------------------------ \n\n" << endl;
}

void menuPrincipal (string arq2) {
    ListaEncadeada nova;
    vector<Artista> lista = nova.getAll(arq2);
    Artista aux;
    ifstream artBin;
    artBin.open(arq2,ios::binary); // Abre artists.bin

    int op=0, escolha=0;
    do {
        cout << "MENU PRINCIPAL" << endl;
        cout << "1 - Arvore Vermelho-Preta" << endl;
        cout << "2- Arvore B" << endl;
        cout << "3- SAIR" << endl;
        cout << "Digite: ";
        cin >> op;

    while(op != 3 && escolha != 3) {
        cout << "ESCOLHA UMA OPCAO" << endl;
        cout << "1- Modo de analise" << endl;
        cout << "2- Modo de teste" << endl;
        cout << "3- SAIR" << endl;
        cout << "Digite: ";
        cin >> escolha;

        if(op == 1 && escolha == 1){
            cout << "Gerando arquivo..." << endl;
            analiseVermelhoPreto(arq2);
            cout << "Arquivo 'saida.txt' gerado" << endl;
        }
        
        else if(op == 2 && escolha == 1){
            cout << "Gerando arquivo..." << endl;
            analiseArvoreB(arq2);
            cout << "Arquivo 'saida.txt' gerado" << endl;
        }

        else if(op == 1 && escolha == 2){
            string nome, codigo;
            int local = -100;
            cout << "Preenchendo a arvore..." << endl;
            ArvoreVP arvoreVP;
            for (int i = 0; i < lista.size(); i++){ // percorrendo a lista de artistas
                arvoreVP.insere(lista[i]);
            }
            cout << "Digite o nome do artista: ";
            cin >> nome;

            if(arvoreVP.busca(nome, &local, &codigo)) {  
                artBin.seekg(local); // Posiciona o ponteiro em .bin
                artBin.read((char *) &(aux),sizeof(Artista)); //Le conteudo da linha em .bin
                cout << "Nome: " << aux.name << ", popularity: " << aux.popularity << ", genres: "
                << aux.genres << " , id: " << aux.id << " , followers: " << aux.followers << endl;
            }  
            else
                cout << endl << "nao encontrado" << endl;
        }

        else if(op ==2 && escolha == 2){
            int ordem;
            cout << "Digite a ordem minima da arvore: ";
            cin >> ordem;

            string nome, codigo;
            int local = -100;
            cout << "Preenchendo a arvore..." << endl;
            ArvoreB arvoreB(ordem, arq2);
            for (int i = 0; i < lista.size(); i++){ // percorrendo a lista de artistas
                arvoreB.insere(lista[i].name, lista[i].local, lista[i].id);
            }
            cout << "Digite o nome do artista: ";
            cin >> nome;
            if(arvoreB.Busca(nome, &local, &codigo)) {  
                artBin.seekg(local); // Posiciona o ponteiro em .bin
                artBin.read((char *) &(aux),sizeof(Artista)); //Le conteudo da linha em .bin
                cout << "Nome: " << aux.name << ", popularity: " << aux.popularity << ", genres: "
                << aux.genres << " , id: " << aux.id << " , followers: " << aux.followers << endl;                }  
            else
                cout << endl << "nao encontrado" << endl;
        }
        }  
    } while (op != 3 );
    artBin.close(); //Fecha .bin 
}



int main(int argc, char *argv[])
{
    ///Criacao das variaves para  manipulacao do .bin
    string diretorio=argv[1];
    string arq1 = diretorio + "/artists.csv";
    string arq2 = diretorio + "/artists.bin";

    
    ifstream testeArt;
    testeArt.open(arq2, ios::binary); // Abertura de artists.bin
    
    if  (testeArt.fail()){ // Se não foi encontrado .bin, então será processado um novo arquivo
        cout << "Arquivo artists.bin nao encontrado. Gerando um novo arquivo." << endl;
        ListaEncadeada ArtistsData;     //Classe criada para armazenar e manipular nossa struct
        ArtistsData.NovaLista(arq1);    // Cria nova lista
        ArtistsData.escreveBin(arq2);       //Funcao para criacao e escrita do arquivo .bin
    }
    testeArt.close();
    menuPrincipal(arq2);

    return 0;
}
