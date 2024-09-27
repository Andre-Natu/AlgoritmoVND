#ifndef ALGORITMOGULOSO_H
#define ALGORITMOGULOSO_H
#include "PedidoData.h"
#include <map>

void calcularSolucaoGulosa(PedidoData& pedidos, std::vector<Solucao>& solucao);
void calcularFuncaoObjetivo(PedidoData& pedidos, std::multimap<double, int>& funcaoObjetivo);

#endif //ALGORITMOGULOSO_H
