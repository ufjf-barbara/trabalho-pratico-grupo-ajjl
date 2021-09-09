#include "HuffmanTree.h"
#include "HuffmanNode.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

HuffmanTree::HuffmanTree(string Dna,int tam)
{
    tamanho=tam;
    DNA=Dna;

    quantidadeC=0;
    quantidadeG=0;
    quantidadeT=0;
    quantidadeA=0;
    TamanhoDaFila=4;

    contar();

}

HuffmanTree::~HuffmanTree()
{
    delete compact;
    del(Raiz);
}
void HuffmanTree::del(HuffmanNode *No)
{
    if (No!=NULL)
    {
        del(No->direita);
        del(No->esquerda);
        delete No;
    }


}

void HuffmanTree::contar()
{
    for(int i=0;i<tamanho;i++)
    {
        if(DNA[i]=='c')
            quantidadeC++;

        else if(DNA[i]=='g')
            quantidadeG++;

        else if(DNA[i]=='t')
            quantidadeT++;

        else if(DNA[i]=='a')
            quantidadeA++;
    }
    HuffmanNode *NoC=new HuffmanNode;
    HuffmanNode *NoG=new HuffmanNode;
    HuffmanNode *NoT=new HuffmanNode;
    HuffmanNode *NoA=new HuffmanNode;

    iniciarNode(NoC,'c',quantidadeC++,1);
    iniciarNode(NoG,'g',quantidadeG++,1);
    iniciarNode(NoT,'t',quantidadeT++,1);
    iniciarNode(NoA,'a',quantidadeA++,1);

    FilaPrioridade[0]=NoC;
    FilaPrioridade[1]=NoG;
    FilaPrioridade[2]=NoT;
    FilaPrioridade[3]=NoA;

    int i,j;
    for (i=0;i<TamanhoDaFila-1;i++)
        for (j=0;j<TamanhoDaFila-i-1;j++)
            if (FilaPrioridade[j]->frequencia > FilaPrioridade[j+1]->frequencia)
                troca(FilaPrioridade[j], FilaPrioridade[j+1]);

    juntar();

}
void HuffmanTree::iniciarNode(HuffmanNode *No,char data,long long int frequencia,bool folha)
{
    No->direita=NULL;
    No->esquerda=NULL;
    No->data=data;
    No->frequencia=frequencia;
    No->folha=folha;
}
void HuffmanTree::troca(HuffmanNode *x,HuffmanNode *y)
{
    HuffmanNode temp = *x;
    *x = *y;
    *y = temp;
}

void HuffmanTree::juntar()
{
    //junta de forma iterativa todos os nos iniciais da arvore

    HuffmanNode *No1=new HuffmanNode;
    iniciarNode(No1,'\0',FilaPrioridade[0]->frequencia+FilaPrioridade[1]->frequencia,0);  //o vetor � ordenado de forma que os nos com menor frequencia est�o no inicio, juntando-os pirmeiro
    No1->esquerda=FilaPrioridade[0];
    No1->direita=FilaPrioridade[1];

    FilaPrioridade[0]=No1;
    FilaPrioridade[1]=FilaPrioridade[TamanhoDaFila-1];

    TamanhoDaFila--;

    //ordena os novos nos;
    int i,j;
    for (i=0;i<TamanhoDaFila-1;i++)
        for (j=0;j<TamanhoDaFila-i-1;j++)
            if (FilaPrioridade[j]->frequencia > FilaPrioridade[j+1]->frequencia)
                troca(FilaPrioridade[j], FilaPrioridade[j+1]);

    //o processo se repete 3 vezes
    //****************************************************************************************************//

    HuffmanNode *No2 =new HuffmanNode;
    iniciarNode(No2,'\0',FilaPrioridade[0]->frequencia+FilaPrioridade[1]->frequencia,0);
    No2->esquerda=FilaPrioridade[0];
    No2->direita=FilaPrioridade[1];

    FilaPrioridade[0]=No2;
    FilaPrioridade[1]=FilaPrioridade[TamanhoDaFila-1];

    TamanhoDaFila--;

    for (i=0;i<TamanhoDaFila-1;i++)
        for (j=0;j<TamanhoDaFila-i-1;j++)
            if (FilaPrioridade[j]->frequencia > FilaPrioridade[j+1]->frequencia)
                troca(FilaPrioridade[j], FilaPrioridade[j+1]);

    //****************************************************************************************************//

    HuffmanNode *No3 =new HuffmanNode;
    iniciarNode(No3,'\0',FilaPrioridade[0]->frequencia+FilaPrioridade[1]->frequencia,0);
    No3->esquerda=FilaPrioridade[0];
    No3->direita=FilaPrioridade[1];

    FilaPrioridade[0]=No3;
    TamanhoDaFila--;

    Raiz=No3;   //o no com o somatorio de todas as frequencias � nomiado raiz

}
void HuffmanTree::percorreraux()
{
    //inicia o mapeamento
    string caminho;
    percorrer(Raiz,caminho);

}


