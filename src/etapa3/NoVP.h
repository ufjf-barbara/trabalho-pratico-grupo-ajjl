#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED
#include <iostream>
#include <string>
#include "NoA.h"

/*

Propriedades:
 - Cada nó é V ou P
 - A raiz é P
 - Cada folha (NIL) é P
 - Se um nó é V, seus filhos sao P
 - Todo caminho até as folhas possui o mesmo número de nós P (altura negra)

 Altura negra = Numero de nós pretos em qualquer caminho de um nó X até uma folha, excluindo o nó X

*/

#define RED 1
#define BLACK 0

class NoVP {
    protected:
        Artista artista; // Recebe todos dados do artista
        NoVP* direito; // Ponteiro para filho direito do nó
        NoVP* esquerdo; // Ponteiro para filho esquerdo do nó
        NoVP* pai; // Ponteiro para pai do nó
        bool cor; // RED = 1, BLACK = 0

    public:
        NoVP(){};

        NoVP(Artista artista){
            this->artista = artista;
            this->direito = nullptr;
            this->esquerdo = nullptr;
            this->pai = nullptr;
            this->cor = RED; // Para obedecer propriedade de que todo nó inserido deve ser vermelho
        }

        ~NoVP() = default;

        Artista getArtista() { return this->artista; }

        NoVP *getDireito() const{
            if(this == nullptr)
                return nullptr;
            return this->direito;
        }

        NoVP *getEsquerdo() const{
            if(this == nullptr)
                return nullptr;
            return this->esquerdo;
        }

        void setDireito(NoVP *direito){
            if(this != nullptr)
                this->direito = direito;
        }

        void setEsquerdo(NoVP *esquerdo){
            if(this != nullptr)
                this->esquerdo = esquerdo;
        }

        NoVP *getPai() const{
            if(this == nullptr)
                return nullptr;
            return this->pai;
        }

        void setPai(NoVP *pai){
            if (this != nullptr)
                this->pai = pai;
        }

        bool getCor() const{
            if(this == nullptr)
                return false;
            return this->cor;
        }

        void setCor(bool cor){
            if (this != nullptr)
                this->cor = cor;
        }
};
#endif // NOVP_H_INCLUDED