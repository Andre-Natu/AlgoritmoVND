#ifndef PEDIDODATA_H
#define PEDIDODATA_H

#include <iostream>
#include <vector>

// Definição da struct
struct Solucao {
    int indexPedidoAnterior;
    int indexPedido;
    int tempoConclusao;
    int multa;


    // Construtor que inicializa todos os membros com valores zero
    Solucao() : indexPedidoAnterior(0), indexPedido(0), tempoConclusao(0), multa(0) {}
};

class PedidoData {

    public:
        std::vector<int> tempoProducao;
        std::vector<int> prazo;
        std::vector<int> valorMulta;
        std::vector<std::vector<int>> matrizTempoTransicao;


        explicit PedidoData(const std::string& nomeArquivo);
        void exibirDados() const;

        [[nodiscard]] int getNumeroPedidos() const;
        [[nodiscard]] int getMultaTotal() const;
        void adicionarMulta(int multa);
        void setMultaTotal(int multa);
    private:
        int numeroPedidos = 0;
        int multaTotal = 0;

        bool lerDadosDoArquivo(const std::string& nomeArquivo);
};



#endif //PEDIDODATA_H
