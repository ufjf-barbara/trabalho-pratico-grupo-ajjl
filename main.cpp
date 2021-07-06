#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ListaEncadeada.h"         // estrutura de dados que armazena as informacoes dos artistas
#include "ListaEncadeadaTracks.h"   // estrutura de dados que armazena as informacoes das tracks

using namespace std;

/*
Comandos para compilar via terminal: 
    g++ *.cpp *.h -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/

/// Esta é a função que utilizaremos para o menu de opcoes do console
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


    //ArtistsData.imprimeIds();  ///Funcao para teste onde imprime todo o conteudo da lista
    //ArtistsData.imprimeBin(); ///Funcao para teste onde imprime todo o conteudo de .bin

    /// =============================================

    /// Manipulacao de Tracks onde segue de forma analoga ao Artists


    ListaEncadeadaTracks TracksData;
    TracksData.NovaLista(arq2);
    TracksData.escreveBin();


    //TracksData.imprimeBin(); ///Funcao para teste onde imprime todo o conteudo de .bin
    //TracksData.imprimeIds(); /// ///Funcao para teste onde imprime todo o conteudo da lista

    moduloDeTestes(ArtistsData, TracksData);

    return 0;
}

    return 0;
}
