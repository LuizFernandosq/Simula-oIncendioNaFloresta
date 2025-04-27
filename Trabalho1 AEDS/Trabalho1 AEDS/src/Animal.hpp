#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <utility>
#include <list>
#include <string>
#include "Mapa.hpp"

class Animal {
private:
    std::pair<int, int> posicao;
    std::list<std::pair<int, int>> caminho;
    int passos;
    int encontrosAgua;
    bool vivo;
    bool segundaChanceUsada;
    int iteracoesParado;
    int iteracaoMorte;  // Novo atributo

    // Métodos auxiliares existentes
    bool podeMoverPara(int x, int y, const Mapa& mapa) const;
    bool jaVisitada(int x, int y) const;
    void converterVizinhosParaArvores(Mapa& mapa);

public:
    Animal();
    
    // Métodos existentes
    void mover(Mapa& mapa);
    std::pair<int, int> getPosicao() const;
    bool estaVivo() const;
    int getPassos() const;
    int getEncontrosAgua() const;
    std::string getStatus() const;
    std::string getUltimaPosicao() const;
    const std::list<std::pair<int, int>>& getCaminho() const;
    
    // Novos métodos para segunda chance e sobrevivência
    bool estaEmPerigo(const Mapa& mapa) const;       
    bool temRotaDeFuga(const Mapa& mapa) const;   
    void forcarFuga(Mapa& mapa);                     
    void usarSegundaChance();                       
    bool usouSegundaChance() const;                 
    void morrer(int iteracao);                      
    int getIteracaoMorte() const;                    

   
    int calcularPrioridade(int tipo_celula, bool visitada) const;
    std::vector<std::pair<int, int>> getDirecoesPossiveis() const;
    std::pair<std::pair<int, int>, int> avaliarDirecao(int linha, int coluna, const Mapa& mapa) const;
    bool devePararBusca(int prioridade) const;
    std::pair<int, int> encontrarMelhorMovimento(const Mapa& mapa) const;
};

#endif