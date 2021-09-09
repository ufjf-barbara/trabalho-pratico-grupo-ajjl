#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "CasamentoPadrao.h"


using namespace std;


/*
Comandos para compilar via terminal: 
    g++ *.c* -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/

string nomeSequencia(int indice){ 
        string tes = "dna";
        tes += (indice+1) + '0';
        tes += ".txt";
        return tes;
}

string nomePadrao(int indice){ 
        string tes = "padrao";
        tes += (indice+1) + '0';
        tes += ".txt";
        return tes;
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

void submenuCasamento(int qtSeq, int qtPadrao){ 
     int opcao;
     CasamentoPadrao padrao;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Forca bruta" << endl;
        cout << " 2 - KMP" << endl;
        cout << " 3 - BHM" << endl;
        cout << " 4 - Voltar" << endl;
        cin >> opcao;
        if (opcao == 1) {
            cout << "Executando método Forca Bruta..." << endl;
            for (int i = 0; i < qtSeq; i++){
                string sequenciaT = leArquivoTexto(nomeSequencia(i));
                for (int j = 0; j < qtPadrao; j++)
                {
                    string padraoP = leArquivoTexto(nomePadrao(j));
                    padrao.ForcaBruta(sequenciaT, padraoP);
                }
            }
                cout << "Etapa concluida!" << endl;
        }
        else if (opcao == 2) {
            cout << " Executando método KMP..." << endl;
            for (int i = 0; i < qtSeq; i++){
                string sequenciaT = leArquivoTexto(nomeSequencia(i));
                for (int j = 0; j < qtPadrao; j++)
                {
                    string padraoP = leArquivoTexto(nomePadrao(j));
                    padrao.KMP(sequenciaT, padraoP);
                }
            }

            cout << "Etapa concluida!" << endl;
        }
        else if (opcao == 3) {
            cout << " Executando método BHM..." << endl;
            for (int i = 0; i < qtSeq; i++){
                string sequenciaT = leArquivoTexto(nomeSequencia(i));
                for (int j = 0; j < qtPadrao; j++)
                {
                    string padraoP = leArquivoTexto(nomePadrao(j));
                    padrao.BHMsearch(sequenciaT, padraoP);
                }
            }

            cout << "Etapa concluida!" << endl;
        }
    } while (opcao != 4);
}

void menu(int qtSeq, int qtPadrao) { // Menu para selecionar as opcoes 
    int opcao;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Casamento de padrao" << endl;
        cout << " 2 - Metodo de Compressao" << endl;
        cout << " 3 - Sair" << endl;
        cin >> opcao;
        if (opcao == 1) {
            submenuCasamento(qtSeq, qtPadrao);
        }
        else if (opcao == 2) {
            cout<< "chamadas compressao" << endl;
            cout << " Etapa concluida" << endl;
        }
    }
    while(opcao != 3); // Sair
}



/* void leArquivoPadrao(string arquivo, string *sequenciaP)
{
    ifstream arq(arquivo);
    string str;
    int c = 0;
    if(arq.is_open()){
        while (c < 3)
        {
            getline(arq, str);
            sequenciaP[c] = str;
            [0] = "accccttp"
            [1] = "asdasdas"
            c ++;
        }
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    arq.close();
    return aux;
} */

int main() // ./main <caminhoSeq> <qntArqSeq> <caminhoPad> <qntArqPad>
{
    //string caminhoSeq = argv[1]; 
    //string qtTStr = argv[2];
    //int qtSeq = stoi(qtTStr);
    //string padraoP = argv[2];
    //string qtPStr = argv[4];
    //int qtP = stoi(qtPStr);
    
    // string arquivo= "dna1.txt";
    // string sequenciaT = leArquivoTexto(arquivo);
    // menu();

   // arquivo= "padrao.txt";
    // string padraoP = leArquivoTexto(arquivo);
    // CasamentoPadrao padrao;
    // cout << "Forca Bruta" << endl;
    // padrao.ForcaBruta(sequenciaT, "tttac");
    // cout << "BHM" << endl;
    // padrao.BHMsearch(sequenciaT, "tttac");
    // cout << "KMP" << endl;
    // padrao.KMP(sequenciaT, "tttac");
    int qtPadrao;
    int qtSeq;
    cout << "Digite o numero de sequencias a serem lidas: ";
    cin >> qtSeq;
    cout << "Digite o numero de padroes a serem lidos: ";
    cin >> qtPadrao;
    menu(qtSeq, qtPadrao);

    return 0;
}
