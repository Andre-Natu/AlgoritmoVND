#include "ILS.h"

#include <random>

#include "AlgoritmoGuloso.h"
#include "SwapAdjacencia.h"
#include "VND.h"

bool criterioAceitacao(PedidoData& pedidos, std::vector<Solucao>& solucao , std::vector<Solucao>& novaSolucao) {

    int novaMultaTotal = 0;
    int multaAntiga = 0;
    for (int i = 0; i < pedidos.getNumeroPedidos(); i++) {
        novaMultaTotal += novaSolucao[i].multa;
        multaAntiga += solucao[i].multa;
    }

    //  se a nova solução for melhor, copia ela para a solução.
    if (novaMultaTotal < multaAntiga) {
        std::copy(novaSolucao.begin(), novaSolucao.end(), solucao.begin());
        pedidos.setMultaTotal(novaMultaTotal);
        return true;
    }
    return false;
}

void calcularSolucaoILS(PedidoData& pedidos, std::vector<Solucao>& solucao) {
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

        // Perturbação
        trocarElementos(numeroAleatorio1,numeroAleatorio2,novaSolucao, pedidos);
        trocarElementos(numeroAleatorio3,numeroAleatorio4,novaSolucao, pedidos);

        // Busca Local
        calcularSolucaoVND(pedidos, novaSolucao);

        // testa para ver se a nova solução é melhor, se for, redefine o criterio de parada.
        if (criterioAceitacao(pedidos,solucao, novaSolucao)) {
            k = 0;
        } else {
            k++;
        }
    }


}
