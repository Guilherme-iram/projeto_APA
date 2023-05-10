#pragma once
#include <iostream>
#include "Solution.hpp"
#include "Instancia.hpp"


Solution::Solution(std::vector<Linha_producao> linhas, int tempo_total, Instancia instancia){
    this->linhas_producao = linhas;
    this->tempo_total = tempo_total;
    this->instancia = instancia;
}

void Solution::custo_linhas(){
    int custo_linha;
    int len_linha;

    for (int i = 0; i < linhas_producao.size() ; i++){
        custo_linha = 0;
        len_linha = linhas_producao[i].produtos.size();
        for (int j = 0; j < len_linha - 1; j++){
            custo_linha += instancia.tempo_preparo[linhas_producao[i].produtos[j] - 1][linhas_producao[i].produtos[j + 1] - 1];
            custo_linha += instancia.custo_producao[linhas_producao[i].produtos[j] - 1];
        }
        custo_linha += instancia.custo_producao[linhas_producao[i].produtos[len_linha - 1] - 1];
        linhas_producao[i].custo = custo_linha;
    }
}

int Solution::custo_total(){
    
    this->custo_linhas();
    int custo_maximo = this->linhas_producao[0].custo;

    for (int i = 0; i < this->linhas_producao.size(); i++){
        if (linhas_producao[i].custo > custo_maximo){
            
            custo_maximo = linhas_producao[i].custo;
        }
        // std::cout << "Custo da linha " << i + 1 << ": " << linhas_producao[i].custo << std::endl;
    }
    return custo_maximo;
}