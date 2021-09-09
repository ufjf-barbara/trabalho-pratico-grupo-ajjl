#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;


/*
Comandos para compilar via terminal: 
    g++ *.c* -o main
    ./main SEU/DIRETORIO/trabalho-pratico-grupo-ajjl
*/
void submenuCasamento(){ 
     int opcao;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Forca bruta" << endl;
        cout << " 2 - KMP" << endl;
        cout << " 3 - BHM" << endl;
        cout << " 4 - Voltar" << endl;
        cin >> opcao;
        if (opcao == 1) {
            cout << "Executando método Forca Bruta..." << endl;

            cout << "Etapa concluida!" << endl;
        }
        else if (opcao == 2) {
            cout << " Executando método KMP..." << endl;

            cout << "Etapa concluida!" << endl;
        }
        else if (opcao == 3) {
            cout << " Executando método BHM..." << endl;

            cout << "Etapa concluida!" << endl;
        }
    } while (opcao != 4);
}

void menu() { // Menu para selecionar as opcoes 
    int opcao;
    do{
        cout << "Executar qual etapa?" << endl;
        cout << " 1 - Casamento de padrao" << endl;
        cout << " 2 - Metodo de Compressao" << endl;
        cout << " 3 - Sair" << endl;
        cin >> opcao;
        if (opcao == 1) {
            submenuCasamento();
        }
        else if (opcao == 2) {
            cout<< "chamadas compressao" << endl;
            cout << " Etapa concluida" << endl;
        }
    }
    while(opcao != 3); // Sair
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

void ForcaBruta(string T, string P){
    int tamT = T.length();
    int tamP = P.length();
    int ocorrencias = 0;
    for(int i = 0; i <= (tamT-tamP); i++){
        int k = i;
        int j = 0;
        while(T[k] == P[j]){
            j ++;
            k ++;
            if(j==tamP){
                //cout << "Casamento na posicao: " << i << endl;
                ocorrencias ++;
                break;
            }
        }
    }
    cout << "Numero total de ocorrencias ----> " << ocorrencias << endl;
}

void BHMsearch(string sequenciaT, string padraoP){
    int sequenciaSize = sequenciaT.length();
    int padraoSize = padraoP.length();
    int d[256], j, k;
    int ocorrencias = 0;
    // inicializacao da tabela de deslocamentos
    for(int j=0; j<= 256; j++)
        d[j] = padraoSize;
    for(int j=1; j< padraoSize;j++)
        d[padraoP[j - 1]] = padraoSize - j;

    // fase de pesquisa
    for (int i = padraoSize; i <= sequenciaSize; i += d[sequenciaT[i - 1]])
    {
        for(j = padraoSize, k = i; sequenciaT[k-1] == padraoP[j-1] && j>0; j--)
            k--;
        if(j == 0){
            ocorrencias++;
            //cout << "Casamento na posicao: " << k << endl;
        }
    }
    cout << "Numero total de ocorrencias ----> " << ocorrencias << endl;
}

void prefixo(string P, int tamP, int* lps){
	lps[0] = 0; 
	int j = 0;
	int i = 1;
	while (i < tamP) {
		if (P[i] == P[j]) {
			j++;
			lps[i] = j;
			i++;
		}
		else {
			if (j != 0) 
				j = lps[j - 1];
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
}

void KMP(string T, string P){
	int tamT = T.length();
    int tamP = P.length();
	int* lps = new int [tamP];
    int ocorrencias = 0;

	prefixo(P, tamP, lps);

	int i = 0; 
	int j = 0;
	while (i < tamT) {
		if (P[j] == T[i]) {
			j++;
			i++;
		}
		if (j == tamP) {
			//cout << "Casamento na posicao: " << i-j << endl;
            ocorrencias ++;
			j = lps[j-1];
		}
		else if (i < tamT && P[j] != T[i]) {
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
    cout << "Numero total de ocorrencias ----> " << ocorrencias << endl;
}


int main() // ./main <caminhoSeq> <qntArqSeq> <caminhoPad> <qntArqPad>
{
    //string caminhoSeq = argv[1]; 
    //string qtTStr = argv[2];
    //int qtSeq = stoi(qtTStr);
    //string padraoP = argv[2];
    //string qtPStr = argv[4];
    //int qtP = stoi(qtPStr);
    
    string arquivo= "dna1.txt";
    string sequenciaT = leArquivoTexto(arquivo);
    // menu();
    // cout << sequenciaT << endl;

    arquivo= "padrao.txt";
    string padraoP = leArquivoTexto(arquivo);
    cout << "Forca Bruta" << endl;
    ForcaBruta(sequenciaT, "tttac");
    cout << "BHM" << endl;
    BHMsearch(sequenciaT, "tttac");
    cout << "KMP" << endl;
    KMP(sequenciaT, "tttac");

    string tes = "padrao";
    tes += 1 + '0';
    tes += ".txt";
    cout << "STRING " << tes << endl;

    // auto s = std::format("padrao{}", 1); 
    // cout << "res " << s;
    // string test = string.Format("padrao{}", 1);
    //   std::cout << fmt::format("padrao{}", 1);

    // cout << "res " << test;


    return 0;
}
