#ifndef NOB_H_INCLUDED
#define NOB_H_INCLUDED
#include<string>

using namespace std;
class NoB
{
    public:
       NoB(){;};
      ~NoB(){;};
      string *chave;
      string *codigo;
      int *local;
      NoB **filhos;
      int n;
      int folha;
};

#endif // NOB_H
