#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ListaEncadeada.h"         // estrutura de dados que armazena as informacoes dos artistas
#include "ArvoreVP.h"

using namespace std;

/*
Comandos para compilar via terminal: 
    g++ *.c* -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/



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

    ArvoreVP tree;
    tree.start(arq2); // provisorio ate ter menu

    int local = 0;
    string codigo;
    
    if(tree.busca("Tuviel Levi", &local, &codigo)) {  
        cout << local << " " << codigo << endl;
    }  
    else
        cout << endl << "nao encotrado" << endl;

    return 0;
}
