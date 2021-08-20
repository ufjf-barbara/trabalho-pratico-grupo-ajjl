#ifndef NOA_H_INCLUDED
#define NOA_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;
typedef struct
{
    char id[23];
    char genres [700];
    char name [400];
    int popularity;
    float followers;

}
Artista;

class NoA
{
private:
    string id;
    string genres;
    string name;
    int popularity;
    float followers;

    NoA *prox;
    NoA *ant;

public:
    NoA(){};
    ~NoA(){};
    NoA* getAnt()          { return ant; };
    void setAnt(NoA *p)    { ant = p; };
    NoA* getProx()         { return prox; };
    void setProx(NoA *p)   { prox = p; };

    string getid()         { return id; };
    string getgenres()     { return genres; };
    string getname()       { return name; };
    int getpopularity()    { return popularity; };
    float getfollowers()   { return followers; };

    void setid(string Idnew) { id = Idnew; };
    void setgenres(string genresnew) { genres = genresnew; }
    void setname(string namenew) { name = namenew; }
    void setpopularity(int popularitynew) { popularity = popularitynew; }
    void setfollowers(float followersnew) { followers = followersnew; }

};
#endif // NO_H_INCLUDED
