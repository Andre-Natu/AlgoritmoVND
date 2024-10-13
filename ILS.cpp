#include "ILS.h"

#include <random>

#include "AlgoritmoGuloso.h"
#include "opt2.h"
#include "ReInsert.h"
#include "SwapAdjacencia.h"
#include "VND.h"

bool criterioAceitacao(PedidoData& pedidos, std::vector<Solucao>& solucao , std::vector<Solucao>& novaSolucao,int melhorMultaNovaSolucao, int melhorMultaTotal) {


    std::cout << "Valor nova Multa ILS: " << melhorMultaNovaSolucao << std::endl;
    std::cout << "Valor Multa VND Antiga: " << melhorMultaTotal << std::endl;
    std::cout << "Valor Melhor Multa total faz o L: " << pedidos.getMultaTotal() << std::endl;



    //  se a nova solução for melhor, copia ela para a solução.
    if (melhorMultaNovaSolucao < melhorMultaTotal) {
        std::copy(novaSolucao.begin(), novaSolucao.end(), solucao.begin());
        pedidos.setMultaTotal(melhorMultaNovaSolucao);
        return true;
    }
    return false;
}

int calcularSolucaoILS(PedidoData& pedidos, std::vector<Solucao>& solucao, int melhorMultaTotal) {
    // busca local e solucao inicial
    //calcularSolucaoGulosa(pedidos, solucao);
    //calcularSolucaoVND(pedidos, solucao);

    int k = 0;
    while (k < 10) {
        std::vector<Solucao> novaSolucao = solucao;

        // processo para gerar um número aleatório.
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, pedidos.getNumeroPedidos() - 1);
        const int numeroAleatorio1 = distribution(gen);
        const int numeroAleatorio2 = distribution(gen);
        const int numeroAleatorio3 = distribution(gen);
        const int numeroAleatorio4 = distribution(gen);
        const int numeroAleatorio5 = distribution(gen);
        const int numeroAleatorio6 = distribution(gen);


        int melhorMultaNovaSolucao = melhorMultaTotal;
        // Perturbação
        melhorMultaNovaSolucao = trocarElementos(numeroAleatorio1,numeroAleatorio2,novaSolucao, pedidos);
        melhorMultaNovaSolucao = trocarElementos(numeroAleatorio3,numeroAleatorio4,novaSolucao, pedidos);
        melhorMultaNovaSolucao = trocarElementos(numeroAleatorio5,numeroAleatorio6,novaSolucao, pedidos);

        std::cout << "Multa da nova solucao apos o swap: " << melhorMultaNovaSolucao << std::endl;
        std::cout << "Multa Antiga sem mudar: " << melhorMultaTotal << std::endl;

        // Busca Local
        melhorMultaNovaSolucao = calcularSolucaoVND(pedidos, novaSolucao, melhorMultaNovaSolucao);

        // testa para ver se a nova solução é melhor, se for, redefine o criterio de parada.
        if (criterioAceitacao(pedidos,solucao, novaSolucao, melhorMultaNovaSolucao, melhorMultaTotal)) {
            melhorMultaTotal = melhorMultaNovaSolucao;
            k = 0;
        } else {
            k++;
        }
    }


    return melhorMultaTotal;
}
