cmake_minimum_required(VERSION 3.29)
project(ProjetoAPA)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjetoAPA main.cpp
        PedidoData.cpp
        PedidoData.h
        AlgoritmoGuloso.cpp
        AlgoritmoGuloso.h
        SwapAdjacencia.cpp
        SwapAdjacencia.h
        Swap.cpp
        Swap.h
        VND.cpp
        VND.h
        opt2.cpp
        opt2.h
        ReInsert.cpp
        ReInsert.h
        ILS.cpp
        ILS.h)
