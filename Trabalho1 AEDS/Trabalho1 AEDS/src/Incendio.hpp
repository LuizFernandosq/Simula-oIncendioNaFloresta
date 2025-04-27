#ifndef INCENDIO_HPP
#define INCENDIO_HPP

#include <string>
#include "Mapa.hpp"
#include "Animal.hpp"

class Incendio {
private:
    Mapa mapa;
    Animal animal; 

    bool podePropagarCima();
    bool podePropagarBaixo();
    bool podePropagarEsquerda();
    bool podePropagarDireita();

public:
    Incendio(const std::string& nomeArquivo);
    void imprimirMapa() const; 
    void executarSimulacao();
   
    
};

#endif
