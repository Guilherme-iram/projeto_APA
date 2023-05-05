#pragma once

#include <vector>

typedef struct {
    int n_linhas;
    int n_produtos;
    std::vector<int> produtos;
    std::vector<int> custo_producao;
    std::vector<std::vector<int>> tempo_preparo;
} Instancia;


