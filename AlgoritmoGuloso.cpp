#include "AlgoritmoGuloso.h"
#include "PedidoData.h"
#include <map>
#include <algorithm>

void calcularFuncaoObjetivo(PedidoData& pedidos, std::multimap<double, int>& funcaoObjetivo) {


    // Preenchendo o multimap
    for (int i = 0; i < pedidos.getNumeroPedidos(); i++) {
        double resultado = (pedidos.prazo[i] - pedidos.tempoProducao[i]) /  static_cast<double>(pedidos.valorMulta[i]);
        funcaoObjetivo.insert(std::pair(resultado, i));
    }


}

void calcularSolucaoGulosa(PedidoData& pedidos, std::vector<Solucao>& solucao) {
    // Multimap para armazenar (valor, índice)
    std::multimap<double, int> funcaoObjetivo;

    calcularFuncaoObjetivo(pedidos, funcaoObjetivo);

    int tempoAtual = 0;
    // como posicaoAnterior iniciando com 0, não é preciso de um if no começo pra lidar com
    // o problema da matriz ter uma linha a mais que colunas.
    int pedidoAnterior = 0;
    int i = 0;

    // itera sobre a funcaoObjetivo, fazendo o calculo da solucao gulosa
    for (const auto&[valorFuncaoObjetivo, pedidoAtual] : funcaoObjetivo) {

        // faz a passagem do tempo e registra o tempo de conclusão do pedido.
        tempoAtual += pedidos.matrizTempoTransicao[pedidoAnterior][pedidoAtual];
        tempoAtual += pedidos.tempoProducao[pedidoAtual];

        // armazena os valores no struct solucao.
        solucao[i].tempoConclusao = tempoAtual;
        solucao[i].indexPedido = pedidoAtual;
        solucao[i].indexPedidoAnterior = pedidoAnterior;

        // calculo da multa
        solucao[i].multa = std::max(0,
            pedidos.valorMulta[pedidoAtual] * (solucao[i].tempoConclusao - pedidos.prazo[pedidoAtual]));
        pedidos.adicionarMulta(solucao[i].multa);

        // +1 por que a matriz tem mais linhas do que colunas
        pedidoAnterior = pedidoAtual + 1;
        i++;
    }

}
