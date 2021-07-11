#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "MetodosOrdenacao.h"       // funcoes de ordenacao
#include "ListaEncadeada.h"         // estrutura de dados que armazena as informacoes dos artistas
#include "ListaEncadeadaTracks.h"   // estrutura de dados que armazena as informacoes das tracks

using namespace std;

/*
Comandos para compilar via terminal: 
    g++ *.cpp *.h -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/

/// Menu da parte 1 do trabalho
/*
void moduloDeTestes(ListaEncadeada ArtistsData, ListaEncadeadaTracks TracksData){ 
    int opcao, tam, op;
    do{
        cout << "1 - MODULO DE TESTES" << endl;
        cout << "2 - SAIR" << endl;
        cin  >> opcao;
        if(opcao == 1){
            cout << "Informe o tamanho da entrada: ";  ///Informe 10 para saida em console ou 100 para saida em .txt
            cin  >> tam;
            if(tam == 10 || tam == 100){
                cout << "Deseja importar do arquivo tracks ou artists?" << endl;
                cout << "1- TRACKS" << endl;
                cout << "2- ARTISTS" << endl;
                cin  >> op;
                if(op == 1)
                    TracksData.importaBin(tam); ///Funcao que importa de .bin e salva em um vetor
                else if( op == 2 )
                    ArtistsData.importaBin(tam);
                else
                    cout << "OPCAO INVALIDA!"<< endl;
            }
            else
                cout <<"TAMANHO DE ENTRADA INVÁLIDA! ESCOLHA N=10 OU N=100"<<endl;
        }
    }
    while(opcao != 2);
}
*/

void menu(){
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
            ordenaQuick();
            ordenaHeap();
            ordenaMerge();
            cout << " Etapa concluida, resultados salvos em saida.txt" << endl;
        }
        else if (opcao == 2) {
            cout << " Executando tabela Hash" << endl;
            tabelaHash();
            cout << " Etapa concluida" << endl;
        }
        else if (opcao == 3) {
            cout << " Executando modulo de teste" << endl;
            moduloTeste ();
            cout << " Etapa concluida, resultados salvos em teste.txt" << endl;
        }
        else {
            cout << " Opcao invalida" << endl;
            menu();
        }
    }
    while(opcao != 4);
}

int main(int argc, char *argv[])
{
    ///Criacao das variaves para  manipulacao do .csv
    string diretorio=argv[1];
    string arq1= diretorio + "/artists.csv";
    string arq2= diretorio + "/tracks.csv";
    
    
    /// Manipulacao de Artists:
    ListaEncadeada ArtistsData; ///Classe criada para armazenar e manipular nossa struct
    ArtistsData.NovaLista(arq1);
    ArtistsData.escreveBin();///Funcao para criacao e escrita do arquivo .bin

    /// =============================================

    /// Manipulacao de Tracks onde segue de forma analoga ao Artists
    ListaEncadeadaTracks TracksData;
    TracksData.NovaLista(arq2);
    TracksData.escreveBin();

    menu();

    return 0;
}
