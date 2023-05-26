#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"
#include "math.h"

class Pertubacao_double_swap
{
    public:

        Instancia instancia;
        
        Pertubacao_double_swap (const Instancia& instancia)
        {
            this->instancia = instancia;
        };
        
        void run(Solution& s)
        {   
            
            int rand_l =  rand() % instancia.n_linhas;
            int size_l = s.linhas_producao[rand_l].produtos.size();
            int rand_i = 1 + rand() % (s.linhas_producao[rand_l].produtos.size() > 2? s.linhas_producao[rand_l].produtos.size() - 2 : 2);
            int rand_j = 1 + rand() % (s.linhas_producao[rand_l].produtos.size() > 2? s.linhas_producao[rand_l].produtos.size() - 2 : 2);
            int rand_k = 1 + rand() % (s.linhas_producao[rand_l].produtos.size() > 2? s.linhas_producao[rand_l].produtos.size() - 2 : 2);
            int rand_m = 1 + rand() % (s.linhas_producao[rand_l].produtos.size() > 2? s.linhas_producao[rand_l].produtos.size() - 2 : 2);
            int aux;

            if (rand_i > rand_j)
            {
                aux = rand_i;
                rand_i = rand_j;
                rand_j = aux;
            }

            if (rand_k > rand_m)
            {
                aux = rand_k;
                rand_k = rand_m;
                rand_m = aux;
            }

            if (rand_i != rand_j && size_l > 3)
            {
                int delta_custo = 0;

                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_i - 1] - 1][s.linhas_producao[rand_l].produtos[rand_i] - 1];
                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_i] - 1][s.linhas_producao[rand_l].produtos[rand_i + 1] - 1];
                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_j - 1] - 1][s.linhas_producao[rand_l].produtos[rand_j] - 1];
                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_j] - 1][s.linhas_producao[rand_l].produtos[rand_j + 1] - 1];

                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_i - 1] - 1][s.linhas_producao[rand_l].produtos[rand_j] - 1];
                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_j] - 1][s.linhas_producao[rand_l].produtos[rand_i + 1] - 1];
                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_j - 1] - 1][s.linhas_producao[rand_l].produtos[rand_i] - 1];
                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_i] - 1][s.linhas_producao[rand_l].produtos[rand_j + 1] - 1];

                s.linhas_producao[rand_l].custo += delta_custo;
                movement(s, rand_l, rand_i, rand_j);
            }
            if (rand_k != rand_m && size_l > 3)
            {
                int delta_custo = 0;

                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_k - 1] - 1][s.linhas_producao[rand_l].produtos[rand_k] - 1];
                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_k] - 1][s.linhas_producao[rand_l].produtos[rand_k + 1] - 1];
                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_m - 1] - 1][s.linhas_producao[rand_l].produtos[rand_m] - 1];
                delta_custo -= instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_m] - 1][s.linhas_producao[rand_l].produtos[rand_m + 1] - 1];

                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_k - 1] - 1][s.linhas_producao[rand_l].produtos[rand_m] - 1];
                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_m] - 1][s.linhas_producao[rand_l].produtos[rand_k + 1] - 1];
                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_m - 1] - 1][s.linhas_producao[rand_l].produtos[rand_k] - 1];
                delta_custo += instancia.tempo_preparo[s.linhas_producao[rand_l].produtos[rand_k] - 1][s.linhas_producao[rand_l].produtos[rand_m + 1] - 1];

                s.linhas_producao[rand_l].custo += delta_custo;
                movement(s, rand_l, rand_k, rand_m);
            }

        }

        void movement(Solution& s, int n_l, int i, int j)
        {
            int aux = s.linhas_producao[n_l].produtos[i];
            s.linhas_producao[n_l].produtos[i] = s.linhas_producao[n_l].produtos[j];
            s.linhas_producao[n_l].produtos[j] = aux;
        };

};