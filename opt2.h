
#ifndef OPT2_H
#define OPT2_H
#include "PedidoData.h"

void fazerOPT(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal);

void inverterElementos(int primeiroElemento,int segundoElemento, std::vector<Solucao>& solucao,const PedidoData& pedidos);


#endif //OPT2_H
