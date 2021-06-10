#ifndef NOT_H_INCLUDED
#define NOT_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class NoT
{
private:
    string id;
    string name;
    int popularity;
    int duration_ms;
    bool explicito;
    string artists;
    string id_artists;
    string release_date;
    float danceability;
    float energy;
    float key;
    float loudness;
    float mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int time_signature;

    NoT *prox;

public:
    NoT()                  { };
    ~NoT()                 { };
    NoT* getProx()         { return prox; };
    void setProx(NoT *p)   { prox = p; };

    string getid()               { return id; };
    string getname()             { return name; };
    int getpopularity()          { return popularity; };
    int getduration_ms()         { return duration_ms; };
    bool getexplicito()          { return explicito; };
    string getartists()          { return artists; };
    string getid_artists()       { return id_artists; };
    string getrelease_date()     { return release_date; };
    float getdanceability()      { return danceability; };
    float getenergy()            { return energy; };
    float getkey()               { return key; };
    float getloudness()          { return loudness; };
    float getmode()              { return mode; };
    float getspeechiness()       { return speechiness; };
    float getacousticness()      { return acousticness; };
    float getinstrumentalness()  { return instrumentalness; };
    float getliveness()          { return liveness; };
    float getvalence()           { return valence; };
    float gettempo()             { return tempo; };
    int gettime_signature()      { return time_signature; };

    void setid(string Idnew)                          { id = Idnew; };
    void setname(string namenew)                      { name = namenew; };
    void setpopularity(int popularitynew)             { popularity = popularitynew; };
    void setduration_ms(int duration_msnew)           {duration_ms = duration_msnew; } ;
    void setexplicito(bool explicitonew)              {explicito = explicitonew; };
    void setartists (string artistsnew)               {artists = artistsnew; };
    void setid_artists(string id_artistsnew)          {id_artists = id_artistsnew; };
    void setrelease_date(string release_datenew)      {release_date = release_datenew; };
    void setdanceability(float danceabilitynew)       {danceability = danceabilitynew; };
    void setenergy(float energynew)                   {energy = energynew; };
    void setkey(float keynew)                         {key = keynew; };
    void setloudness(float loudnessnew)               {loudness = loudnessnew; };
    void setmode(float modenew)                       {mode = modenew; };
    void setspeechiness(float speechinessnew)         {speechiness = speechinessnew; };
    void setacousticness(float acousticnessnew)       {acousticness = acousticnessnew; };
    void setinstrumentalness(float instrumentalnessnew) {instrumentalness= instrumentalnessnew; };
    void setliveness (float livenessnew)            {liveness = livenessnew; };
    void setvalence (float valencenew)              {valence = valencenew; };
    void settempo (float temponew )                 {tempo = temponew; };
    void settime_signature (int time_signaturenew)  {time_signature = time_signaturenew; };

};
#endif // NO_H_INCLUDED
