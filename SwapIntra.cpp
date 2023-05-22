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
            int best_caso = 0;
            std::vector<int> vec_aux = {0, 0};
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
                        vec_aux = costSwap(s, n_l, i, j);
                        deltaCusto = vec_aux[1];

                        if (deltaCusto < bestDeltaCusto)
                        {
                            bestDeltaCusto = deltaCusto;
                            best_n_l = n_l;
                            best_i = i;
                            best_j = j;
                            best_caso = vec_aux[0];
                        }
                    }
                }
            }
            
            if (bestDeltaCusto < 0)
            {
                // std::cout << "SwapIntra ENCONTRADO! " << std::endl;
                // std::cout << "DELTA: " << bestDeltaCusto << std::endl;
                // std::cout << "Linha: " << best_n_l << std::endl;
                // std::cout << "i: " << best_i << std::endl;
                // std::cout << "j: " << best_j << std::endl;
                // std::cout << "Caso: " << best_caso << std::endl;

                swap(s, best_n_l, best_i, best_j);
                s.media_custo += (bestDeltaCusto / instancia.n_linhas);
                double nova_variancia = 0;
                
                for (int i = 0; i < instancia.n_linhas; i++)
                {
                    nova_variancia += pow((s.media_custo - s.linhas_producao[i].custo), 2);
                }
                s.variancia_custo = nova_variancia;
            }
            
        }

        void swap(Solution& s, int n_l, int i, int j)
        {
            int aux = s.linhas_producao[n_l].produtos[i];
            s.linhas_producao[n_l].produtos[i] = s.linhas_producao[n_l].produtos[j];
            s.linhas_producao[n_l].produtos[j] = aux;
        };

        std::vector<int> costSwap(const Solution& s, int n_l, int i, int j)
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
                    return {caso, deltaCusto};
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
                // std::std::cout << "CASO 6" << std::std::endl;
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
                // std::std::cout << "Caso BASE" << std::std::endl;
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

            return {caso, deltaCusto};
        }
};