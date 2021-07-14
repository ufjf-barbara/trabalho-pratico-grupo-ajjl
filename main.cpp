#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "MetodosOrdenacao.h"       // funcoes de ordenacao
#include "ListaEncadeada.h"         // estrutura de dados que armazena as informacoes dos artistas
#include "ListaEncadeadaTracks.h"   // estrutura de dados que armazena as informacoes das tracks
#include "TabelaHash.h" // tabela hash
#include "NoHash.h"

using namespace std;

/*
Comandos para compilar via terminal: 
    g++ *.cpp *.h -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/

void menu(string arq3, string arq4) { // Menu para selecionar as opcoes 
    int opcao;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Ordenacao" << endl;
        cout << " 2 - Hash" << endl;
        cout << " 3 - Modulo de Teste" << endl;
        cout << " 4 - Sair" << endl;
        cin >> opcao;
        if (opcao == 1) {
            cout << " Executando ordenacoes" << endl;
            MetodosOrdenacao ord;
            ord.ordenacoes(arq3); // Chama a execucao das ordenacoes
            cout << " Ordenacoes concluidas, resultados salvos em saida.txt" << endl;
            cout << endl;
        }
        else if (opcao == 2) {
            int M, N;
            cout << " Executando tabela Hash" << endl;
            cout << "Digite o valor de N: ";
            cin >> N;
            cout << "Digite o numero de artistas mais frequentes desejado: ";
            cin >> M;
            
            TabelaHash tabela(N*2);
            tabela.insereArtists(N,arq4, M, 1);
            cout << " Etapa concluida" << endl;
        }
        else if (opcao == 3) {
            int N = 700;
            cout << " Executando modulo de teste" << endl;
            int M;
            cout << "Digite o numero de artistas mais frequentes desejado: ";
            cin >> M;
            MetodosOrdenacao ord;
            ord.moduloTeste(arq3); // Chama a execucao do Modulo de Teste

            TabelaHash tabela(N*2);
            tabela.insereArtists(N,arq4, M, 2);

            cout << " Modulo teste concluido, resultados salvos em teste.txt" << endl;
            cout << endl;
        }
    }
    while(opcao != 4); // Sair
}

int main(int argc, char *argv[])
{
    ///Criacao das variaves para  manipulacao do .bin
    string diretorio=argv[1];
    string arq1 = diretorio + "/artists.csv";
    string arq2 = diretorio + "/tracks.csv";
    string arq3 = diretorio + "/artists.bin";
    string arq4 = diretorio + "/tracks.bin";
    
    ifstream testeArt;
    testeArt.open(arq3, ios::binary); // Abertura de artists.bin
    
    if  (testeArt.fail()){ // Se não foi encontrado .bin, então será processado um novo arquivo
        cout << "Arquivo artists.bin nao encontrado. Gerando um novo arquivo." << endl;
        ListaEncadeada ArtistsData;     //Classe criada para armazenar e manipular nossa struct
        ArtistsData.NovaLista(arq1);    // Cria nova lista
        ArtistsData.escreveBin(arq3);       //Funcao para criacao e escrita do arquivo .bin
    }
    testeArt.close();

    ifstream testeTrack;
    testeTrack.open(arq4, ios::binary); // Abertura de tracks.bin

    if  (testeTrack.fail()){ // Se não foi encontrado .bin, então será processado um novo arquivo
        cout << "Arquivo tracks.bin nao encontrado. Gerando um novo arquivo." << endl;
        ListaEncadeadaTracks TracksData;
        TracksData.NovaLista(arq2);
        TracksData.escreveBin(arq4);
    }
    testeTrack.close();
   
    menu(arq3, arq4); //Chamada para o menu

    return 0;
}
