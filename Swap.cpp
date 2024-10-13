#include "Swap.h"
#include <array>
#include "PedidoData.h"
#include <vector>


void fazerSwap(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal) {
    // como posicaoAnterior iniciando com 0, não é preciso de um if no começo para lidar
    // com o problema da matriz ter uma linha a mais que colunas.
    int pedidoAnterior = 0;
    int tempoAtual = 0;

    for (int i = 0; i < pedidos.getNumeroPedidos() - 2; i++) {
        for (int j = i+2; j < pedidos.getNumeroPedidos(); j++) {
            int novaMultaTotal = 0;

            // remove todas as multas dos valores alterados.
            for (int k = 0; k < i; k++) {

                novaMultaTotal += solucao[k].multa;

                if (novaMultaTotal < 0) {
                    std::cout << "Multa negativa: " << novaMultaTotal << std::endl;
                    throw std::runtime_error("Forcing termination");
                }
            }

            // calcula o novo tempo de conclusão do primeiro elemento trocando com o segundo.
            tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[j].indexPedido];
            tempoAtual += pedidos.tempoProducao[solucao[j].indexPedido];
            novaMultaTotal += std::max(0,
                  pedidos.valorMulta[solucao[j].indexPedido] *
                  (tempoAtual - pedidos.prazo[solucao[j].indexPedido]));


            // Calcula o tempo de conclusão e multa dos elementos entre o i e o J.
            pedidoAnterior = solucao[j].indexPedido + 1;
            for(int k = i+1; k < j; k++) {
                tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[k].indexPedido];
                tempoAtual += pedidos.tempoProducao[solucao[k].indexPedido];
                novaMultaTotal += std::max(0,
                  pedidos.valorMulta[solucao[k].indexPedido] *
                  (tempoAtual - pedidos.prazo[solucao[k].indexPedido]));

                // if para parar o loop se a solução for ruim.
                if (novaMultaTotal >= melhorMultaTotal[0]) {
                    k = pedidos.getNumeroPedidos() + 1;
                }
                 pedidoAnterior = solucao[k].indexPedido +1;
            }

            // Verifica se a nova solução é pior que a melhor, se for ele para ela.
            if (novaMultaTotal < melhorMultaTotal[0]) {


                // Calcula o novo tempo de conclusão do segundo elemento trocando com o primeiro elemento.
                // Ver se dá para remover essa linha do pedido.
                pedidoAnterior = solucao[j-1].indexPedido + 1;
                tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i].indexPedido];
                tempoAtual += pedidos.tempoProducao[solucao[i].indexPedido];
                novaMultaTotal += std::max(0,
                      pedidos.valorMulta[solucao[i].indexPedido] *
                      (tempoAtual - pedidos.prazo[solucao[i].indexPedido]));

                // soma +1, pois a matriz tem mais linhas que colunas.
                pedidoAnterior = solucao[i].indexPedido +1;

                // Calcula o novo tempo de conclusão dos elementos posteriores a troca.
                for(int k = j+1; k < pedidos.getNumeroPedidos(); k++) {
                    tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[k].indexPedido];
                    tempoAtual += pedidos.tempoProducao[solucao[k].indexPedido];
                    novaMultaTotal += std::max(0,
                      pedidos.valorMulta[solucao[k].indexPedido] *
                      (tempoAtual - pedidos.prazo[solucao[k].indexPedido]));

                    // if para parar o loop se a solução for ruim.
                    if (novaMultaTotal >= melhorMultaTotal[0]) {
                        k = pedidos.getNumeroPedidos() + 1;
                    }

                    pedidoAnterior = solucao[k].indexPedido +1;
                }
            }

            // Resetando o tempoAtual e o pedidoAnterior.
            if (i-1 < 0) {
                tempoAtual = 0;
                pedidoAnterior = 0;
            }else {
                tempoAtual = solucao[i-1].tempoConclusao;
                pedidoAnterior = solucao[i-1].indexPedido + 1;
            }

            if (novaMultaTotal < melhorMultaTotal[0] ) {
                melhorMultaTotal[0] = novaMultaTotal;

                // i representa o segundo elemento da troca e i+1 o segundo pois eles foram trocados.
                melhorMultaTotal[1] = i;
                melhorMultaTotal[2] = j;
            }
        }
        // Resetando o tempoAtual e o pedidoAnterior:
        tempoAtual = solucao[i].tempoConclusao;
        pedidoAnterior = solucao[i].indexPedido + 1;
    }
}
