#include "Solution.hpp"
#include "Instancia.hpp"
#include <iostream>

class SwapInter
{
public:
    Instancia instancia;

    SwapInter(const Instancia &instancia)
    {
        this->instancia = instancia;
    };

    void run(Solution &s)
    {
    }

    void swap(Solution &s, int n_l, int i, int j)
    {
        int aux = s.linhas_producao[n_l].produtos[i];
        s.linhas_producao[n_l].produtos[i] = s.linhas_producao[n_l].produtos[j];
        s.linhas_producao[n_l].produtos[j] = aux;
    };

    std::vector<int> costSwap(const Solution &s, int i_l, int j_l, int i, int j)
    {
        int deltaCusto = 0;
        int caso = 0;

        int size_i = s.linhas_producao[i_l].produtos.size();
        int size_j = s.linhas_producao[j_l].produtos.size();

        if (i == 0 && j == 0)
        {
            std::cout << "CASO 1" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;
            caso = 1;
        }

        else if ((i == 0 && j >= 1))
        {
            std::cout << "CASO 2" << std::endl;

            if (j == size_j - 1)
            {
                std::cout << "J ultimo e i = 0" << std::endl;
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];

                std::cout << "Custo = " << deltaCusto << std::endl;
                return {caso, deltaCusto};
            }
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;
            caso = 2;
        }


        else if ((i >= 1 && j == 0) && i < size_i - 1)
        {
            std::cout << "CASO 3" << std::endl;
            //n testei
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];
            caso = 3;
        }

        else if ((i >= 1 && j == size_j -1) && i < size_i - 1)
        {
            std::cout << "CASO 4" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j- 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            caso = 4;
        }
        
        else if ((i >= 1 && j >= 1) && i < size_i - 1)
        {
            std::cout << "CASO 5" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];
            caso = 5;
        }
        

        else if (i == size_i - 1 && j == 0)
        {
            //NÃO TESTEI, POR FAVOR TESTAR !!!!!!!!!!
            std::cout << "CASO 6" << std::endl;
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 6;
        }

        else if ((i == size_i - 1 && j == size_j - 1))
        {
            //NÃO TESTEI, POR FAVOR TESTAR !!!!!!!!!!
            std::cout << "CASO 7" << std::endl;
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 7;
        }

        else if ((i == size_i - 1 && j >= 1))
        {
            //NÃO TESTEI, POR FAVOR TESTAR !!!!!!!!!!
            std::cout << "CASO 8" << std::endl;
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 8;
        }



        // else if (j == (size_p - 1) && i < (size_p - 2))
        // {
        //     // std::cout << "CASO 5" << std::endl;
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];

        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
        //     caso = 5;
        // }
        // else if (i + 1 == j)
        // {
        //     // std::cout << "CASO 6" << std::endl;
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
        //     caso = 6;
        // }
        // else
        // {
        //     // std::cout << "Caso BASE" << std::endl;
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
        //     deltaCusto -= instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];

        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i - 1] - 1][s.linhas_producao[n_l].produtos[j] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j] - 1][s.linhas_producao[n_l].produtos[i + 1] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[j - 1] - 1][s.linhas_producao[n_l].produtos[i] - 1];
        //     deltaCusto += instancia.tempo_preparo[s.linhas_producao[n_l].produtos[i] - 1][s.linhas_producao[n_l].produtos[j + 1] - 1];
        //     caso = -1;
        // }

        return {caso, deltaCusto};
    }
};