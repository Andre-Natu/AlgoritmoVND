//
// Created by sousa on 18/09/2024.
//

#include "PedidoData.h"
#include <iostream>
#include <fstream>

PedidoData::PedidoData(const std::string& nomeArquivo) {
    if (!lerDadosDoArquivo(nomeArquivo)) {
        std::cerr << "Falha ao ler os dados do arquivo." << std::endl;
    }
}

bool PedidoData::lerDadosDoArquivo(const std::string& nomeArquivo) {
    std::ifstream entrada(nomeArquivo);

    if (!entrada) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return false;
    }

    entrada >> numeroPedidos;

    tempoProducao.resize(numeroPedidos);
    prazo.resize(numeroPedidos);
    valorMulta.resize(numeroPedidos);

    for (int i = 0; i < numeroPedidos; ++i) {
        entrada >> tempoProducao[i];
    }

    for (int i = 0; i < numeroPedidos; ++i) {
        entrada >> prazo[i];
    }

    for (int i = 0; i < numeroPedidos; ++i) {
        entrada >> valorMulta[i];
    }

    matrizTempoTransicao.resize(numeroPedidos + 1, std::vector<int>(numeroPedidos));

    for (int i = 0; i < numeroPedidos + 1; ++i) {
        for (int j = 0; j < numeroPedidos; ++j) {
            entrada >> matrizTempoTransicao[i][j];
        }
    }

    entrada.close();
    return true;
}

void PedidoData::exibirDados() const {
    std::cout << "Numero de pedidos: " << numeroPedidos << std::endl;
    std::cout << "tempo de Producao: ";
    for (const auto& val : tempoProducao) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Prazo: ";
    for (const auto& val : prazo) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "valor da Multa: ";
    for (const auto& val : valorMulta) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Matriz com o Tempo de Transicao: " << std::endl;
    for (const auto& row : matrizTempoTransicao) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int PedidoData::getNumeroPedidos() const {
    return numeroPedidos;
}

int PedidoData::getMultaTotal() const {
    return multaTotal;
}

void PedidoData::setMultaTotal(const int multa) {
    multaTotal = multa;
}

void PedidoData::adicionarMulta(const int multa) {

    multaTotal += multa;
}