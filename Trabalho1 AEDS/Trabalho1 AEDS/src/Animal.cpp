#include "Animal.hpp"
#include "Mapa.hpp"
#include "config.hpp"
#include <algorithm>
#include <stdexcept>

Animal::Animal() : posicao(ANIMAL_X, ANIMAL_Y),
                   passos(0),
                   encontrosAgua(0),
                   vivo(true),
                   segundaChanceUsada(false),
                   iteracoesParado(0),
                   iteracaoMorte(-1) 
{

    caminho.push_back(posicao);
}

// A ideia para a movimentação do animal foi dividir em varias funções
// a primeira verifica se está dentro do limite e se ele não está indo pro fogo(2)

bool Animal::podeMoverPara(int x, int y, const Mapa &mapa) const
{
    return mapa.dentroDoLimite(x, y) && mapa.getValor(x, y) != 2;
}
// A segunda verifica o caminho já foi visitado, se sim a ideia foi dá uma prioridade pra ele menor que todas as outras

bool Animal::jaVisitada(int x, int y) const
{
    return std::find(caminho.begin(), caminho.end(), std::make_pair(x, y)) != caminho.end();
}

int Animal::calcularPrioridade(int tipo_celula, bool visitada) const
{
    if (tipo_celula == 0 && iteracoesParado >= 3)
    {
        return 99;
    }
    // A ideia é que em hipotese alguma ele volte para aquele mesma caso 0 dnovo

    if (visitada)
    {
        return 5;
    }

    switch (tipo_celula)
    {
    case 4:
        return 0;
    case 0:
        return 1;
    case 1:
        return 2;
    case 3:
        return 3;
    default:
        return 99;
    }
}
// A ideia foi definir todas as direções possiveis de movimento
// Ir para todas essas direções e ve qual delas é a melhor opção.
// Se encontrar posição de valor 0, ou seja melhor posição a busca para
// Se não definir o pior caso como melhor caso , pega a posição atual se o numero da prioridade dela for menor q a de pior caso ela vira a nova melhor posição
// assim vai até achar a melhor posição possivel.
// Se analisou todas as direções e não achou outra melhor a busca para.
// Se o animal ainda estiver vivo, analise se ele está na posição 0 e inicia um contador que repete 3 vezes permitindo o animal ficar parado lá
// acabou as tres vezes a função de calcular a prioridade irá definir a posição que ele está como de baixa prioridade e reinicia o contador para quando encontrar outra casa 0
// Após isso a posição que será considerada a atual, é a posição escolhida para melhor caminho
// uma verificação que caso a casa escolhida não for igual a casa anterior, essa posição será armazenada no vetor caminho armazenando essa posição e o contador de passos sobe
// Armazenamos essas posições que posteriormente no final da função executarIncendio() ela leia todos os valores e os imprima no final do arquivo junto com a quantidade de passos
std::vector<std::pair<int, int>> Animal::getDirecoesPossiveis() const
{
    return {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
}

std::pair<std::pair<int, int>, int> Animal::avaliarDirecao(int linha, int coluna, const Mapa &mapa) const
{
    if (!podeMoverPara(linha, coluna, mapa))
    {
        return {{linha, coluna}, 99};
    }
    int tipo = mapa.getValor(linha, coluna);
    bool visitada = jaVisitada(linha, coluna);
    return {{linha, coluna}, calcularPrioridade(tipo, visitada)};
}

bool Animal::devePararBusca(int prioridade) const
{
    return (prioridade == 0);
}

std::pair<int, int> Animal::encontrarMelhorMovimento(const Mapa &mapa) const
{
    auto [lin, col] = posicao;
    auto melhor_pos = posicao;
    int melhor_prio = 99;

    for (const auto &[dl, dc] : getDirecoesPossiveis())
    {
        auto [pos, prio] = avaliarDirecao(lin + dl, col + dc, mapa);

        if (prio < melhor_prio)
        {
            melhor_pos = pos;
            melhor_prio = prio;
            if (devePararBusca(prio))
                break;
        }
    }

    return melhor_pos;
}

void Animal::mover(Mapa &mapa)
{
    if (!vivo)
        return;

    int celula_atual = mapa.getValor(posicao.first, posicao.second);

    if (celula_atual == 0 && iteracoesParado < 3)
    {
        iteracoesParado++;
        return;
    }

    iteracoesParado = 0;
    auto [nova_linha, nova_coluna] = encontrarMelhorMovimento(mapa);

    if (nova_linha != posicao.first || nova_coluna != posicao.second)
    {
        posicao = {nova_linha, nova_coluna};
        caminho.push_back(posicao);
        passos++;
        converterVizinhosParaArvores(mapa);
    }
}

std::pair<int, int> Animal::getPosicao() const { 
    return posicao; 
}
bool Animal::estaVivo() const
{
    return vivo;
}
int Animal::getPassos() const
{
    return passos;
}
int Animal::getEncontrosAgua() const
{
    return encontrosAgua;
}
std::string Animal::getStatus() const
{
    return vivo ? "Vivo" : "Morto";
}
std::string Animal::getUltimaPosicao() const
{
    return "(" + std::to_string(posicao.first) + "," + std::to_string(posicao.second) + ")";
}
const std::list<std::pair<int, int>> &Animal::getCaminho() const { return caminho; }

// A ideia aqui é que se estiver numa casa 4, imediatamente setamos esse valor pra 0
// marcamos todas as posições e colocamos no vetor celularParaConverter
// Le o vetor do começo ao fim e seta as posições como 1
void Animal::converterVizinhosParaArvores(Mapa &mapa)
{
    int x = posicao.first;
    int y = posicao.second;

    if (mapa.getValor(x, y) == 4)
    {

        mapa.setValor(x, y, 0);
        encontrosAgua++;

        std::vector<std::pair<int, int>> celulasParaConverter;

        if (mapa.dentroDoLimite(x - 1, y))
            celulasParaConverter.emplace_back(x - 1, y);

        if (mapa.dentroDoLimite(x + 1, y))
            celulasParaConverter.emplace_back(x + 1, y);

        if (mapa.dentroDoLimite(x, y - 1))
            celulasParaConverter.emplace_back(x, y - 1);

        if (mapa.dentroDoLimite(x, y + 1))
            celulasParaConverter.emplace_back(x, y + 1);

        for (const auto &pos : celulasParaConverter)
        {
            mapa.setValor(pos.first, pos.second, 1);
        }
    }
}
bool Animal::estaEmPerigo(const Mapa& mapa) const {
    return (mapa.getValor(posicao.first, posicao.second) == 2); 
}

bool Animal::temRotaDeFuga(const Mapa& mapa) const {
    for (const auto& [dx, dy] : getDirecoesPossiveis()) {
        int x = posicao.first + dx;
        int y = posicao.second + dy;
        if (mapa.dentroDoLimite(x, y) && mapa.getValor(x, y) != 2) { 
            return true;
        }
    }
    return false; 
}

void Animal::forcarFuga(Mapa& mapa) {
    int melhorPrioridade = 99;
    std::pair<int, int> melhorPos = posicao;

    for (const auto& [dx, dy] : getDirecoesPossiveis()) {
        int x = posicao.first + dx;
        int y = posicao.second + dy;
        
        if (podeMoverPara(x, y, mapa)) {
            int tipo = mapa.getValor(x, y);
            int prioridade = calcularPrioridade(tipo, jaVisitada(x, y));
            
            if (prioridade < melhorPrioridade) {
                melhorPrioridade = prioridade;
                melhorPos = {x, y};
            }
        }
    }

    if (melhorPos != posicao) {
        posicao = melhorPos;
        caminho.push_back(posicao);
        passos++;
    }
}

void Animal::usarSegundaChance() {
    segundaChanceUsada = true;
}

bool Animal::usouSegundaChance() const {
    return segundaChanceUsada;
}

void Animal::morrer(int iteracao) {
    vivo = false;
    iteracaoMorte = iteracao; 
}

int Animal::getIteracaoMorte() const {
    return iteracaoMorte;
}