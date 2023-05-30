#pragma once

#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"
#include "math.h"

class Swapline
{
    public:

        Instancia instancia;
        
        Swapline(const Instancia& instancia)
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
            int best_j = 0;

            for (int n_l=1; n_l < instancia.n_linhas; n_l++)
            {
                if (s.linhas_producao[n_l].custo > greater_cost)
                {
                    greater_cost = s.linhas_producao[n_l].custo;
                    greater_n_l = n_l;
                }
            }

            if (s.linhas_producao[greater_n_l].produtos.size() == 1)
            {
                return;
            }

            for (int i = 0; i < s.linhas_producao[greater_n_l].produtos.size() - 1; i++)
            {
                for (int j = i + 1; j < s.linhas_producao[greater_n_l].produtos.size(); j++)
                {
                    deltaCusto  = costSwap(s, greater_n_l, i, j);
                    
                    if (deltaCusto < bestDeltaCusto)
                    {
                        bestDeltaCusto = deltaCusto;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
            
            
            if (bestDeltaCusto < 0)
            {
                movement(s, greater_n_l, best_i, best_j);
                s.custo_total += bestDeltaCusto;
            }
            
        }

        void movement(Solution& s, int n_l, int i, int j)
        {
            int aux = s.linhas_producao[n_l].produtos[i];
            s.linhas_producao[n_l].produtos[i] = s.linhas_producao[n_l].produtos[j];
            s.linhas_producao[n_l].produtos[j] = aux;
        };

        int costSwap(const Solution& s, int n_l, int i, int j)
        {
            int deltaCusto = 0;
            int caso = 0;
            int size_p = s.linhas_producao[n_l].produtos.size();

            if (i == 0 && j == size_p - 1)
            {
                if (size_p == 2)
                {
                    deltaCusto = - instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j] - 1]
                                 + instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                    return deltaCusto;
                }

                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                caso = 1;
            }

            else if (i == 0 && j == 1)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
                
                caso = 2;
            }
            else if (i == 0 && j > 1)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
                
                caso = 3;
            }
            

            else if (j == (size_p - 1) && i == (size_p - 2))
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                
                caso = 4;
            }
            else if (j == (size_p - 1) && i < (size_p - 2))
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                
                caso = 5;
            }
            else if (i + 1 == j)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
                
                caso = 6;
            }
            else
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
                
                caso = -1;
            }

            return deltaCusto;
        }
};