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
#include "Perturbacao.cpp"
#include "VND.cpp"

using namespace std;

int main()
{
    //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
    vector<string> instances_name = 
    {
        "n10m2_A.txt",
        "n10m2_B.txt",
        "n15m3_A.txt",
        "n15m3_B.txt",
        "n15m4_A.txt",
        "n15m4_B.txt",
        "n29m4_A.txt",
        "n29m4_B.txt",
        "n29m6_A.txt",
        "n29m6_B.txt",
        "n40m5_A.txt",
        "n40m5_B.txt",
        "n52m5_A.txt",
        "n52m5_B.txt",
        "n450m16_A.txt",
        "n500m10_A.txt"
    };


    vector<int> custos;
    vector<double> tempos;

    for (int inst = 0; inst < instances_name.size() - 2; inst++)
    {
        for (int exec = 0; exec < 1; exec++)
        {
            string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\" + instances_name[inst];
            cout << caminho_arquivo << endl;
            // string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n52m5_A.txt";
            // string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/n40m5_A.txt";
            
            Instancia instancia = leitor_de_instancias(caminho_arquivo);

            auto start = std::chrono::high_resolution_clock::now();

            Solution solution;
            Solution best_solution;
            Algoritmo algoritmo;

            solution = algoritmo.construcao(instancia);
            best_solution = Solution(solution); 

            SwapIntra swintra = SwapIntra(instancia);
            SwapInter swinter = SwapInter(instancia);
            Reinsertion reinsertion = Reinsertion(instancia);
            Pertubacao_ultra_swap pertubacao = Pertubacao_ultra_swap(instancia);

            // print solucao inicial
            cout << "------------------" << endl;
            cout << "Solucao inicial: " << endl;
            cout << "Custo: " << solution.custo_total << endl;
            solution.print_solution();
            cout << "------------------" << endl;

            // GRASP + ILS 
            int GRAPS_max_iter = 25;
            int ILS_max_iter = 10;

            for (int i = 0; i < GRAPS_max_iter; i++){
                
                solution = algoritmo.construcao(instancia);
                buscaLocal(solution, swintra, swinter, reinsertion);

                for (int j = 0; j < ILS_max_iter; j++)
                {
                    pertubacao.run(solution);
                    buscaLocal(solution, swintra, swinter, reinsertion);

                    if (solution.custo_total < best_solution.custo_total)
                    {
                        best_solution = solution;

                        cout << "------------------" << endl;
                        cout << "Iteracao GRASP: " << i << endl;
                        cout << "Iteracao ILS: " << j << endl;
                        cout << "NOVO MELHOR Custo: " << best_solution.custo_total << endl;
                        cout << "------------------" << endl;

                        j = 0;
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
            tempos.push_back(elapsed_seconds.count());
        }
    }

    // imprima todos os custos
    double tempo_total = 0;
    cout << "------------------" << endl;
    cout << "Custos: " << endl;
    for (int i = 0; i < custos.size(); i++)
    {
        cout << "------------------" << endl;
        cout << "Instancia " << instances_name[i] << endl;
        cout << " => " << custos[i] << " | " << tempos[i] << endl ;
        tempo_total += tempos[i];
    }
    cout << "------------------" << endl;
    cout << "\ntempo total: " << tempo_total << endl;



    return 0;
    
}