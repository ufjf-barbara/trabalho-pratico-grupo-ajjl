#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "CasamentoPadrao.h"

using namespace std;

void CasamentoPadrao::ForcaBruta(string T, string P){
    int tamT = T.length(); // Tamanho da sequencia de DNA
    int tamP = P.length(); // Tamanho do padrao para busca
    int ocorrencias = 0; // Contador de ocorrencias
    for(int i = 0; i <= (tamT-tamP); i++){ // Enquanto posicao < (TamanhoDNA - TamanhoPadrao)
        int k = i; // Percorre posicao na sequencia
        int j = 0; // Percorre posicao no padrao
        while(T[k] == P[j]){ //Enquanto forem iguais
            j ++;
            k ++;
            if(j==tamP){  // Se completou tamanho do padrao
                cout << "   - Casamento na posicao: " << i << endl;
                ocorrencias ++;
                break;
            }
        }
    }
    cout << "   - Total de ocorrencias ----> " << ocorrencias << endl;
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

void CasamentoPadrao::KMP(string T, string P){
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
			cout << "   - Casamento na posicao: " << i-j << endl;
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
    cout << "   - Total de ocorrencias ----> " << ocorrencias << endl;
}

void CasamentoPadrao::BMHsearch(string sequenciaT, string padraoP){
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
            cout << "    - Casamento na posicao: " << k << endl;
        }
    }
    cout << "   - Total de ocorrencias ----> " << ocorrencias << endl;
}