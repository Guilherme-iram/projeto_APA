#pragma once
#include <vector>

typedef struct {
    int custo;
    std::vector<int> produtos;
} Linha_producao;


class Solution{
    public:
        Solution();
        Solution(const Solution& s);
        Solution(std::vector<Linha_producao> linhas, Instancia instancia);
        
        int custo_total;
        Instancia instancia;
        std::vector<Linha_producao> linhas_producao;

        void custo_linhas();
        void calcula_custo_total();
        void print_solution();
};