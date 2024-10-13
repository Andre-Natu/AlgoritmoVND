#include "ReInsert.h"
#include <array>
#include "PedidoData.h"
#include <vector>

void reInserirElemento(const int primeiroElemento, int segundoElemento, std::vector<Solucao>& solucao, const PedidoData& pedidos) {
    int tempoAtual = 0;
    int pedidoAnterior = 0;


    // Faz a remoção e a inserção do elemento no vetor solução.
    const Solucao indexTemp = solucao[primeiroElemento];
    solucao.erase(solucao.begin() + primeiroElemento);

    if (segundoElemento >= solucao.size()) {
        segundoElemento--;
    }

    auto it = solucao.begin() + segundoElemento ;
    // É −1 por que o vetor solução acabou de diminuir de tamanho.
    solucao.insert(it, indexTemp);

    // recalcula a solução
    for(int i = 0; i < pedidos.getNumeroPedidos(); i++) {

        // Verificar se os índices estão dentro dos limites
        if (solucao[i].indexPedido >= pedidos.getNumeroPedidos()) {
            std::cerr << "Erro: Indices fora dos limites durante o recalculo" << std::endl;
            throw std::runtime_error("Forcing termination");
        }

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

void fazerReInsert(PedidoData& pedidos, std::vector<Solucao>& solucao, std::array<int, 3>& melhorMultaTotal) {


    for (int i = 0; i < pedidos.getNumeroPedidos(); i++) {
        for (int j = 0; j < pedidos.getNumeroPedidos(); j++) {
            // pula os casos desnecessários ou que o swap já realizava antes
            if (j == i | j == i+1 | j == i+2 | j == i-1) {
                continue;
            }

            int pedidoAnterior = 0;
            int tempoAtual = 0;
            int novaMultaTotal = 0;

            // Representa o caso em que o elemento é inserido depois da posição original.
            if ( i < j) {
                // pula o elemento i e simula até a posição j.
                for (int k = 0; k < j; k++) {
                    if (k != i) {
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
                }


                // Simula a solução do elemento i inserido na nova posição.
                tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i].indexPedido];
                tempoAtual += pedidos.tempoProducao[solucao[i].indexPedido];
                novaMultaTotal += std::max(0,
                      pedidos.valorMulta[solucao[i].indexPedido] *
                      (tempoAtual - pedidos.prazo[solucao[i].indexPedido]));
                pedidoAnterior = solucao[i].indexPedido +1;

                // percorre os elementos após a inserção
                for (int k = j; k < pedidos.getNumeroPedidos(); k++) {
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


            }

            // Representa o caso em que o elemento é inserido numa posição anterior da posição original.
            if ( i > j) {
                // simula até a posição j, o que não muda nada.
                for (int k = 0; k < j; k++) {
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

                // Simula a solução do elemento i inserido na nova posição.
                tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][solucao[i].indexPedido];
                tempoAtual += pedidos.tempoProducao[solucao[i].indexPedido];
                novaMultaTotal += std::max(0,
                      pedidos.valorMulta[solucao[i].indexPedido] *
                      (tempoAtual - pedidos.prazo[solucao[i].indexPedido]));
                pedidoAnterior = solucao[i].indexPedido +1;

                // percorre os elementos após a inserção
                for (int k = j; k < pedidos.getNumeroPedidos(); k++) {
                    if (k != i) {
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
                }


            }

            if (novaMultaTotal < melhorMultaTotal[0]) {
                melhorMultaTotal[0] = novaMultaTotal;

                // i representa o segundo elemento da troca e i+1 o segundo pois eles foram trocados.
                melhorMultaTotal[1] = i;
                melhorMultaTotal[2] = j;
            }
        }
    }
    std::cout << "Melhor multa: " << melhorMultaTotal[0] << std::endl;

}