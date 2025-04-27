#ifndef MAPA_HPP
#define MAPA_HPP

#include <vector>
#include <string>

class Mapa {
private:
    std::vector<std::vector<int>> matriz;
    int linhas;
    int colunas;
    int fogoX;
    int fogoY;

public:
    Mapa();
    void carregarMapa(const std::string& nomeArquivo);
    void imprimirMapa() const;
    int getLinhas() const;
    int getColunas() const;
    int getValor(int x, int y) const;
    void setValor(int x, int y, int valor);
    bool dentroDoLimite(int x, int y) const;
    int getFogoX() const;
    int getFogoY() const;

};

#endif 
