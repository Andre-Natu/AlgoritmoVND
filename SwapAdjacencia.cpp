#include "SwapAdjacencia.h"
#include <array>
#include "PedidoData.h"

int trocarElementos(const int primeiroElemento, const int segundoElemento, std::vector<Solucao>& solucao, const PedidoData& pedidos) {
    int tempoAtual = 0;
    int pedidoAnterior = 0;
    int novaMultaTotal = 0;

    // troca os dois valores de lugar
    const int indexTemp = solucao[primeiroElemento].indexPedido;
    solucao[primeiroElemento].indexPedido = solucao[segundoElemento].indexPedido;
    solucao[segundoElemento].indexPedido = indexTemp;

    // recalcula a solução
    for(int i = 0; i < pedidos.getNumeroPedidos(); i++) {
        // faz a passagem do tempo e registra o tempo de conclusão do pedido.
        tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i].indexPedido];
        tempoAtual += pedidos.tempoProducao[solucao[i].indexPedido];

        // armazena os valores no struct solucao.
        solucao[i].tempoConclusao = tempoAtual;
        solucao[i].indexPedidoAnterior = pedidoAnterior;
        solucao[i].multa = std::max(0,
            pedidos.valorMulta[solucao[i].indexPedido] *
            (solucao[i].tempoConclusao - pedidos.prazo[solucao[i].indexPedido]));

        // calculando a nova multa da mudança.
        novaMultaTotal += std::max(0,
              pedidos.valorMulta[solucao[i].indexPedido] *
              (tempoAtual - pedidos.prazo[solucao[i].indexPedido]));

        pedidoAnterior = solucao[i].indexPedido +1;
    }
    return novaMultaTotal;
}

void fazerSwapAdjacencia(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal) {



    // como posicaoAnterior iniciando com 0, não é preciso de um if no começo pra lidar
    // com o problema da matriz ter uma linha a mais que colunas.
    int pedidoAnterior = 0;
    int tempoAtual = 0;

    for (int i = 0; i < pedidos.getNumeroPedidos() - 1; i++) {
        int novaMultaTotal = 0;

        // remove todas as multas dos valores alterados.
        for (int j = 0; j < i; j++) {

            novaMultaTotal += solucao[j].multa;

            if (novaMultaTotal < 0) {
                std::cout << "Multa negativa: " << novaMultaTotal << std::endl;
                throw std::runtime_error("Forcing termination");
            }
        }

        // calcula o novo tempo de conclusão do elemento trocando com o elemento da frente.
        tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i+1].indexPedido];
        tempoAtual += pedidos.tempoProducao[solucao[i+1].indexPedido];
        novaMultaTotal += std::max(0,
              pedidos.valorMulta[solucao[i+1].indexPedido] *
              (tempoAtual - pedidos.prazo[solucao[i+1].indexPedido]));

        // Calcula o novo tempo de conclusão do segundo elemento trocando com o elemento de trás.
        // É i+1 porque o elemento de trás agora é o i+1, pois eles trocaram de posição.
        pedidoAnterior = solucao[i+1].indexPedido + 1;
        tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i].indexPedido];
        tempoAtual += pedidos.tempoProducao[solucao[i].indexPedido];
        novaMultaTotal += std::max(0,
              pedidos.valorMulta[solucao[i].indexPedido] *
              (tempoAtual - pedidos.prazo[solucao[i].indexPedido]));

        //soma +1 porque a matriz tem mais linhas que colunas.
        pedidoAnterior = solucao[i].indexPedido +1;

        // Calcula o novo tempo de conclusão dos elementos posteriores a troca.
        for(int j = i+2; j < pedidos.getNumeroPedidos(); j++) {
            tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[j].indexPedido];
            tempoAtual += pedidos.tempoProducao[solucao[j].indexPedido];
            novaMultaTotal += std::max(0,
              pedidos.valorMulta[solucao[j].indexPedido] *
              (tempoAtual - pedidos.prazo[solucao[j].indexPedido]));

            // if para parar o loop se a solução for ruim.
            if (novaMultaTotal >= melhorMultaTotal[0]) {
                j = pedidos.getNumeroPedidos() + 1;
            }
            pedidoAnterior = solucao[j].indexPedido +1;
        }

        // Resetando o tempoAtual e o pedidoAnterior:
        tempoAtual = solucao[i].tempoConclusao;
        pedidoAnterior = solucao[i].indexPedido + 1;

        if (novaMultaTotal < melhorMultaTotal[0] ) {
            melhorMultaTotal[0] = novaMultaTotal;

            // i representa o segundo elemento da troca e i+1 o segundo pois eles foram trocados.
            melhorMultaTotal[1] = i;
            melhorMultaTotal[2] = i+1;
        }
    }
    std::cout << "Menor multa: " << melhorMultaTotal[0] << std::endl;
}
