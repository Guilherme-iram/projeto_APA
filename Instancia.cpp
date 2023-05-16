#pragma once
#include "Instancia.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


Instancia leitor_de_instancias(std::string nome_arquivo) {
    
    unsigned int n_linhas;
    unsigned int n_produtos;
    std::vector<int> produtos_id;
    std::vector<int> produtos_custo;
    std::vector<std::vector<int>> tempo_preparo;
    std::string linha;
    std::ifstream arquivo(nome_arquivo);
    
    if (arquivo.is_open())
    {
        int tempo;
        arquivo >> n_linhas >> n_produtos;

        // lendo array de produtos
        for (unsigned int i = 0; i < n_produtos; i++) {
            int produto;
            arquivo >> produto;
            produtos_custo.push_back(produto);
            produtos_id.push_back(i + 1);
        }
        
        // lendo matriz de tempo de preparo
        for (unsigned int i = 0; i < n_produtos; i++) {
            std::vector<int> linha;
            for (unsigned int j = 0; j < n_produtos; j++) {
                
                arquivo >> tempo;
                linha.push_back(tempo);
            }
            tempo_preparo.push_back(linha);
        }
        arquivo.close();
        return {n_linhas, n_produtos, produtos_id, produtos_custo, tempo_preparo};
        
    } else {
    
        std::cout << "Unable to open file";
        return {0, 0, produtos_id, produtos_custo, tempo_preparo};

    }
}