#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include "PedidoData.h"
#include "AlgoritmoGuloso.h"
#include "ILS.h"
#include "SwapAdjacencia.h"
#include "VND.h"
#include "ReInsert.h"

int main() {
    PedidoData pedidos("instancias/n60A.txt");

    // Criando o vetor Solucao que será usado no programa inteiro
    std::vector<Solucao> solucao(pedidos.getNumeroPedidos());

    auto inicio = std::chrono::high_resolution_clock::now();
    calcularSolucaoGulosa(pedidos, solucao);

    // Calcula a duração
    auto fim = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::micro> tempoGuloso = fim - inicio;

    std::cout << "Valor total a ser pago de multa do guloso: " << pedidos.getMultaTotal() << std::endl;

    int melhorMultaOriginal = pedidos.getMultaTotal();

    // calculo do VND
    inicio = std::chrono::high_resolution_clock::now();
    melhorMultaOriginal = calcularSolucaoVND(pedidos, solucao, melhorMultaOriginal);

    // Calcula a duracao
    fim = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::micro> tempoVND = fim - inicio;

    // Calculo da ILS
    inicio = std::chrono::high_resolution_clock::now();
    int melhorMultaNovaSolucao = calcularSolucaoILS(pedidos, solucao, melhorMultaOriginal);

    // Calcula a duracao
    fim = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::micro> tempoILS = fim - inicio;

    std::cout << "Melhor multa Antiga: " << melhorMultaOriginal << std::endl;
    std::cout << "Melhor multa nova era games: " << melhorMultaNovaSolucao << std::endl;
    std::cout << "Melhor multa final: " << pedidos.getMultaTotal() << std::endl;

    std::cout << "O Guloso demorou " << tempoGuloso.count() << " ns." << std::endl;
    std::cout << "O VND demorou " << tempoVND.count() << " ns." << std::endl;
    std::cout << "A meta-heuristica demorou " << tempoILS.count() << " ns." << std::endl;


    // apagar essa linha do código.
    // std::array melhorMultaTotal = { pedidos.getMultaTotal(), 0, 0 };
    // fazerReInsert(pedidos, solucao, melhorMultaTotal);


    /*
    // Acessando e exibindo os elementos do vetor
    for (const auto& element : solucao) {
        std::cout << "indexPedidoAnterior: " << element.indexPedidoAnterior
                  << ", indexPedido: " << element.indexPedido
                  << ", tempoConclusao: " << element.tempoConclusao
                  << ", multa: " << element.multa << std::endl;
    }*/
    return 0;
}
