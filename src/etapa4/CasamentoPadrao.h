#ifndef CasamentoPadrao_H_INCLUDED
#define CasamentoPadrao_H_INCLUDED
#include <string>
typedef std::string string;

class CasamentoPadrao{
    public:
        void ForcaBruta(string T, string P);
        void KMP(string T, string P);
        void BMHsearch(string sequenciaT, string padraoP);
};

#endif