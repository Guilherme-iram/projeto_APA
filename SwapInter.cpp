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
        //Não mexi aqui, só fiz os custos do swap em baixo !!!!!!!!!!!!
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
                std::cout << "CASO 3" << std::endl;
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
                deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];

                deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
                deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];

                std::cout << "Custo = " << deltaCusto << std::endl;

                caso = 3;
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
            std::cout << "CASO 4" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];
            
            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 4;
        }

        else if ((i >= 1 && j == size_j -1) && i < size_i - 1)
        {
            std::cout << "CASO 5" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j- 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            
            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 5;
        }
        
        else if ((i >= 1 && j >= 1) && i < size_i - 1)
        {
            std::cout << "CASO 6" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[i_l].produtos[i + 1] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];
            
            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 6;
        }
        

        else if (i == size_i - 1 && j == 0)
        {

            std::cout << "CASO 7" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 7;
        }

        else if ((i == size_i - 1 && j == size_j - 1))
        {

            std::cout << "CASO 8" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 8;
        }

        else if ((i == size_i - 1 && j >= 1))
        {

            std::cout << "CASO =9" << std::endl;

            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto -= instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i - 1] - 1][s.linhas_producao[j_l].produtos[j] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[j_l].produtos[j - 1] - 1][s.linhas_producao[i_l].produtos[i] - 1];
            deltaCusto += instancia.tempo_preparo[s.linhas_producao[i_l].produtos[i] - 1][s.linhas_producao[j_l].produtos[j + 1] - 1];

            std::cout << "Custo = " << deltaCusto << std::endl;

            caso = 9;
        }


        return {caso, deltaCusto};
    }
};