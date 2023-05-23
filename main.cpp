#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "Instancia.cpp"
#include "Solution.cpp"
#include "Construcao.cpp"
#include "SwapIntra.cpp"
#include "SwapInter.cpp"
#include "Reinsertion.cpp"

using namespace std;

int main()
{
    //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
    
    //string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n40m5_A.txt";
    string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/n40m5_A.txt";
    
    Instancia instancia = leitor_de_instancias(caminho_arquivo);
    vector<int> custos;

    for (int exec = 0; exec < 10; exec++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        Solution solution;
        Algoritmo algoritmo;

        solution = algoritmo.construcao(instancia);
        Solution best_solution = Solution(solution); 

        SwapIntra swintra = SwapIntra(instancia);
        SwapInter swinter = SwapInter(instancia);
        Reinsertion reinsertion = Reinsertion(instancia);

        // print solucao inicial
        cout << "------------------" << endl;
        cout << "Solucao inicial: " << endl;
        cout << "Custo: " << solution.custo_total << endl;
        solution.print_solution();
        cout << "------------------" << endl;

        // GRASP 
        int GRAPS_max_iter = 10000;
        for (int i = 1; i < GRAPS_max_iter; i++){
            
            solution = algoritmo.construcao(instancia);
            
            // VND
            for (int k = 1; k <= 1; k++)
            {
                double melhor_custo = best_solution.custo_total;
            
                switch (k)
                {
                    case 1:
                        swintra.run(solution);
                        break;
                
                    case 2:
                        swinter.run(solution);
                        break;

                    case 3:
                        reinsertion.run(solution);
                        break;
                    
                }
                
                solution.calcula_custo_total();

                if (solution.custo_total < melhor_custo)
                {   
                    melhor_custo = solution.custo_total;
                    best_solution = solution;
                    k = 0;

                    // cout << "------------------" << endl;
                    cout << "Iteracao: " << i << endl;
                    cout << "NOVO MELHOR Custo: " << best_solution.custo_total << endl;
                    // cout << "------------------" << endl;

                } 

            }

        }
        
            
        auto end = std::chrono::high_resolution_clock::now();

        // Cálculo do tempo de execução em segundos
        std::chrono::duration<double> elapsed_seconds = end - start;

        best_solution.calcula_custo_total();

        cout << "------------------" << endl;
        cout << "Melhor solucao APOS SWAP: " << endl;
        cout << "Custo: " << best_solution.custo_total << endl;
        best_solution.print_solution();
        std::cout << "Tempo de execução: " << elapsed_seconds.count() << " segundos\n";
        std::cout << "FIM DO PROGRAMA" << std::endl;
        cout << "------------------" << endl;

        custos.push_back(best_solution.custo_total);
    }

    // imprima todos os custos
    cout << "------------------" << endl;
    cout << "Custos: " << endl;
    for (int i = 0; i < custos.size(); i++)
    {
        cout << " => " << custos[i] << endl;
    }
    cout << "------------------" << endl;
    

    return 0;
    
}