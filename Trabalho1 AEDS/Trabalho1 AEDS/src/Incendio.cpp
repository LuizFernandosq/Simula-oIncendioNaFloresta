#include "Incendio.hpp"
#include "Animal.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "config.hpp"
#include <stdexcept>
#include <thread>     
#include <chrono>   
Incendio::Incendio(const std::string& nomeArquivo) :  animal() {
    mapa.carregarMapa(nomeArquivo);
    int fogoX = mapa.getFogoX();
    int fogoY = mapa.getFogoY();
    mapa.setValor(fogoX, fogoY, 2);

    std::pair<int, int> posAnimal = animal.getPosicao();
    if (mapa.getValor(posAnimal.first, posAnimal.second) == 2) {
        throw std::runtime_error("O animal nasceu numa posição de fogo, logo está morto.");
    }
}

void Incendio::executarSimulacao() {
    try {
    
        std::cout << "Simulação concluída. Verifique o arquivo output.dat\n";
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        throw; 
    }
    std::ofstream clearFile("output.dat");
    clearFile.close();

    std::vector<std::pair<int, int>> queimarProximaIteracao;
    for (int iteracao = 1; iteracao <= MAX_ITERACOES; ++iteracao) {
        std::ofstream arquivo("output.dat", std::ios::app);  

        animal.mover(mapa);

       
        arquivo << "Iteração " << iteracao << "\n";
        
        for (const auto& pos : queimarProximaIteracao) {
            mapa.setValor(pos.first, pos.second, 3);
        }
        // Primeiramente limpamos o vetor, para que ele comece vazio
        // Marcamos todas as posições que vão queimar (virar 2)e adicionamos no vetor novasChamas. 
        //Lemos toda a matriz e analisamos o que vai entrar dentro do vetor
        //Para entrar nesse vetor tem as condiçõs de que o vento está no sentido que esteja dentro do mapa, e que posição esteja comoo 1
        // Lemos esse vetor por completo e tudo que estava dentro dele é marcado como uma posição de valor 2
        queimarProximaIteracao.clear();

        std::vector<std::pair<int, int>> novasChamas;
        for (int i = 0; i < mapa.getLinhas(); ++i) {
            for (int j = 0; j < mapa.getColunas(); ++j) {
                if (mapa.getValor(i, j) == 2) {
                    queimarProximaIteracao.emplace_back(i, j);
                    
                    if (podePropagarCima() && mapa.dentroDoLimite(i-1, j) && mapa.getValor(i-1, j) == 1)
                        novasChamas.emplace_back(i-1, j);
                    if (podePropagarBaixo() && mapa.dentroDoLimite(i+1, j) && mapa.getValor(i+1, j) == 1)
                        novasChamas.emplace_back(i+1, j);
                    if (podePropagarEsquerda() && mapa.dentroDoLimite(i, j-1) && mapa.getValor(i, j-1) == 1)
                        novasChamas.emplace_back(i, j-1);
                    if (podePropagarDireita() && mapa.dentroDoLimite(i, j+1) && mapa.getValor(i, j+1) == 1)
                        novasChamas.emplace_back(i, j+1);
                }
            }
        }

        for (const auto& pos : novasChamas) {
            mapa.setValor(pos.first, pos.second, 2);
        }
        if (animal.estaEmPerigo(mapa)) {
            if (animal.temRotaDeFuga(mapa) && !animal.usouSegundaChance()) {
                animal.forcarFuga(mapa);
                animal.usarSegundaChance();
            } else {
                animal.morrer(iteracao);
            }
        }

        for (int i = 0; i < mapa.getLinhas(); ++i) {
            for (int j = 0; j < mapa.getColunas(); ++j) {
                arquivo << mapa.getValor(i, j) << " ";
            }
            arquivo << "\n";
        }
        arquivo << "\n";  
        arquivo << "Animal: " << animal.getUltimaPosicao() 
                << " | Status: " << animal.getStatus() 
                << " | Passos: " << animal.getPassos()
                << " | Encontros com água: " << animal.getEncontrosAgua() << "\n\n"; 

        
        arquivo.close();
        std::this_thread::sleep_for(std::chrono::seconds(2)); 
        
        // O codigo irá parar quando nenhum dos vetores tiver mais casas pra queimar

        if (queimarProximaIteracao.empty() && novasChamas.empty()) break; 
    }

    std::ofstream arquivo("output.dat", std::ios::app);
    const auto& caminho = animal.getCaminho();
    arquivo << "\nCAMINHO COMPLETO (" << caminho.size() << " passos): ";
    
    bool primeiro = true;
    for (const auto& pos : caminho) {
        if (!primeiro) arquivo << " - ";
        arquivo << "(" << pos.first << "," << pos.second << ")";
        primeiro = false;
    }
    if (!animal.estaVivo()) {
        arquivo << "\nANIMAL MORREU NA ITERACAO " << animal.getIteracaoMorte()-1;
    }
    arquivo.close();
}

// Funçõs booleanas para sabermos se o vento está propicio para propagar em uma direção especifica
// Se a existencia de vento for falsa , ou aquela direção especifica for verdadeira o fogo se espalha para o local desejado

bool Incendio::podePropagarCima() { 
    return !VENTO_ATIVO || VENTO_NORTE;
}

bool Incendio::podePropagarBaixo() { 
    return !VENTO_ATIVO || VENTO_SUL; 
}

bool Incendio::podePropagarEsquerda() { 
    return !VENTO_ATIVO || VENTO_OESTE; 
}

bool Incendio::podePropagarDireita() { 
    return !VENTO_ATIVO || VENTO_LESTE; 
}