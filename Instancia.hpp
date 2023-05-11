#pragma once

#include <vector>

typedef struct {
    unsigned int n_linhas;
    unsigned int n_produtos;
    std::vector<int> produtos;
    std::vector<int> custo_producao;
    std::vector<std::vector<int>> tempo_preparo;
} Instancia;


