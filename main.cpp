#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

#include "Instancia.cpp"
#include "Solution.cpp"
#include "Construcao.cpp"
#include "SwapIntra.cpp"
#include "SwapInter.cpp"
#include "Reinsertion.cpp"
#include "Perturbacao.cpp"
#include "VND.cpp"
#include "csv.cpp"
using namespace std;

int main()
{
    // criarArquivoCSV("resultados_custo.csv");
    // criarArquivoCSV("resultados_tempo.csv");

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

    vector<double> media_construcoes;
    vector<double> medias_custos;
    vector<double> medias_tempos;

    int GRAPS_max_iter = 64;
    int ILS_max_iter = 4;
    int exec_max = 10;

    // Nao ta pegando as 2 ultimas instancias grandes aqui pra agilizar os testes
    for (int inst = 0; inst < instances_name.size(); inst++)
    {
        vector<int> custos = {};
        vector<int> custos_construcao = {};
        vector<double> tempos = {};

        for (int exec = 0; exec < exec_max; exec++)
        {

            //Escolher o caminho da pasta e comentar o outro  !!!!!!!!!!!!!!!!!!!!!
            string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\" + instances_name[inst];
            // string caminho_arquivo = "C:\\Users\\Guilherme\\Documents\\Faculdade\\p5\\APA\\projeto_APA\\instancias\\n52m5_A.txt";
            // string caminho_arquivo = "/home/mikenew/projeto_APA/instancias/n40m5_A.txt";
            
            Instancia instancia = leitor_de_instancias(caminho_arquivo);

            auto start = std::chrono::high_resolution_clock::now();

            Solution solution;
            Solution best_solution;
            Algoritmo algoritmo;

            solution = algoritmo.construcao(instancia);
            best_solution = Solution(solution); 
            custos_construcao.push_back(best_solution.custo_total);
            
            SwapIntra swintra = SwapIntra(instancia);
            SwapInter swinter = SwapInter(instancia);
            Reinsertion reinsertion = Reinsertion(instancia);
            Pertubacao_ultra_swap pertubacao = Pertubacao_ultra_swap(instancia);

            for (int i = 0; i < GRAPS_max_iter; i++){

                // if (i % 2 == 0)
                // {
                //     solution = algoritmo.construcao(instancia);
                // }
                // else
                // {
                //     solution = algoritmo.construcao_melhor_insersao(instancia);
                // }

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
        
        double media_custo = 0;
        double media_construcao = 0;
        double media_tempo = 0;


        for (int i = 0; i < custos.size(); i++)
        {
            media_custo += custos[i];
            media_construcao += custos_construcao[i];
            media_tempo += tempos[i];
        }

        media_custo = media_custo / custos.size();
        media_construcao = media_construcao / custos_construcao.size();
        media_tempo = media_tempo / tempos.size();

        medias_custos.push_back(media_custo);
        media_construcoes.push_back(media_construcao);
        medias_tempos.push_back(media_tempo);
    }

    // imprima todos os custos
    double tempo_total = 0;
    cout << "------------------" << endl;
    cout << "Custos Médios : " << endl;
    for (int i = 0; i < medias_custos.size(); i++)
    {
        cout << "------------------" << endl;
        cout << instances_name[i] << endl;
        cout << " => " << medias_custos[i] << " | " << media_construcoes[i] << " | " << medias_tempos[i]  << "s" << endl ;
        tempo_total += medias_tempos[i];
    }
    cout << "------------------" << endl;
    cout << "\nMédia tempo total: " << tempo_total * exec_max << endl;

    vector<string> registro_custo = {};
    vector<string> registro_construcao = {};
    vector<string> registro_tempo = {};


    registro_custo.push_back(std::to_string(exec_max));
    registro_custo.push_back(std::to_string(GRAPS_max_iter));
    registro_custo.push_back(std::to_string(ILS_max_iter));

    registro_construcao.push_back(std::to_string(exec_max));
    registro_construcao.push_back(std::to_string(0));
    registro_construcao.push_back(std::to_string(0));

    registro_tempo.push_back(std::to_string(exec_max));
    registro_tempo.push_back(std::to_string(GRAPS_max_iter));
    registro_tempo.push_back(std::to_string(ILS_max_iter));

    for (int i = 0; i < medias_custos.size(); i++)
    {
        registro_custo.push_back(std::to_string(medias_custos[i]));
        registro_construcao.push_back(std::to_string(media_construcoes[i]));
        registro_tempo.push_back(std::to_string(medias_tempos[i]));
    }

    if (registro_custo.size() - 3 != instances_name.size())
    {
        for (int i = 0; i < registro_custo.size() - 3 - instances_name.size(); i++)
        {
            registro_custo.push_back("9999");
            registro_construcao.push_back("9999");
            registro_tempo.push_back("9999");
        }
    }

    adicionarRegistroCSV("resultados/resultados_custo.csv", registro_custo);
    adicionarRegistroCSV("resultados/resultados_construcao.csv", registro_construcao);
    adicionarRegistroCSV("resultados/resultados_tempo.csv", registro_tempo);
    
    return 0;
    
}