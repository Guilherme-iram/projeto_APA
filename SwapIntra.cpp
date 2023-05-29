#pragma once

#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"
#include "math.h"

class SwapIntra
{
    public:

        Instancia instancia;
        
        SwapIntra(const Instancia& instancia)
        {
            this->instancia = instancia;
        };
        
        void run(Solution& s)
        {
            int deltaCusto;
            int bestDeltaCusto = 0;
            int best_n_l = 0;
            int best_i = 0;
            int best_j = 0;

            for (int n_l = 0; n_l < instancia.n_linhas; n_l++)
            {
                for (int i = 0; i < s.linhas_producao[n_l].produtos.size() - 1; i++)
                {
                    for (int j = i + 1; j < s.linhas_producao[n_l].produtos.size(); j++)
                    {
                        deltaCusto = costSwap(s, n_l, i, j);

                        if (deltaCusto < bestDeltaCusto)
                        {
                            bestDeltaCusto = deltaCusto;
                            best_n_l = n_l;
                            best_i = i;
                            best_j = j;
                        }
                    }
                }
            }
            
            if (bestDeltaCusto < 0)
            {
                movement(s, best_n_l, best_i, best_j);
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
                // std::std::cout << "CASO 1" << std::std::endl;
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
                // std::std::cout << "CASO 2" << std::std::endl;
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
                caso = 2;
            }
            else if (i == 0 && j > 1)
            {
                // std::std::cout << "CASO 3" << std::std::endl;
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
                // std::std::cout << "CASO 4" << std::std::endl;
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
                caso = 4;
            }
            else if (j == (size_p - 1) && i < (size_p - 2))
            {
                // std::std::cout << "CASO 5" << std::std::endl;
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