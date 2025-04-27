#include "Mapa.hpp"
#include <fstream>
#include <iostream>

Mapa::Mapa() 
    : linhas(0), 
      colunas(0), 
      fogoX(0), 
      fogoY(0) 
{}

void Mapa::carregarMapa(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    arquivo >> linhas >> colunas >> fogoX >> fogoY;

    matriz.resize(linhas, std::vector<int>(colunas));
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arquivo >> matriz[i][j];
        }
    }

    arquivo.close();
}

void Mapa::imprimirMapa() const {
    for (const auto& linha : matriz) {
        for (int valor : linha) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}
int Mapa::getLinhas() const { 
    return linhas; 
    }
int Mapa::getColunas() const { 
    return colunas; 
}   
int Mapa::getValor(int x, int y) const {
     return matriz[x][y]; 
    }
void Mapa::setValor(int x, int y, int valor) { 
    matriz[x][y] = valor; 
    }
bool Mapa::dentroDoLimite(int x, int y) const {
     return x >= 0 && x < linhas && y >= 0 && y < colunas;
     }
int Mapa::getFogoX() const { 
    return fogoX; 
    }      
int Mapa::getFogoY() const { 
   return fogoY; 
    }   
   