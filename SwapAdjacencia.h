#ifndef SWAPADJACENCIA_H
#define SWAPADJACENCIA_H
#include "PedidoData.h"

void fazerSwapAdjacencia(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal);
void trocarElementos(int primeiroElemento,int segundoElemento, std::vector<Solucao>& solucao,const PedidoData& pedidos);

#endif //SWAPADJACENCIA_H
