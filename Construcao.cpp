#include "Solution.hpp"
#include "Instancia.hpp"
#include "iostream"

#include <algorithm> 
#include <cstdlib>
#include <tuple>

using namespace std;

typedef struct{
    int custo;
    int posicao;
    int linha;
} Insersao;

class Algoritmo
{
    public: 
        unsigned int index_aux;
        double alpha;
        Algoritmo(double a)
        {
            alpha = a;
            index_aux = 0; //time(0);
        };
        
        Solution construcao(const Instancia& instancia)
        {
            unsigned int seed = time(0); 
            srand(seed + index_aux++);

            vector<int> produtos_id(instancia.produtos);
            vector<Linha_producao> linhas_de_producao = {};
            
            unsigned int i, j;

            int size_produtos;
            int melhor_custo;

            std::random_shuffle(produtos_id.begin(), produtos_id.end());

            for (i = 0; i < instancia.n_linhas; i++)
            {
                linhas_de_producao.push_back({instancia.custo_producao[produtos_id[i] - 1], {produtos_id[i]}});
            }
            
            for (i = instancia.n_linhas; i < produtos_id.size() ; i++)
            {
                // melhor_custo = 9999;

                vector<Insersao> candidatos_posicao = {};
                Insersao posicao_candidato = {};

                for (j = 0; j < instancia.n_linhas; j++)
                {
                    size_produtos = linhas_de_producao[j].produtos.size();

                    posicao_candidato.custo = instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1];
                    posicao_candidato.posicao = 0;
                    posicao_candidato.linha = j;

                    candidatos_posicao.push_back(posicao_candidato);

                    posicao_candidato.custo = instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1];
                    posicao_candidato.posicao = size_produtos;
                    posicao_candidato.linha = j;

                    candidatos_posicao.push_back(posicao_candidato);

                    // Compara se o custo de produção do produto atual é menor que o custo de produção do produto na posição 0 da linha de producao j
                    // if (instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1] < melhor_custo)
                    // {
                    //     melhor_custo = instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[0] - 1];
                    //     melhor_posicao[0] = j;
                    //     melhor_posicao[1] = 0;
                    // }

                    // // Compara se o custo de produção do produto atual é menor que o custo de produção do produto no final da linha de producao j
                    // if (instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1] < melhor_custo)
                    // {
                    //     melhor_custo = instancia.tempo_preparo[linhas_de_producao[j].produtos[size_produtos - 1] - 1][produtos_id[i] - 1];
                    //     melhor_posicao[0] = j;
                    //     melhor_posicao[1] = size_produtos;
                    // }
                }

                // ordenar candidatos_posicao de acordo com o custo
                sort(candidatos_posicao.begin(), candidatos_posicao.end(), [](const Insersao& lhs, const Insersao& rhs) {
                    return lhs.custo < rhs.custo;
                });

                // calcular o número de candidatos a serem selecionados com base no valor de alpha
                int num_candidatos_selecionados = static_cast<int>(alpha * candidatos_posicao.size());

                // selecionar os candidatos iniciais
                vector<Insersao> candidatos_selecionados(candidatos_posicao.begin(), candidatos_posicao.begin() + num_candidatos_selecionados);

                // randomizar a lista de candidatos selecionados
                random_shuffle(candidatos_selecionados.begin(), candidatos_selecionados.end());

                // obter o melhor candidato a partir dos candidatos selecionados
                Insersao melhor_candidato = candidatos_selecionados[0];
                

                linhas_de_producao[melhor_candidato.linha].produtos.insert(linhas_de_producao[melhor_candidato.linha].produtos.begin() + melhor_candidato.posicao, produtos_id[i]);
            
            }

            Solution solution = Solution(linhas_de_producao, instancia);
            solution.calcula_custo_total();
            return solution;
        }
};



//         typedef struct{
//             int custo;
//             int posicao;
//             int linha;
//         }Insersao;

//         Solution construcao_melhor_insersao(const Instancia& instancia)
//         {
//             unsigned int seed = time(0); 
//             srand(seed + index_aux++);

//             vector<int> produtos_id(instancia.produtos);
//             vector<Linha_producao> linhas_de_producao = {};
            
//             int i, j, k;

//             int size_produtos;
//             int melhor_custo;

//             std::random_shuffle(produtos_id.begin(), produtos_id.end());
            
//             for (i = 0; i < instancia.n_linhas; i++)
//             {
//                 linhas_de_producao.push_back({instancia.custo_producao[produtos_id[i] - 1], {produtos_id[i]}});
//             }

//             for (i = instancia.n_linhas; i < produtos_id.size() ; i++)
//             {
//                 melhor_custo = 9999;
//                 Insersao melhor_insercao;

//                 for (j = 0; j < instancia.n_linhas; j++)
//                 {
//                     size_produtos = linhas_de_producao[j].produtos.size();

//                     for (k = 0; k <= size_produtos; k++)
//                     {
//                         int custo = 0;
//                         // adiciona no começo
//                         if (k == 0)
//                         {
//                             custo = instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[k] - 1];
//                         }
//                         // adiciona no final
//                         else if (k == size_produtos)
//                         {
//                             custo = instancia.tempo_preparo[linhas_de_producao[j].produtos[k - 1] - 1][produtos_id[i] - 1];
//                         }
//                         // adiciona no meio
//                         else
//                         {
//                             custo += instancia.tempo_preparo[linhas_de_producao[j].produtos[k - 1] - 1][produtos_id[i] - 1];
//                             custo += instancia.tempo_preparo[produtos_id[i] - 1][linhas_de_producao[j].produtos[k] - 1];
//                             custo -= instancia.tempo_preparo[linhas_de_producao[j].produtos[k - 1] - 1][linhas_de_producao[j].produtos[k] - 1]; 
//                         }

//                         if (custo < melhor_custo)
//                         {
//                             melhor_custo = custo;
//                             melhor_insercao = {custo, k, j};
//                         }
//                     }

//                 }
//                 if (melhor_insercao.posicao == linhas_de_producao[melhor_insercao.linha].produtos.size())
//                 {
//                     linhas_de_producao[melhor_insercao.linha].produtos.push_back(produtos_id[i]);
//                 }
//                 else
//                 {
//                     linhas_de_producao[melhor_insercao.linha].produtos.insert(linhas_de_producao[melhor_insercao.linha].produtos.begin() + melhor_insercao.posicao, produtos_id[i]);
//                 }
                
//             }

//             Solution solution = Solution(linhas_de_producao, instancia);
//             solution.calcula_custo_total();
//             return solution;
//         }
// };



