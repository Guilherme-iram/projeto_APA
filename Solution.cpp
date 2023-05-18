#pragma once
#include <iostream>
#include "Solution.hpp"
#include "Instancia.hpp"


Solution::Solution(std::vector<Linha_producao> linhas, int tempo_total, Instancia instancia){
    this->linhas_producao = linhas;
    this->tempo_total = tempo_total;
    this->instancia = instancia;
}

Solution::Solution(std::vector<Linha_producao> Linhas, Instancia instancia){
    this->linhas_producao = Linhas;
    this->instancia = instancia;
    this->tempo_total = Linhas[0].custo;

    // Temporario
    for (unsigned int i = 1; i < Linhas.size(); i++){
        if (Linhas[i].custo > this->tempo_total){
            this->tempo_total = Linhas[i].custo;
        }
    }
}

Solution::Solution(const Solution& s){
    this->linhas_producao = s.linhas_producao;
    this->tempo_total = s.tempo_total;
    this->instancia = s.instancia;
}

Solution::Solution(){

}


void Solution::custo_linhas(){
    
    int custo_linha;
    unsigned int len_linha;

    for (unsigned int i = 0; i < linhas_producao.size() ; i++){
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
    int soma_custos = 0;
    for (unsigned int i = 0; i < this->linhas_producao.size(); i++){
        if (linhas_producao[i].custo > custo_maximo){           
            custo_maximo = linhas_producao[i].custo;
        }
        soma_custos += linhas_producao[i].custo;
    }
    // ISSO AQUI TÁ ERRADO, TEM QUE AJEITAR, É PROVISÓRIO PRA VER O SWAP FUNCIONANDO
    return soma_custos;
}

void Solution::print_solution(){

    std::cout << "Tempo total: " << this->custo_total() << std::endl;
    for (unsigned int i = 0; i < this->linhas_producao.size(); i++){
        std::cout << "Linha " << i + 1 << ": ";
        for (unsigned int j = 0; j < this->linhas_producao[i].produtos.size(); j++){
            std::cout << this->linhas_producao[i].produtos[j] << " ";
        }
        std::cout << std::endl;
    }
}