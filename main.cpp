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
void menuAntigo(ListaEncadeada ArtistsData, ListaEncadeadaTracks TracksData){ 
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

void menu(MetodosOrdenacao aux, string arq3, string arq4){
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
            aux.ordenacoes(arq3);
            cout << " Etapa concluida, resultados salvos em saida.txt" << endl;
        }
        else if (opcao == 2) {
            cout << " Executando tabela Hash" << endl;
            //FUNCAO DA TABELA HASH AQUI
            cout << " Etapa concluida" << endl;
        }
        else if (opcao == 3) {
            cout << " Executando modulo de teste" << endl;
            aux.moduloTeste(arq3, arq4);
            cout << " Etapa concluida, resultados salvos em teste.txt" << endl;
            cout << " " << endl;
        }
    }
    while(opcao != 4);
}

int main(int argc, char *argv[])
{
    ///Criacao das variaves para  manipulacao do .bin
    string diretorio=argv[1];
    string arq1= diretorio + "/artists.csv";
    string arq2= diretorio + "/tracks.csv";
    string arq3= diretorio + "/artists.bin";
    string arq4= diretorio + "/tracks.bin";
    
    ifstream testeArt;
    testeArt.open(arq3, ios::binary);
    
    if  (testeArt.fail()){
        cout << "Arquivo artists.bin nao encontrado. Gerando um novo arquivo." << endl;
        
        ListaEncadeada ArtistsData; ///Classe criada para armazenar e manipular nossa struct
        ArtistsData.NovaLista(arq1);    // Cria nova lista
        ArtistsData.escreveBin();   ///Funcao para criacao e escrita do arquivo .bin
    }
    testeArt.close();

    ifstream testeTrack;
    testeTrack.open(arq4, ios::binary);

    if  (testeTrack.fail()){
        cout << "Arquivo tracks.bin nao encontrado. Gerando um novo arquivo." << endl;
        
        ListaEncadeadaTracks TracksData;
        TracksData.NovaLista(arq2);
        TracksData.escreveBin();
    }
    testeTrack.close();

    //menuAntigo(ArtistsData, TracksData);
    
    MetodosOrdenacao aux;
    menu(aux, arq3, arq4);

    return 0;
}
