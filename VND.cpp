#include "VND.h"
#include <array>

#include "Swap.h"
#include "SwapAdjacencia.h"


void calcularSolucaoVND(PedidoData& pedidos, std::vector<Solucao>& solucao) {
    // 1 valor é o valor da multa, o segundo é o index da primeira posição
    // e o terceiro valor é o index da segunda posição.
    std::array melhorMultaTotal = { pedidos.getMultaTotal(), 0, 0 };

    fazerSwapAdjacencia(pedidos, solucao, melhorMultaTotal);
    trocarElementos(melhorMultaTotal[1],melhorMultaTotal[2],solucao, pedidos);

    fazerSwap(pedidos, solucao, melhorMultaTotal);
    trocarElementos(melhorMultaTotal[1],melhorMultaTotal[2],solucao, pedidos);
/*
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
                // implementar o 2-opt.
                    break;
            case 4:
                // implementar o re-insertion.
                    break;
            default:
                // não existe possibilidade de cair aq.
                    break;;
        }

        if ( melhorMultaTotal[0] < pedidos.getMultaTotal() ) {
            // faz o swap de fato.
            pedidos.setMultaTotal(melhorMultaTotal[0]);
            trocarElementos(melhorMultaTotal[1],melhorMultaTotal[2],solucao, pedidos);
        } else {
            k++;
        }
    }
    */
}