void HuffmanTree::percorrer(HuffmanNode *No, string Caminho)
{
    //percorre toda a arvore achando as folhas e mapeando o caminho para cada caractere
    if(No->folha==0)
    {
        percorrer(No->esquerda,Caminho+"0");
        percorrer(No->direita,Caminho+"1");
    }
    if(No->folha==1)
    {
        if(No->data=='a')
            caminhoA=Caminho;

        else if(No->data=='c')
            caminhoC=Caminho;

        else if(No->data=='t')
            caminhoT=Caminho;

        else if(No->data=='g')
            caminhoG=Caminho;
    }
}

void HuffmanTree::comprimir()
{
    ofstream comprimido;
    comprimido.open("comprimido.txt");

    for(int i=0;i<tamanho;i++)
    {
        if(DNA[i]=='a')
            comprimido<<caminhoA;
        else if(DNA[i]=='t')
            comprimido<<caminhoT;
        else if(DNA[i]=='g')
            comprimido<<caminhoG;
        else if(DNA[i]=='c')
        {
            comprimido<<caminhoC;
        }
    }
    comprimido.close();
    comprimir2();
}
void HuffmanTree::comprimir2()
{

    ifstream Comprimir;
    Comprimir.open("comprimido.txt");

    string convertendo;
    getline(Comprimir,convertendo);

    Comprimir.close();

    QuantidadeDeInt=(convertendo.size()/32)+1;

    unsigned int *n= new unsigned int [QuantidadeDeInt];

    memset(n,0,sizeof(int)*QuantidadeDeInt);

    long long int y=0;
    for(int i=0;i<QuantidadeDeInt;i++)
    {
        for(int j=0;j<32;j++)
        {
            n[i]= n[i]<<1;
            if(convertendo[y]=='1')
                n[i]=(n[i]^0b01);
            y++;
        }
    }
    compact=n;

}


void HuffmanTree::descomprimir()
{
    HuffmanNode *No=Raiz;

    ifstream comprimido;
    comprimido.open("comprimido.txt");
    string convertendo;


    int y=0;
    getline(comprimido,convertendo);

    comprimido.close();

    ofstream saida;
    saida.open("saida.txt");
    for(int i=0;i<convertendo.size();i++)
    {
        if (convertendo[i]=='0')
        {
            No=No->esquerda;
        }
        else if (convertendo[i]=='1')
        {
            No=No->direita;
        }

        if (No->folha)
        {
            cout << No->data;
            No=Raiz;
            y++;
            if (y%60==0)
                cout << '\n';
        }
    }
    saida.close();
}
void HuffmanTree::descomprimir2()
{
    HuffmanNode *No=Raiz;
    long long int y=0;
    int x=0;
    int z=31;

    for(int i=0;i<QuantidadeDeInt;i++)
    {
        for(int j=0;j<32;j++){
            if((compact[i]<<x)>>(z))
            {
                //cout << "1";
                No=No->direita;
            }
            else{
                //cout << "0";
                No=No->esquerda;
            }
            if (No->folha){
                No=Raiz;
                y++;
            }
            x++;
        }
    }
}
float HuffmanTree::TaxaComprecao()
{
    int TamanhoFinal=quantidadeA*(caminhoA.size());
    TamanhoFinal=TamanhoFinal+(quantidadeC*(caminhoC.size()));
    TamanhoFinal=TamanhoFinal+(quantidadeT*(caminhoT.size()));
    TamanhoFinal=TamanhoFinal+(quantidadeG*(caminhoG.size()));

    cout << endl << TamanhoFinal << " "<<tamanho*4 ;

    float taxa=(tamanho*4)-TamanhoFinal;
    taxa=taxa/(tamanho*4);

    return taxa *100;
}
