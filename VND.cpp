#include "VND.h"
#include <array>

#include "opt2.h"
#include "ReInsert.h"
#include "Swap.h"
#include "SwapAdjacencia.h"


void calcularSolucaoVND(PedidoData& pedidos, std::vector<Solucao>& solucao) {
    // 1 valor é o valor da multa, o segundo é o index da primeira posição
    // e o terceiro valor é o index da segunda posição.
    std::array melhorMultaTotal = { pedidos.getMultaTotal(), 0, 0 };

    int k = 1;
    // 4 é a quantidade de vizinhanças que exitem no VND.
    while ( k <= 4) {

        switch(k) {
            case 1:
                fazerSwapAdjacencia(pedidos, solucao, melhorMultaTotal);
                    break;
            case 2:
                fazerSwap(pedidos, solucao, melhorMultaTotal);
                    break;
            case 3:
                fazerOPT(pedidos, solucao, melhorMultaTotal);
                    break;
            case 4:
                fazerReInsert(pedidos, solucao, melhorMultaTotal);
                    break;
            default:
                // não existe possibilidade de cair aq.
                    break;;
        }

        if ( melhorMultaTotal[0] < pedidos.getMultaTotal() ) {

            switch (k) {
                case 3:
                    inverterElementos(melhorMultaTotal[1],melhorMultaTotal[2],solucao, pedidos);
                    break;;
                case 4:
                    reInserirElemento(melhorMultaTotal[1],melhorMultaTotal[2],solucao, pedidos);
                    break;;
                default:
                    // para os casos do swap.
                    trocarElementos(melhorMultaTotal[1],melhorMultaTotal[2],solucao, pedidos);
                    break;;
            }
            // faz o swap de fato.
            pedidos.setMultaTotal(melhorMultaTotal[0]);
            k = 1;
        } else {
            k++;
        }
    }

}

