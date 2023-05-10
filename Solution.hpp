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
        Solution(std::vector<Linha_producao> linhas,
        int tempo_total, Instancia instancia);
        

        std::vector<Linha_producao> linhas_producao;
        int tempo_total = 9999;
        Instancia instancia;

        void custo_linhas();
        int custo_total();
        void print_solution();
};