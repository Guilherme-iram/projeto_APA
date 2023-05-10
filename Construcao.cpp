#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"
#include <cstdlib>
#include <ctime>
#include <tuple>

using namespace std;

Solution construcao(Instancia instancia)
{
    unsigned seed = time(0);
    srand(seed);

    vector<int> produtos_id(instancia.produtos);

    vector<Linha_producao> linhas_de_producao;
    
    int i, j;
    int rand_index;
    int rand_produto;

    
    int size_produtos;
    int melhor_custo;
    int tamanho_linha_de_producao;


    for (i = 0; i < instancia.n_linhas; i++)
    {
        rand_index = rand() % (instancia.n_produtos - 1);
        rand_produto = produtos_id[rand_index];
        produtos_id.erase(produtos_id.begin() + rand_index);

        linhas_de_producao.push_back({instancia.custo_producao[rand_produto - 1], {rand_produto}});
    }
    
   
    // Tomar cuidado com o make_tuple: complexidade O(n)
    for (i = 0; i < produtos_id.size() ; i++)
    {
        melhor_custo = 999;
        std::tuple<int, int> melhor_posicao(0,0);
        for (j = 0; j < linhas_de_producao.size(); j++)
        {
            size_produtos = linhas_de_producao[j].produtos.size();

            // Compara se o custo de produção do produto atual é menor que o custo de produção do produto na posição 0 da linha de producao j
            if (instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1] < melhor_custo)
            {
                melhor_custo = instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1];
                melhor_posicao = std::make_tuple(j, 0);
            }

            // Compara se o custo de produção do produto atual é menor que o custo de produção do produto no final da linha de producao j
            if (instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1] < melhor_custo)
            {
                melhor_custo = instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1];
                melhor_posicao = std::make_tuple(j, linhas_de_producao[j].produtos.size());
            }
        }
        
        linhas_de_producao[std::get<0>(melhor_posicao)].produtos.insert(linhas_de_producao[std::get<0>(melhor_posicao)].produtos.begin() + std::get<1>(melhor_posicao), produtos_id[i]);
        linhas_de_producao[std::get<0>(melhor_posicao)].custo += melhor_custo + instancia.custo_producao[produtos_id[i] - 1];
    }


    for (i = 0; i < linhas_de_producao.size(); i++)
    {
        cout << "Linha " << i << ": ";
        tamanho_linha_de_producao = linhas_de_producao[i].produtos.size();

        for (j = 0; j < tamanho_linha_de_producao ; j++)
        {
            cout << linhas_de_producao[i].produtos[j] << " ";
        }
        cout << "\nCusto: " << linhas_de_producao[i].custo << endl;
    }

    Solution solution = Solution(linhas_de_producao, 0, instancia);
    solution.custo_total();

    return solution;
}

