#pragma once
#include <iostream>
#include "Solution.hpp"
#include "Instancia.hpp"
#include <math.h>


Solution::Solution(std::vector<Linha_producao> Linhas, Instancia instancia){
    this->linhas_producao = Linhas;
    this->instancia = instancia;
    this->custo_total = Linhas[0].custo;
}

Solution::Solution(const Solution& s){
    this->linhas_producao = s.linhas_producao;
    this->custo_total = s.custo_total;
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

void Solution::calcula_custo_total(){
    
    this->custo_linhas();
    
    int custo_maximo = this->linhas_producao[0].custo;

    for (unsigned int i = 1; i < this->linhas_producao.size(); i++){
        if (linhas_producao[i].custo > custo_maximo){           
            custo_maximo = linhas_producao[i].custo;
        }
    }

    this->custo_total = custo_maximo;

} 

void Solution::print_solution(){

    std::cout << "Tempo total: " << this->custo_total << std::endl;
    std::cout << "Linhas de producao: " << std::endl;
    for (unsigned int i = 0; i < this->linhas_producao.size(); i++){
        std::cout << "Linha " << i + 1 << ": ";
        for (unsigned int j = 0; j < this->linhas_producao[i].produtos.size(); j++){
            std::cout << this->linhas_producao[i].produtos[j] << " ";
        }
        std::cout << std::endl;
    }
}