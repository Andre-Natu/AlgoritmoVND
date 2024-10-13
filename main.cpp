#include <chrono>
#include <fstream>
#include <iostream>
#include "PedidoData.h"
#include "AlgoritmoGuloso.h"
#include "ILS.h"
#include "VND.h"

int main() {
    PedidoData pedidos("instancias/n60P.txt");

    // Criando o vetor Solucao que será usado no programa inteiro
    std::vector<Solucao> solucao(pedidos.getNumeroPedidos());

    auto inicio = std::chrono::high_resolution_clock::now();
    calcularSolucaoGulosa(pedidos, solucao);
    // Calcula a duração
    auto fim = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> tempoGuloso = fim - inicio;

    std::cout << "Valor total a ser pago de multa do guloso: " << pedidos.getMultaTotal() << std::endl;

    int melhorMultaOriginal = pedidos.getMultaTotal();

    // calculo do VND
    inicio = std::chrono::high_resolution_clock::now();
    melhorMultaOriginal = calcularSolucaoVND(pedidos, solucao, melhorMultaOriginal);
    // Calcula a duracao
    fim = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> tempoVND = fim - inicio;

    std::cout << "Melhor multa do VND: " << melhorMultaOriginal << std::endl;


    // Calculo da ILS
    inicio = std::chrono::high_resolution_clock::now();
    int melhorMultaNovaSolucao = calcularSolucaoILS(pedidos, solucao, melhorMultaOriginal);
    pedidos.setMultaTotal(melhorMultaNovaSolucao);
    // Calcula a duracao
    fim = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> tempoILS = fim - inicio;

    std::cout << "Melhor multa meta-heuristica: " << pedidos.getMultaTotal() << std::endl;

    std::cout << "O Guloso demorou " << tempoGuloso.count() << " ms." << std::endl;
    std::cout << "O VND demorou " << tempoVND.count() << " ms." << std::endl;
    std::cout << "A meta-heuristica demorou " << tempoILS.count() << " ms." << std::endl;
    return 0;
}
