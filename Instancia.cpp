#pragma once
#include "Instancia.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


void leitor_de_instancias(
    std::string nome_arquivo,
    int& n_linhas_ref,
    int& n_produtos_ref,
    std::vector<int>& produtos_id_ref,
    std::vector<int>& produtos_custo_ref,
    std::vector<std::vector<int>>& tempo_preparo_ref) {
    
    std::string linha;
    std::ifstream arquivo(nome_arquivo);
    
    if (arquivo.is_open())
    {
        arquivo >> n_linhas_ref >> n_produtos_ref;

        // lendo array de produtos
        for (int i = 0; i < n_produtos_ref; i++) {
            int produto;
            arquivo >> produto;
            produtos_custo_ref.push_back(produto);
            produtos_id_ref.push_back(i + 1);
        }
        
        // lendo matriz de tempo de preparo
        for (int i = 0; i < n_produtos_ref; i++) {
            std::vector<int> linha;
            for (int j = 0; j < n_produtos_ref; j++) {
                int tempo;
                arquivo >> tempo;
                linha.push_back(tempo);
            }
            tempo_preparo_ref.push_back(linha);
        }
        arquivo.close();
    } else {
        std::cout << "Unable to open file";
    }
}