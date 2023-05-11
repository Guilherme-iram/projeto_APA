#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"
#include <cstdlib>
#include <ctime>
#include <tuple>

using namespace std;

void construcao(Solution& s, const Instancia& instancia)
{

    static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    seed += 12345;
    srand(seed);

    vector<int> produtos_id(instancia.produtos);
    vector<Linha_producao> linhas_de_producao = {};
    
    unsigned int i, j;
    int rand_index;
    int rand_produto;

    int size_produtos;
    int melhor_custo;


    for (i = 0; i < instancia.n_linhas; i++)
    {
        rand_index = rand() % (instancia.n_produtos - 1);
        rand_produto = produtos_id[rand_index];
        produtos_id.erase(produtos_id.begin() + rand_index);

        linhas_de_producao.push_back({instancia.custo_producao[rand_produto - 1], {rand_produto}});
    }
    
    for (i = 0; i < produtos_id.size() ; i++)
    {
        melhor_custo = 9999;

        int melhor_posicao[] = {0, 0};


        for (j = 0; j < instancia.n_linhas; j++)
        {
            size_produtos = linhas_de_producao[j].produtos.size();

            // Compara se o custo de produção do produto atual é menor que o custo de produção do produto na posição 0 da linha de producao j
            if (instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1] < melhor_custo)
            {
                melhor_custo = instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1];
                melhor_posicao[0] = j;
                melhor_posicao[1] = 0;
            }

            // Compara se o custo de produção do produto atual é menor que o custo de produção do produto no final da linha de producao j
            if (instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1] < melhor_custo)
            {
                melhor_custo = instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1];
                melhor_posicao[0] = j;
                melhor_posicao[1] = size_produtos;
            }
        }

        linhas_de_producao[melhor_posicao[0]].produtos.insert(linhas_de_producao[melhor_posicao[0]].produtos.begin() + melhor_posicao[1], produtos_id[i]);
        linhas_de_producao[melhor_posicao[0]].custo += melhor_custo + instancia.custo_producao[produtos_id[i] - 1];
    }

    Solution solution = Solution(linhas_de_producao, instancia);
    s = solution;
}

