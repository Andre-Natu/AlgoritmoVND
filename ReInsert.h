#ifndef REINSERT_H
#define REINSERT_H
#include "PedidoData.h"

int reInserirElemento(int primeiroElemento,int segundoElemento, std::vector<Solucao>& solucao,const PedidoData& pedidos);
void fazerReInsert(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal);


#endif //REINSERT_H
