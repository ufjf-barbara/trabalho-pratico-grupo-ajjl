#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include "CasamentoPadrao.h"
#include "HuffmanTree.h"


using namespace std;


/*
Comandos para compilar via terminal: 
    g++ *.c* -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl/src/etapa4
*/

string nomesequencia(string diretorio, int indice){
    string nome = diretorio;
    nome += "/dna";
    nome += (indice + 1) + '0';
    nome += ".txt";
    return nome;
}

string nomePadrao(string diretorio, int indice){
    string nome = diretorio;
    nome += "/padrao";
    nome += (indice + 1) + '0';
    nome += ".txt";
    return nome;
}

string leArquivoTexto(string arquivo)
{
    ifstream arq(arquivo);
    string str,aux, skip;
    if(arq.is_open())
    {
        getline(arq, skip);
        getline(arq, skip);
        while (getline(arq, str))
        {
            aux+=str;
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    arq.close();

    return aux;
}

void submenuCasamento(string diretorio, int qtSeq, int qtPadrao){ 
     int opcao;
     CasamentoPadrao padrao;
     clock_t start, end;
     float tempo;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Forca bruta" << endl;
        cout << " 2 - KMP" << endl;
        cout << " 3 - BMH" << endl;
        cout << " 4 - Voltar" << endl;
        cin >> opcao;

        if(opcao != 4){
            for (int i = 0; i < qtSeq; i++){
                string nomeArqsequencia = nomesequencia(diretorio, i);
                string sequenciaT = leArquivoTexto(nomeArqsequencia);
                cout << "Sequencia DNA " << i+1 << " (tamanho " << sequenciaT.length() << "): " << endl;
                for (int j = 0; j < qtPadrao; j++)
                {
                    string nomeArqPadrao = nomePadrao(diretorio, j);
                    string padraoP = leArquivoTexto(nomeArqPadrao);
                    cout << endl << "Padrao " << j+1 << " (tamanho " << padraoP.length() << "): " << endl;
                    
                    if(opcao == 1){
                        cout << "   Forca Bruta:" << endl;
                        start = clock();
                        padrao.ForcaBruta(sequenciaT, padraoP);
                        end = clock();
                    }
                    else if (opcao == 2){
                        cout << "   KMP:" << endl;
                        start = clock();
                        padrao.KMP(sequenciaT, padraoP);
                        end = clock();
                    }
                    else if (opcao == 3){
                        cout << "   BMH:" << endl;
                        start = clock();
                        padrao.BMHsearch(sequenciaT, padraoP);
                        end = clock();
                    }
                    tempo = (float)(end - start) / CLOCKS_PER_SEC;
                    cout << "   - Tempo: " << tempo << "s" << endl;
                }
                    cout << endl << "--------------------" << endl << endl;
            }
        }
    } while (opcao != 4);
}

void submenuCompressao(string diretorio, int qtSeq){
    for (int i = 0; i < qtSeq; i++){
        string nomeArqsequencia = nomesequencia(diretorio, i);
        string sequenciaT = leArquivoTexto(nomeArqsequencia);
        clock_t start, end;
        
        cout << "Sequencia DNA " << i+1 << " (tamanho " << sequenciaT.length() << "): " << endl;

        HuffmanTree compressao(sequenciaT, sequenciaT.length());
        compressao.percorreraux();
        start = clock();
        compressao.comprimir();
        compressao.descomprimir2();
        end = clock();
        cout << "Taxa de compressao: " << compressao.TaxaComprecao() << "%" << endl;
        cout << "Tempo: " << (float)(end - start) / CLOCKS_PER_SEC << "s" << endl;
        cout << endl << "--------------------" << endl << endl;
    }    
}

void menu(string diretorio, int qtSeq, int qtPadrao) { // Menu para selecionar as opcoes 
    int opcao;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Casamento de padrao" << endl;
        cout << " 2 - Metodo de Compressao" << endl;
        cout << " 3 - Sair" << endl;
        cin >> opcao;
        if (opcao == 1) {
            submenuCasamento(diretorio, qtSeq, qtPadrao);
        }
        else if (opcao == 2) {
            submenuCompressao(diretorio, qtSeq);
        }
    }
    while(opcao != 3); // Sair
}

int main(int argc, char *argv[]) // ./main <caminhoSeq>
{
    int qtPadrao, qtSeq;
    string diretorio = argv[1];

    cout << "Digite o numero de sequencias a serem lidas: ";
    cin >> qtSeq;
    cout << "Digite o numero de padroes a serem lidos: ";
    cin >> qtPadrao;
    menu(diretorio, qtSeq, qtPadrao);

    return 0;
}
