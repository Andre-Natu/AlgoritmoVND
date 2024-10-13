#include <array>
#include "PedidoData.h"
#include <vector>
#include "opt2.h"


void inverterElementos(const int primeiroElemento, const int segundoElemento, std::vector<Solucao>& solucao, const PedidoData& pedidos) {

    // como o 2-opt nunca vai trocar o primeiro elemento de lugar, não precisa começar com 0.
    int pedidoAnterior = solucao[primeiroElemento].indexPedido + 1;
    int tempoAtual = solucao[primeiroElemento].tempoConclusao;

    // Se o i e o j se encontrarem, significa que já trocaram todos os valores
    int j = segundoElemento-1;
    for (int i = primeiroElemento +1; i < j; i++) {

        // troca os dois valores de lugar.
        const int indexTemp = solucao[i].indexPedido;
        solucao[i].indexPedido = solucao[j].indexPedido;
        solucao[j].indexPedido = indexTemp;

        j--;
    }

    // recalcula a solução
    for(int i = primeiroElemento + 1; i < pedidos.getNumeroPedidos(); i++) {
        // faz a passagem do tempo e registra o tempo de conclusão do pedido.
        tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i].indexPedido];
        tempoAtual += pedidos.tempoProducao[solucao[i].indexPedido];

        // armazena os valores no struct solucao.
        solucao[i].tempoConclusao = tempoAtual;
        solucao[i].indexPedidoAnterior = pedidoAnterior;
        solucao[i].multa = std::max(0,
            pedidos.valorMulta[solucao[i].indexPedido] *
            (solucao[i].tempoConclusao - pedidos.prazo[solucao[i].indexPedido]));

        pedidoAnterior = solucao[i].indexPedido +1;
    }
}

void fazerOPT(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal) {

// mudar o j para i+5, para pular as trocas ja feitas pelos swaps.
    for (int i = 0; i < pedidos.getNumeroPedidos() - 5; i++) {
        for (int j = i+5; j < pedidos.getNumeroPedidos(); j++) {
            // como o 2-opt nunca vai trocar o 1 elemento de lugar, não precisa começar com 0.
            int pedidoAnterior = solucao[i].indexPedido + 1;
            int tempoAtual = solucao[i].tempoConclusao;
            int novaMultaTotal = 0;

            // adiciona apenas as multas dos valores que não foram alterados.
            for (int k = 0; k <= i; k++) {
                novaMultaTotal += solucao[k].multa;
            }

            // simula a inversão dos elementos entre o i e o j.
            for(int k = j-1; k > i; k--) {
                tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[k].indexPedido];
                tempoAtual += pedidos.tempoProducao[solucao[k].indexPedido];

                novaMultaTotal += std::max(0,
                  pedidos.valorMulta[solucao[k].indexPedido] *
                  (tempoAtual - pedidos.prazo[solucao[k].indexPedido]));


                pedidoAnterior = solucao[k].indexPedido +1;

                // if para parar o loop se a solução for ruim.
                if (novaMultaTotal >= melhorMultaTotal[0]) {
                    k = i;
                }
            }

            // Calcula o novo tempo de conclusão dos elementos posteriores a inversão.
            for(int k = j; k < pedidos.getNumeroPedidos(); k++) {
                tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[k].indexPedido];
                tempoAtual += pedidos.tempoProducao[solucao[k].indexPedido];
                novaMultaTotal += std::max(0,
                  pedidos.valorMulta[solucao[k].indexPedido] *
                  (tempoAtual - pedidos.prazo[solucao[k].indexPedido]));

                pedidoAnterior = solucao[k].indexPedido +1;
                // if para parar o loop se a solução for ruim.
                if (novaMultaTotal >= melhorMultaTotal[0]) {
                    k = pedidos.getNumeroPedidos() + 1;
                }

            }

            if (novaMultaTotal < melhorMultaTotal[0] ) {
                melhorMultaTotal[0] = novaMultaTotal;

                // i representa o segundo elemento da troca e i+1 o segundo pois eles foram trocados.
                melhorMultaTotal[1] = i;
                melhorMultaTotal[2] = j;
            }
        }
    }
}