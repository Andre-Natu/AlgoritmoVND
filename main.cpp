#include <array>
#include <fstream>
#include <iostream>
#include "PedidoData.h"
#include "AlgoritmoGuloso.h"
#include "SwapAdjacencia.h"
#include "VND.h"

int main() {
    PedidoData pedidos("instancias/n60A.txt");

    // Exibindo os dados apenas para motivos de teste.
    // pedidos.exibirDados();

    // Criando o vetor Solucao que será usado no programa inteiro
    std::vector<Solucao> solucao(pedidos.getNumeroPedidos());

    calcularSolucaoGulosa(pedidos, solucao);
    std::cout << "Valor total a ser pago de multa do guloso: " << pedidos.getMultaTotal() << std::endl;

    calcularSolucaoVND(pedidos, solucao);

    /*
    // Acessando e exibindo os elementos do vetor
    for (const auto& element : solucao) {
        std::cout << "indexPedidoAnterior: " << element.indexPedidoAnterior
                  << ", indexPedido: " << element.indexPedido
                  << ", tempoConclusao: " << element.tempoConclusao
                  << ", multa: " << element.multa << std::endl;
    }
*/
    return 0;
}
