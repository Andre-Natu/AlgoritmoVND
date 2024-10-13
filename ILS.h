#ifndef ILS_H
#define ILS_H
#include "PedidoData.h"

int calcularSolucaoILS(PedidoData& pedidos, std::vector<Solucao>& solucao, int melhorMultaTotal);

bool criterioAceitacao(PedidoData& pedidos,std::vector<Solucao>& solucao, std::vector<Solucao>& novaSolucao, int melhorMultaNovaSolucao, int melhorMultaTotal);
#endif //ILS_H
