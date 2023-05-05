#pragma once
#include <vector>

typedef struct {
    int custo;
    std::vector<int> produtos;
} Linha_producao;


class Solution{
    public:
        Solution(std::vector<Linha_producao> linhas,
        int tempo_total, Instancia instancia);

        std::vector<Linha_producao> linhas_producao;
        int tempo_total = 9999;
        Instancia instancia;

        void custo_linhas();
        int custo_total();
};