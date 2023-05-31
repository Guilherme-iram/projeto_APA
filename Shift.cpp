#pragma once

#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"
#include "math.h"

class Shiftline
{
    public:

        Instancia instancia;
        
        Shiftline(const Instancia& instancia)
        {
            this->instancia = instancia;
        };
        
        void run(Solution& s)
        {
            int deltaCusto = 0;
            int bestDeltaCusto = 0;
            
            int greater_n_l = 0;
            int greater_cost = s.linhas_producao[0].custo;

            int best_i = 0;
            int best_size = 0;

            for (int n_l = 1; n_l < instancia.n_linhas; n_l++)
            {
                if (s.linhas_producao[n_l].custo > greater_cost)
                {
                    greater_cost = s.linhas_producao[n_l].custo;
                    greater_n_l = n_l;
                }
            }

            if (s.linhas_producao[greater_n_l].produtos.size() == 4)
            {
                return;
            }

            for (int size = 1; size < s.linhas_producao[greater_n_l].produtos.size() - 3; size++)
            {
                for (int i = 1; i < s.linhas_producao[greater_n_l].produtos.size() - size - 1; i++)
                {
                    deltaCusto = costShift(s, greater_n_l, i, size);

                    if (deltaCusto < bestDeltaCusto)
                    {
                        bestDeltaCusto = deltaCusto;
                        best_i = i;
                        best_size = size;
                    }
                }
            }
            
            if (bestDeltaCusto < 0)
            {
                movement(s, greater_n_l, best_i, best_size);
                s.custo_total += bestDeltaCusto;
            }
            
        }

        void movement(Solution& s, int n_l, int i, int size)
        {
            std::vector<int> aux(s.linhas_producao[n_l].produtos.begin() + i, s.linhas_producao[n_l].produtos.begin() + i + size);
            int dest_index = s.linhas_producao[n_l].produtos.size() - size;

            // Copia do i + size até o final do array para o inicio do array + i 
            std::copy(s.linhas_producao[n_l].produtos.begin() + i + size, s.linhas_producao[n_l].produtos.end(), s.linhas_producao[n_l].produtos.begin() + i);
            
            // Copia do aux para o final do array, finalizando o shift do bloco size para o final do array
            std::copy(aux.begin(), aux.end(), s.linhas_producao[n_l].produtos.begin() + dest_index);
        }

        int costShift(const Solution& s, int n_l, int i, int size)
        {
            int deltaCusto = 0;
            int size_l = s.linhas_producao[n_l].produtos.size();
            
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i + size - 1] - 1][s.linhas_producao[n_l].produtos[i + size] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i + size] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[size_l - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];

            return deltaCusto;
        }
};