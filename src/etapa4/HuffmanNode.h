#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H

using namespace std;
class HuffmanNode
{
    public:
        HuffmanNode(){;};
        ~HuffmanNode(){;};

        char data;
        bool folha;
        long long int frequencia;
        HuffmanNode *esquerda;
        HuffmanNode *direita;

};

#endif // HUFFMANNODE_H
