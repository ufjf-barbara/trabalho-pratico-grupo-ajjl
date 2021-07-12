#ifndef NoHash_H_INCLUDED
#define NoHash_H_INCLUDED
#include <string>
typedef std::string string;

class NoHash{
public :
    string id;
    string nome;
    int frequencia;
    string musicaPopular;
    int popularity;

    NoHash(string id, string nome, int frequencia, string musicaPopular, int popularity){
        this->id = id;
        this->nome = nome;
        this->frequencia = frequencia;
        this->musicaPopular = musicaPopular;
        this->popularity = popularity;
    }
};


#endif // NoHash_H_INCLUDED