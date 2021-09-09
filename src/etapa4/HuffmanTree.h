#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "HuffmanNode.h"
#include <string>

using namespace std;
class HuffmanTree
{
    public:
        HuffmanTree(string Dna,int tam);
        ~HuffmanTree();
        void percorreraux();
        void comprimir();
        void comprimir2();
        void descomprimir2();
        void descomprimir();


    private:
        string DNA;
        int tamanho;
        HuffmanNode *Raiz;

        unsigned int *compact;
        int QuantidadeDeInt;

        string caminhoC;
        string caminhoG;
        string caminhoT;
        string caminhoA;

        int TamanhoDaFila;
        HuffmanNode *FilaPrioridade[4];

        int quantidadeC;
        int quantidadeG;
        int quantidadeT;
        int quantidadeA;

        void contar();
        void iniciarNode(HuffmanNode *No,char data,long long int frequencia,bool folha);

        void percorrer(HuffmanNode *No, string Caminho);

        void troca(HuffmanNode *x,HuffmanNode *y);
        void juntar();

        void del(HuffmanNode *No);

        float TaxaComprecao();
};

#endif // HUFFMANTREE_H
