#pragma once 

#include "Solution.hpp"
#include "Instancia.hpp"
#include <iostream>

class Reinsertion
{
    public:
        Instancia instancia;

        Reinsertion(const Instancia &instancia)
        {
            this->instancia = instancia;
        };

        void run(Solution &s)
        {
                int deltaCusto;
                int bestDeltaCusto = 0;
                int best_l1 = 0;
                int best_l2 = 0;
                int best_i = 0;
                int best_j = 0;

                for (int l1 = 0; l1 < instancia.n_linhas - 1; l1++)
                {
                    if(!(s.linhas_producao[l1].produtos.size() > 1)) continue;

                    for (int l2 = l1 + 1; l2 < instancia.n_linhas; l2++)
                    {   
                        for (int i = 0; i < s.linhas_producao[l1].produtos.size(); i++)
                        {
                            for (int j = 0; j <= s.linhas_producao[l2].produtos.size(); j++)
                                {
                                    deltaCusto = costReinsertion(s, l1, l2, i, j);

                                    if (deltaCusto < bestDeltaCusto)
                                    {
                                        bestDeltaCusto = deltaCusto;
                                        best_l1 = l1;
                                        best_l2 = l2;
                                        best_i = i;
                                        best_j = j;
                                    }
                            }
                        }
                    }
                }

                if (bestDeltaCusto < 0)
                {
                    movement(s, best_l1, best_l2, best_i, best_j);
                }
                
        }

        void movement(Solution &s, int l1, int l2, int i, int j)
        {

            int aux = s.linhas_producao[l1].produtos[i];
            int size_j = s.linhas_producao[l2].produtos.size();

            if (j == size_j)
            {
                s.linhas_producao[l1].produtos.erase(s.linhas_producao[l1].produtos.begin() + i);
                s.linhas_producao[l2].produtos.push_back(aux);
            }
            else
            {
                s.linhas_producao[l1].produtos.erase(s.linhas_producao[l1].produtos.begin() + i);
                s.linhas_producao[l2].produtos.insert(s.linhas_producao[l2].produtos.begin() + j, aux);
            }

        };


        int costReinsertion(const Solution &s, int l1, int l2, int i, int j)
        {
            int deltaCusto = 0;
            int caso = 0;

            int size_i = s.linhas_producao[l1].produtos.size();
            int size_j = s.linhas_producao[l2].produtos.size();

            if (i == 0 && j == 0)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l2].produtos[j] - 1];

                caso = 1;
            }

            else if (i == 0 && j <= size_j - 1)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l2].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l2].produtos[j] - 1];

                caso = 2;
            }


            else if (i == size_i - 1 && j == 0)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l2].produtos[j] - 1];

                caso = 3;
            }

            else if (i == size_i - 1 && j <= size_j - 1)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l2].produtos[j] - 1];
                
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l2].produtos[j] - 1];

                caso = 4;
            }
            

            else if (i < size_i - 1 && j == 0)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l2].produtos[j] - 1];

                caso = 5;
            }

            else if (i == 0 && j == size_j)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];

                caso = 6;
            }
            
            else if (i == size_i -1 && j == size_j)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];

                caso = 7;
            }

            else if (i >= 1 && j == size_j)
            {

                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];

                caso = 8;
            }

            else if (i < size_i - 1 && j <= size_j - 1)
            {
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l2].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i - 1] - 1][s.linhas_producao[l1].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l2].produtos[j - 1] - 1][s.linhas_producao[l1].produtos[i] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[l1].produtos[i] - 1][s.linhas_producao[l2].produtos[j] - 1];

                caso = 9;
            }
        
            return deltaCusto;
        }
};