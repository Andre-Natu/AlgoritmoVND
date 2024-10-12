#ifndef ILS_H
#define ILS_H
#include "PedidoData.h"

void calcularSolucaoILS(PedidoData& pedidos, std::vector<Solucao>& solucao);

bool criterioAceitacao(PedidoData& pedidos,std::vector<Solucao>& solucao, std::vector<Solucao>& novaSolucao);

#endif //ILS_H
